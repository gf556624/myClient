#include "ChUpdateWidget.h"
#include <QtWidgets/QApplication>
#include "ChLog.h"

int main(int argc, char *argv[])
{
	// ��ʼ����־
	gChLog->init();

	QApplication a(argc, argv);
	ChUpdateWidget w;
	w.show();
	return a.exec();
}