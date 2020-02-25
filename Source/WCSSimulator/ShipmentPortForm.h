#pragma once

#include <QWidget>

#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QMessageBox>
//#include "ui_ShipmentPortForm.h"

class ShipmentPortForm : public QWidget
{
	Q_OBJECT

public:
	ShipmentPortForm(QWidget* parent = Q_NULLPTR);
	~ShipmentPortForm();

private:
	//Ui::ShipmentPortForm ui;
private:
	QPushButton* m_pbutAdd;
	QPushButton* m_pbutEdit;
	QPushButton* m_pbutDel;
	QLineEdit* m_leditNo;
	QLineEdit* m_leditName;
	QComboBox* m_combStatus;
	QStandardItemModel* m_model;
public:
	quint8 m_byNo;
	QString m_strName;
	bool m_bFull;
private:
	/*!
	 * @brief 初始化控件内的成员
	 * @return void
	 * @since 2020/2/10 FanKaiyu
	 * 初始化控件内的成员，创建子控件并布局。以及子控件添加信号和槽函数。
	 */
	void Initialize();
signals:
	void AddNewShipmentPort(bool&);

	void DeleteShipmentPort(bool&);

	void EditShipmentPort(bool&);

private slots:
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
	 * @brief 释放编辑按钮
	 * @return void
	 * @since 2020/2/23FanKaiyu
	 * 编辑按钮释放时触发的槽函数
	 */
	void PressedEditButton();

	/*!
	 * @brief 选择Item
	 * @arg const QModelIndex &
	 * @arg const QModelIndex &
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 当前选择的Item发生改变时触发的槽函数
	 */
	void OnSelectItem(const QModelIndex& current);

	/*!
	 * @brief 选择下拉项
	 * @arg int
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 当下拉列表选项发生改变时触发的槽函数
	 */
	void OnComboSelect(int index);
public:
	/*!
	 * @brief 添加新的出货口
	 * @arg quint8 出货口编号
	 * @arg QString 出货口名称
	  * @arg bool 出货口状态
	 * @return bool 添加成功返回true,否则返回false
	 * @since 2020/2/23 FanKaiyu
	 * 向列表中添加新的出货口
	 */
	bool AddNewShipmentPort(quint8 no, QString name, bool full = false);

	/*!
	 * @brief 删除出货口
	 * @arg quint8 出货口编号
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 从列表中将出货口删除
	 */
	void DeleteShipmentPort(quint8 no);

	/*!
	 * @brief 编辑出货口
	 * @arg quint8 出货口编号
	 * @arg QString 出货口名称
	 * @return bool 编辑成功返回true,否则返回false
	 * @since 2020/2/23 FanKaiyu
	 * 修改列表中出货口的属性参数
	 */
	bool EditShipmentPort(quint8 no, QString name);

	/*!
	 * @brief 编辑出货口
	 * @arg quint8 出货口编号
	 * @arg bool 出货口状态
	 * @return bool 编辑成功返回true,否则返回false
	 * @since 2020/2/23 FanKaiyu
	 * 修改列表中出货口的属性参数
	 */
	bool EditShipmentPort(quint8 no, bool full);

	/*!
	 * @brief 编辑出货口
	 * @arg quint8 出货口编号
	 * @arg QString 出货口名称
	 * @arg bool 出货口状态
	 * @return bool 编辑成功返回true,否则返回false
	 * @since 2020/2/23 FanKaiyu
	 * 修改列表中出货口的属性参数
	 */
	bool EditShipmentPort(quint8 no, QString name, bool full);

	void Clear();

	bool IsVaild(quint8 no);
	bool IsVaild(quint8 no, QString& name, bool& full);
};
