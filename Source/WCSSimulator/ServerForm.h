﻿#pragma once

#include <QWidget>
//#include "ui_ServerForm.h"

class ServerForm : public QWidget
{
	Q_OBJECT

public:
	ServerForm(QWidget* parent = Q_NULLPTR);
	~ServerForm();

private:
	//Ui::ServerForm ui;
private:
	/*!
	 * @brief 初始化控件内的成员
	 * @return void
	 * @since 2020/2/10 FanKaiyu
	 * 初始化控件内的成员，创建子控件并布局。以及子控件添加信号和槽函数。
	 */
	void Initialize();
};