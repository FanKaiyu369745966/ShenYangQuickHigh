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
#include <QHeaderView>
#include <QMessageBox>
#include <QGroupBox>
#include <QSet>
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
	QStandardItemModel* m_model;
public:
	QString m_strOrder;				/*< 订单号 */
	QString m_strTray;				/*!< 托盘码 */
	QStringList m_strlSortTable;	/*!< 分捡台列表 */
	QString m_strShipmentPort;		/*!< 出货口编号 */
private:
	QSet<quint8> m_setSort;			/*!< 分捡台集合 */
private:
	/*!
	 * @brief 初始化控件内的成员
	 * @return void
	 * @since 2020/2/10 FanKaiyu
	 * 初始化控件内的成员，创建子控件并布局。以及子控件添加信号和槽函数。
	 */
	void Initialize();

signals:

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
	 * @arg const QModelIndex &
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 当前选择的Item发生改变时触发的槽函数
	 */
	void OnSelectItem(const QModelIndex& current, const QModelIndex& previous);

	/*!
	 * @brief 释放选择按钮
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 选择按钮释放后触发的槽函数
	 */
	void PressedSelectButton();
public:
	/*!
	 * @brief 添加分捡台
	 * @arg quint8 分捡台编号
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 当分捡台增加时需调用此函数
	 */
	void AddNewSortTable(quint8 no);

	/*!
	 * @brief 删除分捡台
	 * @arg quint8 分捡台编号
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 当分捡台减少时需调用此函数
	 */
	void DeleteSortTable(quint8 no);

	// TODO 添加订单

	// TODO 删除订单

	// TODO 更新订单
};
