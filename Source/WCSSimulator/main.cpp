#include "WCSSimulator.h"
#include <QtWidgets/QApplication>
#include <QHostAddress>
#include <QDebug>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	WCSSimulator w;
	w.show();
	return a.exec();
}
