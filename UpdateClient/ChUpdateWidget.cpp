#include "ChUpdateWidget.h"
#include "ChDefine.h"
#include "ChSendManager.h"
#include "ChGlobalPara.h"

#include <QFileDialog>
#include <QDataStream>
#include <QDebug>


ChUpdateWidget::ChUpdateWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	init();
	createConnections();

	ui.btnUpdate->setEnabled(false);
	ui.btnConnect->setEnabled(true);
}

ChUpdateWidget::~ChUpdateWidget()
{
	if (m_pFileTransfer)
	{
		m_pFileTransfer->deleteLater();
		m_pFileTransfer = nullptr;
	}
}

void ChUpdateWidget::init()
{
	m_pSocket = new QTcpSocket(this);
	// �ļ�����
	m_pFileTransfer = new ChFileTransfer(m_pSocket, this);
}

void ChUpdateWidget::createConnections()
{
	connect(ui.btnUpdate, &QPushButton::clicked, this, &ChUpdateWidget::slotUpdate);
	connect(ui.btnConnect, &QPushButton::clicked, this, &ChUpdateWidget::slotConnect);
	connect(m_pSocket, &QTcpSocket::connected, this, [&]() {
		qDebug() << "connected";
		ui.textBrowMsg->append(tr("connected"));
	});
	connect(m_pSocket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
		[=](QAbstractSocket::SocketError socketError) { 
		qDebug() << "connect error";
		ui.textBrowMsg->append(m_pSocket->errorString());
		
		ui.btnConnect->setEnabled(true);
	});

	connect(m_pSocket, &QTcpSocket::readyRead, this, &ChUpdateWidget::slotReadyRead);
	connect(m_pSocket, &QTcpSocket::disconnected, this, &ChUpdateWidget::slotDisconnected);
	connect(ui.btnScan, &QPushButton::clicked, this, &ChUpdateWidget::slotBtnScanClicked);

	// �ļ�����
	connect(m_pFileTransfer, &ChFileTransfer::sigConnected, this, [=]() {
		if (!ui.lineEditFile->text().isEmpty())
		{
			ui.btnUpdate->setEnabled(true);
		}
	});
	// ���������ֵ
	connect(m_pFileTransfer, &ChFileTransfer::sigMaxSize, this, [=](qint64 maxSize) {
		ui.progressBar->setMaximum(maxSize);
	});
	// ���½���
	connect(m_pFileTransfer, &ChFileTransfer::sigUpdateProgress, this, [=](qint64 bytes) {
		ui.progressBar->setValue(bytes);
	});

	// ��Ϣ
	connect(m_pFileTransfer, &ChFileTransfer::sigMsg, this, [=](const QString& strMsg) {
		ui.textBrowMsg->append(strMsg);
	});
}

// �������
void ChUpdateWidget::restartCamera()
{
	gChSendManager->sendMessage(m_pSocket, PAKAGE_RESTART);
}

// ִ������
void ChUpdateWidget::slotUpdate()
{
	QString strText = ui.btnUpdate->text();
	if (QStringLiteral("����") == strText)
	{
		m_pFileTransfer->sendFile();
		ui.btnUpdate->setEnabled(false);
	}
	else if(QStringLiteral("��������") == strText)
	{
		restartCamera();
		ui.btnUpdate->setText(QStringLiteral("����"));
		// ���ڹر�
		this->close();
		ui.lineEditFile->clear();
	}
}

// ���ӵ�����
void ChUpdateWidget::slotConnect()
{
	qDebug() << "connect";
	if (QAbstractSocket::ConnectedState != m_pSocket->state())
	{
		QString strIp = gChGlobalPara->getServerIp();
		int iPort = gChGlobalPara->getServerPort();
		m_pSocket->connectToHost(strIp, iPort);
	}

	ui.btnConnect->setEnabled(false);
}

// ѡ���ļ�
void ChUpdateWidget::slotBtnScanClicked()
{
	QStringList strLstFiles = QFileDialog::getOpenFileNames(this, QStringLiteral("ѡ���ļ�"), ".", tr("*"));
	if (strLstFiles.isEmpty() && ui.lineEditFile->text().isEmpty())
	{
		ui.btnUpdate->setEnabled(false);
		return;
	}

	qInfo() << "state=" << m_pFileTransfer->state();
	if (QAbstractSocket::ConnectedState == m_pFileTransfer->state())
	{
		ui.btnUpdate->setEnabled(true);
	}

	ui.lineEditFile->setText(strLstFiles.join(";"));
	m_pFileTransfer->setSendFiles(strLstFiles);
}

// ������Ϣ
void ChUpdateWidget::slotReadyRead()
{
	qDebug() << "read msg" << "m_pSocket->bytesAvailable()=" << m_pSocket->bytesAvailable();

	// ѭ������ һ�ν��յ���������Է�û�ж�ȡ��ϣ���ɶ���
	while (m_pSocket->bytesAvailable() > 0)
	{
		ChPakage oRecvPakage;
		m_pSocket->read((char*)&oRecvPakage, sizeof(ChPakage));
		qInfo() << "type = " << (ChPakageType)oRecvPakage.m_type;
		switch (oRecvPakage.m_type)
		{
		case PAKAGE_UPDATE:	// ���� �����ļ�
		{
			qDebug() << "update msg = " << oRecvPakage.m_Msg;
			m_pFileTransfer->connectToServer();
		}
		break;
		case PAKAGE_MESSAGE:	// ��Ϣ
		{
			qDebug() << "return message = " << oRecvPakage.m_Msg;
			ui.textBrowMsg->append(oRecvPakage.m_Msg);
		}
		break;
		case PAKAGE_FILE_SEND_END:	// �������
			break;
		case PAKAGE_FILE_RECV_END:	// �������
			{
				qDebug() << "recv file end";
				// ��ʼ������һ���ļ�
				m_pFileTransfer->sendNextFile();
			}
			break;
		case PAKAGE_RESTART: // �������
			{
				ui.textBrowMsg->append(QStringLiteral("�������, ���������"));
				ui.btnUpdate->setEnabled(true);
				ui.btnUpdate->setText(QStringLiteral("��������"));
			}
			break;
		default:
			break;
		}
	}
}

// �Ͽ�����
void ChUpdateWidget::slotDisconnected()
{
	if (m_pSocket)
	{
		m_pSocket->close();
		m_pSocket->deleteLater();
		m_pSocket = nullptr;
	}
}
