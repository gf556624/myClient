/**
*
* File Name : ChFileTransfer.h
*
* Description : �ļ�������
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
	
	// ���ӵ�����
	void connectToServer();
	// ����Ҫ���͵��ļ�
	void setSendFiles(const QStringList& strList);
	// ��ʼ����
	void sendFile();

	// ������һ���ļ�
	void sendNextFile();

	// ����״̬
	QAbstractSocket::SocketState state()const;

private:
	void init();
	void createConnection();
	void freeMem();

	// ����
	void resetMember();

signals:
	// ���½���
	void sigUpdateProgress(qint64 bytes);
	// ���������ֵ
	void sigMaxSize(qint64 maxSize);
	// ��Ϣ
	void sigMsg(const QString& strMsg);
	// ����
	void sigConnected();

private slots:
	// ���·��ͽ���
	void slotUpdateProgress(qint64 bytes);
	// �Ͽ�����
	void slotDisconnected();

private:
	QTcpSocket* m_pSocket{ nullptr };		// client socket
	QTcpSocket* m_pFileSocket{ nullptr };	// file socket

	qint64 m_totalBytes{ 0 };			// �ļ��ܴ�С
	qint64 m_sendBytes{ 0 };			// �ѷ��ʹ�С
	qint64 m_bytesToWrite{ 0 };		// ʣ�����ݴ�С
	QFile m_file;					// Ҫ���͵��ļ�
	QByteArray m_sendData;			// ���͵����ݿ�

	const qint64 m_perSendSize{ 1024 * 1024 };	// ÿ�η��͵����ݴ�С 1M

	QStringList m_lstFiles;		// Ҫ���͵��ļ��б�
};

