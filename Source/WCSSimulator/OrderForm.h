#pragma once

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QSqlQueryModel>
#include <QHeaderView>
#include <QMessageBox>
#include <QGroupBox>
#include <QSet>
#include <QSqlTableModel>
#include <QSqlQuery>

//#include "ui_OrderForm.h"

class OrderForm : public QWidget
{
	Q_OBJECT

public:
	OrderForm(QWidget* parent = Q_NULLPTR);
	~OrderForm();

private:
	//Ui::OrderForm ui;
private:
	QPushButton* m_pbutAdd;
	//QPushButton* m_pbutEdit;
	QPushButton* m_pbutDel;
	QLineEdit* m_leditNo;
	QLineEdit* m_leditTary;
	QLineEdit* m_leditSort;
	QLineEdit* m_leditShipment;
	QTableView* m_table;
	QStandardItemModel* m_model;
public:
	QString m_strOrder;					/*< 订单号 */
	QString m_strTray;					/*!< 托盘码 */
	QStringList m_strlSortTable;			/*!< 分捡台列表 */
	quint8 m_byShipmentPort;				/*!< 出货口编号 */
private:
	QSqlDatabase m_database;
	QMap<quint8, QString> m_mapSort;		/*!< 分捡台集合 */
	bool m_bSearch;						/*!< 搜索标识 */
private:
	/*!
	 * @brief 初始化控件内的成员
	 * @return void
	 * @since 2020/2/10 FanKaiyu
	 * 初始化控件内的成员，创建子控件并布局。以及子控件添加信号和槽函数。
	 */
	void Initialize();

signals:
	void AddNewOrder(bool&);
	void DeleteOrder(bool&);
	//void EditOrder(bool&);
private slots:
	/*!
	 * @brief 点击自动生成按钮
	 * @arg bool
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 点击自动生成单选按钮时触发的槽函数
	 */
	void OnClickCheckButton(bool checked);

	/*!
	 * @brief 编辑框修改完成
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 编辑框接收enter、return或失去焦点时触发的槽函数
	 */
	void EditFinished();

	/*!
	 * @brief 释放添加按钮
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 添加按钮释放后触发的槽函数
	 */
	void PressedAddButton();

	/*!
	 * @brief 释放删除按钮
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 删除按钮释放时触发的槽函数
	 */
	void PressedDeleteButton();

	/*!
	 * @brief 选择Item
	 * @arg const QModelIndex &
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 当前选择的Item发生改变时触发的槽函数
	 */
	void OnSelectItem(const QModelIndex& current);

	/*!
	 * @brief 释放选择按钮
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 选择按钮释放后触发的槽函数
	 */
	void PressedSelectButton();

	/*!
	 * @brief 释放搜索按钮
	 * @return void
	 * @since 2020/2/25 FanKaiyu
	 * 搜索安释放后触发的槽函数
	 */
	void PressedSearchButton();
public:
	/*!
	 * @brief 添加分捡台
	 * @arg quint8 分捡台编号
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 当分捡台增加时需调用此函数
	 */
	void AddNewSortTable(quint8 no, QString name);

	/*!
	 * @brief 删除分捡台
	 * @arg quint8 分捡台编号
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 当分捡台减少时需调用此函数
	 */
	void DeleteSortTable(quint8 no);

	/*!
	 * @brief 更新数据
	 * @return void
	 * @since 2020/2/25 FanKaiyu
	 * 重新刷新数据
	 */
	void UpdateData();

	/*!
	 * @brief 打开数据库
	 * @arg QString
	 * @arg QString
	 * @arg QString
	 * @arg QString
	 * @return void
	 * @since 2020/2/25 FanKaiyu
	 * 数据库连接成功时调用此函数
	 */
	void OpenDatabase(QString host, QString name, QString user, QString password);

	/*!
	 * @brief 关闭数据库
	 * @return void
	 * @since 2020/2/25 FanKaiyu
	 * 中止数据库连接时调用此函数
	 */
	void CloseDatabase();
};
