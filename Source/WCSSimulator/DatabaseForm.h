#pragma once

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFile>
#include <QCheckBox>
//#include "ui_DatabaseForm.h"

class DatabaseForm : public QWidget
{
	Q_OBJECT

public:
	DatabaseForm(QString host = "", QString dbname = "", QString user = "", QString password = "", QWidget* parent = Q_NULLPTR);
	~DatabaseForm();

private:
	//Ui::DatabaseForm ui;
private:
	QLineEdit* m_leditHost;
	QLineEdit* m_leditName;
	QLineEdit* m_leditUser;
	QLineEdit* m_leditPassword;
	QPushButton* m_pbutLink;

public:
	QString m_strHost;
	QString m_strDbName;
	QString m_strUser;
	QString m_strPassword;
	bool m_bLinked;
private:
	/*!
	 * @brief 初始化控件内的成员
	 * @return void
	 * @since 2020/2/15 FanKaiyu
	 * 初始化控件内的成员，创建子控件并布局。以及子控件添加信号和槽函数。s
	 */
	void Initialize();

signals:
	/*!
	 * @brief 连接数据库
	 * @arg bool& 连接成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/16 FanKaiyu
	 * 当点击连接按钮时发出的信号
	 */
	void OnButtonLink(bool&);

	/*!
	 * @brief 关闭数据库
	 * @return void
	 * @since 2020/2/16 FanKaiyu
	 * 当点击关闭按钮时发出的信号
	 */
	void OnButtonClose();

private slots:
	/*!
	 * @brief 显示密码
	 * @arg bool 为true则显示密码，否则隐藏密码
	 * @return void
	 * @since 2020/2/16 FanKaiyu
	 * 点击显示密码时触发的槽函数
	 */
	void slotCheckBoxToggle(bool checked);

	/*!
	 * @brief 点击连接按钮
	 * @return void
	 * @since 2020/2/16 FanKaiyu
	 * 点击连接按钮时触发的槽函数
	 */
	void slotPressedLinkButton();

	/*!
	 * @brief 更改主机名
	 * @return void
	 * @since 2020/2/16 FanKaiyu
	 * 当主机名发生改变时触发的槽函数
	 */
	void slotHostEditFinished();

	/*!
	 * @brief 更改数据库名称
	 * @return void
	 * @since 2020/2/16 FanKaiyu
	 * 当数据库名称发生改变时触发的槽函数
	 */
	void slotDbNameEditFinished();

	/*!
	 * @brief 更改用户名
	 * @return void
	 * @since 2020/2/16 FanKaiyu
	 * 当用户名发生改变的时候触发的槽函数
	 */
	void slotUserEditFinished();

	/*!
	 * @brief 更改密码
	 * @return void
	 * @since 2020/2/16 FanKaiyu
	 * 当密码发生改变的时候触发的槽函数
	 */
	void slotPasswordEditFinished();
};
