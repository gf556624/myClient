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

	// 重启相机
	void restartCamera();

private slots:
	// 升级
	void slotUpdate();
	// 连接
	void slotConnect();
	// 选择文件
	void slotBtnScanClicked();
	// 接收消息
	void slotReadyRead();
	//
	void slotDisconnected();

private:
	Ui::ChUpdateWidgetClass ui;
	QTcpSocket* m_pSocket{nullptr};				// 消息
	ChFileTransfer* m_pFileTransfer{nullptr};	// 传输文件
};
