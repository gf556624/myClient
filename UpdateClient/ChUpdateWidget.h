#pragma once

#include <QtWidgets/QWidget>
#include "ui_ChUpdateWidget.h"

#include "ChFileTransfer.h"

#include <QTcpSocket>
#include <QFile>

class ChUpdateWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ChUpdateWidget(QWidget *parent = Q_NULLPTR);
	~ChUpdateWidget();

private:
	void init();
	void createConnections();

	// �������
	void restartCamera();

private slots:
	// ����
	void slotUpdate();
	// ����
	void slotConnect();
	// ѡ���ļ�
	void slotBtnScanClicked();
	// ������Ϣ
	void slotReadyRead();
	//
	void slotDisconnected();

private:
	Ui::ChUpdateWidgetClass ui;
	QTcpSocket* m_pSocket{nullptr};				// ��Ϣ
	ChFileTransfer* m_pFileTransfer{nullptr};	// �����ļ�
};
