#pragma once

#include <QWidget>
//#include "ui_SortTableForm.h"

class SortTableForm : public QWidget
{
	Q_OBJECT

public:
	SortTableForm(QWidget* parent = Q_NULLPTR);
	~SortTableForm();

private:
	//Ui::SortTableFrom ui;
private:
	/*!
	 * @brief 初始化控件内的成员
	 * @return void
	 * @since 2020/2/10 FanKaiyu
	 * 初始化控件内的成员，创建子控件并布局。以及子控件添加信号和槽函数。
	 */
	void Initialize();
};
