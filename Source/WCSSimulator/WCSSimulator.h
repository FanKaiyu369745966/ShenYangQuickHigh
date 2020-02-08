#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_WCSSimulator.h"

class WCSSimulator : public QMainWindow
{
	Q_OBJECT

public:
	WCSSimulator(QWidget *parent = Q_NULLPTR);

private:
	Ui::WCSSimulatorClass ui;
};
