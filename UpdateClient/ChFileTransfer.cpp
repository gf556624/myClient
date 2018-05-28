#include "ChFileTransfer.h"
#include "ChDefine.h"
#include "ChSendManager.h"
#include "ChGlobalPara.h"

#include <QTcpServer>
#include <QDataStream>
#include <QDir>


ChFileTransfer::ChFileTransfer(QTcpSocket* pSocket, QObject *parent/* = 0*/)
	: m_pSocket(pSocket)
	, QObject(parent)
{
	init();
	createConnection();
}


ChFileTransfer::~ChFileTransfer()
{

}

// ���ӵ�����
void ChFileTransfer::connectToServer()
{
	// �ļ����佨������
	QString strIp = gChGlobalPara->getServerIp();
	int iPort = gChGlobalPara->getFileServerPort();
	m_pFileSocket->connectToHost(strIp, iPort);
	qInfo() << "file socket connect..." << "ip=" << strIp << "port=" << iPort;
}

void ChFileTransfer::setSendFiles(const QStringList& strList)
{
	m_lstFiles = strList;

	if (m_lstFiles.isEmpty())
	{
		return;
	}

	// ��һ��Ҫ�����ļ�
	m_file.setFileName(m_lstFiles.first());
	m_totalBytes = m_file.size();
}

// ��ʼ����
void ChFileTransfer::sendFile()
{
	qDebug() << "startSend";
	if (m_file.fileName().isEmpty())
	{
		return;
	}

	if (!m_file.open(QIODevice::ReadOnly))
	{
		emit sigMsg(QStringLiteral("%1 ��ʧ��").arg(m_file.fileName()));
		return;
	}

	if (m_lstFiles.isEmpty())
	{
		return;
	}

	QString strFileName = m_lstFiles.first();
	emit sigMsg(QStringLiteral("%1 ���ڷ���...").arg(strFileName));

	QDataStream sendOut(&m_sendData, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_8);
	QString currentFileName = QFileInfo(strFileName).fileName();
	sendOut << qint64(0) << qint64(0) << currentFileName;

	// �ܴ�С = �ļ���С + ���͵��ļ�ͷ���Ĵ�С
	m_totalBytes += m_sendData.size();
	sendOut.device()->seek(0);

	// �ļ�ͷ��: sendOut << �ļ���С << �ļ�����С << �ļ���
	sendOut << m_totalBytes << qint64((m_sendData.size() - sizeof(qint64) * 2));

	// ʣ��Ҫ���͵Ĵ�С
	m_bytesToWrite = m_totalBytes - m_pFileSocket->write(m_sendData);

	// ���ͺ�������Ϳ黺��
	m_sendData.resize(0);

	emit sigMaxSize(m_totalBytes);
}

// ������һ���ļ�
void ChFileTransfer::sendNextFile()
{
	if (!m_lstFiles.isEmpty())
	{
		resetMember();
		m_file.setFileName(m_lstFiles.first());
		m_totalBytes = m_file.size();
		// ��ʼ������һ���ļ�
		sendFile();
	}
	else
	{
		// �����ļ����������
		gChSendManager->sendMessage(m_pSocket, PAKAGE_FILE_SEND_END);
	}
}

// ����״̬
QAbstractSocket::SocketState ChFileTransfer::state() const
{
	return m_pFileSocket->state();
}

// ��ʼ��
void ChFileTransfer::init()
{
	m_sendData.resize(0);
	m_pFileSocket = new QTcpSocket(this);
}

// �źŲ�����
void ChFileTransfer::createConnection()
{
	connect(m_pFileSocket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
		[=](QAbstractSocket::SocketError socketError) {
		qDebug() << "file connect error";
		emit sigMsg(m_pFileSocket->errorString());
	});
	connect(m_pFileSocket, &QTcpSocket::connected, this, [&]() {
		qDebug() << "file socket connected";
		emit sigMsg("file socket connected");
		emit sigConnected();
	});

	connect(m_pFileSocket, &QTcpSocket::bytesWritten, this, &ChFileTransfer::slotUpdateProgress);
	connect(m_pFileSocket, &QTcpSocket::disconnected, this, &ChFileTransfer::slotDisconnected);
}

// �ͷ�
void ChFileTransfer::freeMem()
{
	
}

// ����
void ChFileTransfer::resetMember()
{
	m_totalBytes = 0;
	m_sendBytes = 0;
	m_bytesToWrite = 0;
	m_file.setFileName("");
	m_sendData.resize(0);
	// ��һ���ļ���ʼ����
	emit sigUpdateProgress(0);
}

// ���·��ͽ���
void ChFileTransfer::slotUpdateProgress(qint64 bytes)
{
	//�Ѿ����͵�����
	m_sendBytes += (int)bytes;

	//����Ѿ�����������
	if (m_bytesToWrite > 0)
	{
		//ÿ�η���m_perSendSize�Ĵ�С�����ݣ�Ϊ1Mÿ�Σ����ʣ�����ݲ���1M���ͷ���ʣ�����ݵĴ�С
		m_sendData = m_file.read(qMin(m_bytesToWrite, m_perSendSize));
		//������һ�����ݺ�ʣ�����ݵĴ�С
		m_bytesToWrite -= m_pFileSocket->write(m_sendData);

		//��շ��ͻ�����
		m_sendData.resize(0);
	}
	else//���û�з����κ����ݣ���ر��ļ�
	{
		m_file.close();
		m_sendData.resize(0);
	}

	//����������
	if (m_sendBytes == m_totalBytes)
	{
		QString strFileName = QFileInfo(m_lstFiles.first()).fileName();
		emit sigMsg(QStringLiteral("%1 ���ͳɹ�!").arg(strFileName));
		m_file.close();
		m_sendData.resize(0);

		// ������ɴ��б��Ƴ�
		if (!m_lstFiles.isEmpty())
		{
			m_lstFiles.removeFirst();
		}
	}

	//���½�����
	emit sigUpdateProgress(m_sendBytes);
}

// �Ͽ�����
void ChFileTransfer::slotDisconnected()
{
	freeMem();
}

