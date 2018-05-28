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
	// 文件传输
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

	// 文件传输
	connect(m_pFileTransfer, &ChFileTransfer::sigConnected, this, [=]() {
		if (!ui.lineEditFile->text().isEmpty())
		{
			ui.btnUpdate->setEnabled(true);
		}
	});
	// 进度条最大值
	connect(m_pFileTransfer, &ChFileTransfer::sigMaxSize, this, [=](qint64 maxSize) {
		ui.progressBar->setMaximum(maxSize);
	});
	// 更新进度
	connect(m_pFileTransfer, &ChFileTransfer::sigUpdateProgress, this, [=](qint64 bytes) {
		ui.progressBar->setValue(bytes);
	});

	// 消息
	connect(m_pFileTransfer, &ChFileTransfer::sigMsg, this, [=](const QString& strMsg) {
		ui.textBrowMsg->append(strMsg);
	});
}

// 重启相机
void ChUpdateWidget::restartCamera()
{
	gChSendManager->sendMessage(m_pSocket, PAKAGE_RESTART);
}

// 执行升级
void ChUpdateWidget::slotUpdate()
{
	QString strText = ui.btnUpdate->text();
	if (QStringLiteral("升级") == strText)
	{
		m_pFileTransfer->sendFile();
		ui.btnUpdate->setEnabled(false);
	}
	else if(QStringLiteral("立即重启") == strText)
	{
		restartCamera();
		ui.btnUpdate->setText(QStringLiteral("升级"));
		// 窗口关闭
		this->close();
		ui.lineEditFile->clear();
	}
}

// 链接到服务
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

// 选择文件
void ChUpdateWidget::slotBtnScanClicked()
{
	QStringList strLstFiles = QFileDialog::getOpenFileNames(this, QStringLiteral("选择文件"), ".", tr("*"));
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

// 接收消息
void ChUpdateWidget::slotReadyRead()
{
	qDebug() << "read msg" << "m_pSocket->bytesAvailable()=" << m_pSocket->bytesAvailable();

	// 循环接收 一次接收到多个包，以防没有读取完毕，造成丢包
	while (m_pSocket->bytesAvailable() > 0)
	{
		ChPakage oRecvPakage;
		m_pSocket->read((char*)&oRecvPakage, sizeof(ChPakage));
		qInfo() << "type = " << (ChPakageType)oRecvPakage.m_type;
		switch (oRecvPakage.m_type)
		{
		case PAKAGE_UPDATE:	// 升级 传输文件
		{
			qDebug() << "update msg = " << oRecvPakage.m_Msg;
			m_pFileTransfer->connectToServer();
		}
		break;
		case PAKAGE_MESSAGE:	// 消息
		{
			qDebug() << "return message = " << oRecvPakage.m_Msg;
			ui.textBrowMsg->append(oRecvPakage.m_Msg);
		}
		break;
		case PAKAGE_FILE_SEND_END:	// 发送完成
			break;
		case PAKAGE_FILE_RECV_END:	// 接收完成
			{
				qDebug() << "recv file end";
				// 开始传输下一个文件
				m_pFileTransfer->sendNextFile();
			}
			break;
		case PAKAGE_RESTART: // 重启相机
			{
				ui.textBrowMsg->append(QStringLiteral("升级完成, 请重启相机"));
				ui.btnUpdate->setEnabled(true);
				ui.btnUpdate->setText(QStringLiteral("立即重启"));
			}
			break;
		default:
			break;
		}
	}
}

// 断开连接
void ChUpdateWidget::slotDisconnected()
{
	if (m_pSocket)
	{
		m_pSocket->close();
		m_pSocket->deleteLater();
		m_pSocket = nullptr;
	}
}
