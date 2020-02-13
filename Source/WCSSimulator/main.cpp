#include "WCSSimulator.h"
#include <QtWidgets/QApplication>
#include <QDebug>
#include "Discharger.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	WCSSimulator w;
	w.show();

	Discharger tmp(1, "127.0.0.1:10086", false);

	return a.exec();
}
