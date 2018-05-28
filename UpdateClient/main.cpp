#include "ChUpdateWidget.h"
#include <QtWidgets/QApplication>
#include "ChLog.h"

int main(int argc, char *argv[])
{
	// 初始化日志
	gChLog->init();

	QApplication a(argc, argv);
	ChUpdateWidget w;
	w.show();
	return a.exec();
}