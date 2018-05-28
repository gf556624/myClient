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

// 连接到服务
void ChFileTransfer::connectToServer()
{
	// 文件传输建立连接
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

	// 第一个要发的文件
	m_file.setFileName(m_lstFiles.first());
	m_totalBytes = m_file.size();
}

// 开始发送
void ChFileTransfer::sendFile()
{
	qDebug() << "startSend";
	if (m_file.fileName().isEmpty())
	{
		return;
	}

	if (!m_file.open(QIODevice::ReadOnly))
	{
		emit sigMsg(QStringLiteral("%1 打开失败").arg(m_file.fileName()));
		return;
	}

	if (m_lstFiles.isEmpty())
	{
		return;
	}

	QString strFileName = m_lstFiles.first();
	emit sigMsg(QStringLiteral("%1 正在发送...").arg(strFileName));

	QDataStream sendOut(&m_sendData, QIODevice::WriteOnly);
	sendOut.setVersion(QDataStream::Qt_5_8);
	QString currentFileName = QFileInfo(strFileName).fileName();
	sendOut << qint64(0) << qint64(0) << currentFileName;

	// 总大小 = 文件大小 + 发送的文件头部的大小
	m_totalBytes += m_sendData.size();
	sendOut.device()->seek(0);

	// 文件头部: sendOut << 文件大小 << 文件名大小 << 文件名
	sendOut << m_totalBytes << qint64((m_sendData.size() - sizeof(qint64) * 2));

	// 剩余要发送的大小
	m_bytesToWrite = m_totalBytes - m_pFileSocket->write(m_sendData);

	// 发送后，清除发送块缓存
	m_sendData.resize(0);

	emit sigMaxSize(m_totalBytes);
}

// 发送下一个文件
void ChFileTransfer::sendNextFile()
{
	if (!m_lstFiles.isEmpty())
	{
		resetMember();
		m_file.setFileName(m_lstFiles.first());
		m_totalBytes = m_file.size();
		// 开始传输下一个文件
		sendFile();
	}
	else
	{
		// 所有文件都发送完成
		gChSendManager->sendMessage(m_pSocket, PAKAGE_FILE_SEND_END);
	}
}

// 连接状态
QAbstractSocket::SocketState ChFileTransfer::state() const
{
	return m_pFileSocket->state();
}

// 初始化
void ChFileTransfer::init()
{
	m_sendData.resize(0);
	m_pFileSocket = new QTcpSocket(this);
}

// 信号槽连接
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

// 释放
void ChFileTransfer::freeMem()
{
	
}

// 重置
void ChFileTransfer::resetMember()
{
	m_totalBytes = 0;
	m_sendBytes = 0;
	m_bytesToWrite = 0;
	m_file.setFileName("");
	m_sendData.resize(0);
	// 下一个文件开始进度
	emit sigUpdateProgress(0);
}

// 更新发送进度
void ChFileTransfer::slotUpdateProgress(qint64 bytes)
{
	//已经发送的数据
	m_sendBytes += (int)bytes;

	//如果已经发送了数据
	if (m_bytesToWrite > 0)
	{
		//每次发送m_perSendSize的大小的数据，为1M每次，如果剩余数据不足1M，就发送剩余数据的大小
		m_sendData = m_file.read(qMin(m_bytesToWrite, m_perSendSize));
		//发送完一次数据后还剩余数据的大小
		m_bytesToWrite -= m_pFileSocket->write(m_sendData);

		//清空发送缓冲区
		m_sendData.resize(0);
	}
	else//如果没有发送任何数据，则关闭文件
	{
		m_file.close();
		m_sendData.resize(0);
	}

	//如果发送完毕
	if (m_sendBytes == m_totalBytes)
	{
		QString strFileName = QFileInfo(m_lstFiles.first()).fileName();
		emit sigMsg(QStringLiteral("%1 发送成功!").arg(strFileName));
		m_file.close();
		m_sendData.resize(0);

		// 发送完成从列表移除
		if (!m_lstFiles.isEmpty())
		{
			m_lstFiles.removeFirst();
		}
	}

	//更新进度条
	emit sigUpdateProgress(m_sendBytes);
}

// 断开连接
void ChFileTransfer::slotDisconnected()
{
	freeMem();
}

