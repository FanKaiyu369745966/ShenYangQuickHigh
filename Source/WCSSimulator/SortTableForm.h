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
	QPushButton* m_pbutAdd;
	QPushButton* m_pbutEdit;
	QPushButton* m_pbutDel;
	QLineEdit* m_leditNo;
	QLineEdit* m_leditName;
	QStandardItemModel* m_model;
public:
	quint8 m_byNo;
	QString m_strName;
private:
	/*!
	 * @brief 初始化控件内的成员
	 * @return void
	 * @since 2020/2/10 FanKaiyu
	 * 初始化控件内的成员，创建子控件并布局。以及子控件添加信号和槽函数。
	 */
	void Initialize();

signals:
	void AddNewSortTable(bool&);

	void DeleteSortTable(bool&);

	void EditSortTable(bool&);

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
	void OnSelectItem(const QModelIndex& current, const QModelIndex& previous);

public:
	/*!
	 * @brief 添加新的分捡台
	 * @arg quint8 分捡台编号
	 * @arg QString 分捡台名称
	 * @return bool 添加成功返回true,否则返回false
	 * @since 2020/2/23 FanKaiyu
	 * 向列表中添加新的分捡台
	 */
	bool AddNewSortTable(quint8 no, QString name);

	/*!
	 * @brief 删除分捡台
	 * @arg quint8 分捡台编号
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 从列表中将分捡台删除
	 */
	void DeleteSortTable(quint8 no);

	/*!
	 * @brief 编辑分捡台
	 * @arg quint8 分捡台编号
	 * @arg QString 分捡台名称
	 * @return bool 编辑成功返回true,否则返回false
	 * @since 2020/2/23 FanKaiyu
	 * 修改列表中分捡台的属性参数
	 */
	bool EditSortTable(quint8 no, QString name);
};
