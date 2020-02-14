#pragma once

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
//#include "ui_ServerForm.h"

class ServerForm : public QWidget
{
	Q_OBJECT

public:
	ServerForm(const QString& addr = "", QWidget* parent = Q_NULLPTR);
	~ServerForm();

private:
	//Ui::ServerForm ui;
public:
	QString m_addr;		/*!< 服务端地址 */
	bool m_listened;	/*!< 监听标识 */
private:
	QLineEdit* m_leditAddr;
	QPushButton* m_pbutListen;
private:
	/*!
	 * @brief 初始化控件内的成员
	 * @return void
	 * @since 2020/2/10 FanKaiyu
	 * 初始化控件内的成员，创建子控件并布局。以及子控件添加信号和槽函数。
	 */
	void Initialize();

signals:
	/*!
	 * @brief 编辑完成时触发的槽函数
	 * @arg QString 修改后的服务端地址
	 * @return void
	 * @since 2020/2/14 FanKaiyu
	 * 当服务端地址编辑完成时触发的槽函数
	 */
	void signalEditFinished(QString);

	/*!
	 * @brief 当需要监听服务端时发送此信号
	 * @arg bool& 服务端监听成功 返回true,否则返回false
	 * @return void
	 * @since 2020/2/14 FanKaiyu
	 * 通知服务端开启监听
	 */
	void signalListen(bool&);

	/*!
	 * @brief 当需要停止监听服务端时发送此信号
	 * @return void
	 * @since 2020/2/14 FanKaiyu
	 * 通知服务端停止监听
	 */
	void signalClose();
private slots:
	/*!
	 * @brief 当编辑框编辑完成时触发的槽函数
	 * @return void
	 * @since 2020/2/14 FanKaiyu
	 * 当编辑框输入Enter、Return 或光标失去焦点时，更新服务端地址信息
	 */
	void slotEditFinished();

	/*!
	 * @brief 释放详情按钮
	 * @return void
	 * @since 2020/2/14 FanKaiyu
	 * 按下详情按钮并抬起时触发的槽函数
	 */
	void slotReleaseDetailButton();

public slots:
	/*!
	 * @brief 释放监听按钮
	 * @return void
	 * @since 2020/2/14 FanKaiyu
	 * 按下监听按钮并抬起时触发的槽函数
	 */
	void slotReleaseListenButton();
};
