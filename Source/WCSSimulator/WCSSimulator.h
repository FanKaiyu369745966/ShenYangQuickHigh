#pragma once

#include <QtWidgets/QMainWindow>
#include "ServerForm.h"
#include "DischargerForm.h"
#include "SortTableForm.h"
#include "ShipmentPortForm.h"
#include "OrderForm.h"
//#include "ui_WCSSimulator.h"

class WCSSimulator : public QMainWindow
{
	Q_OBJECT

public:
	WCSSimulator(QWidget* parent = Q_NULLPTR);

private:
	//Ui::WCSSimulatorClass ui;

private:
	/*!
	 * @brief 初始化主窗口
	 * @return void
	 * @since 2020/2/8 FanKaiyu
	 * 初始化主窗口以及创建窗口中的控件，并为控件进行布局
	 */
	void Initialize();
};
