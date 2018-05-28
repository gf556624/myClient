/**
*
* File Name : ChFileTransfer.h
*
* Description : 文件传输类
*
* Author : GuoFeng
*
* Create Date : 2018-05-07 14:50
*
* Update Date : 2018-05-07 14:50
*
* Version : 1.0
*
**/

#pragma once

#include <QObject>
#include <QFile>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
class QTcpServer;
QT_END_NAMESPACE

class ChFileTransfer : public QObject
{
	Q_OBJECT

public:
	explicit ChFileTransfer(QTcpSocket* pSocket, QObject *parent = 0);
	~ChFileTransfer();
	
	// 连接到服务
	void connectToServer();
	// 设置要发送的文件
	void setSendFiles(const QStringList& strList);
	// 开始发送
	void sendFile();

	// 发送下一个文件
	void sendNextFile();

	// 连接状态
	QAbstractSocket::SocketState state()const;

private:
	void init();
	void createConnection();
	void freeMem();

	// 重置
	void resetMember();

signals:
	// 更新进度
	void sigUpdateProgress(qint64 bytes);
	// 进度条最大值
	void sigMaxSize(qint64 maxSize);
	// 消息
	void sigMsg(const QString& strMsg);
	// 连接
	void sigConnected();

private slots:
	// 更新发送进度
	void slotUpdateProgress(qint64 bytes);
	// 断开连接
	void slotDisconnected();

private:
	QTcpSocket* m_pSocket{ nullptr };		// client socket
	QTcpSocket* m_pFileSocket{ nullptr };	// file socket

	qint64 m_totalBytes{ 0 };			// 文件总大小
	qint64 m_sendBytes{ 0 };			// 已发送大小
	qint64 m_bytesToWrite{ 0 };		// 剩余数据大小
	QFile m_file;					// 要发送的文件
	QByteArray m_sendData;			// 发送的数据块

	const qint64 m_perSendSize{ 1024 * 1024 };	// 每次发送的数据大小 1M

	QStringList m_lstFiles;		// 要发送的文件列表
};

