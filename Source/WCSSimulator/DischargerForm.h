#pragma once

#include <QWidget>

#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QHostAddress>
#include <QStandardItem>
#include <QHeaderView>
//#include "ui_DischargerForm.h"

class DischargerForm : public QWidget
{
	Q_OBJECT

public:
	DischargerForm(QWidget* parent = Q_NULLPTR);
	~DischargerForm();

private:
	//Ui::DischargerFrom ui;
private:
	QLineEdit* m_leditNo;
	QLineEdit* m_leditAddr;
	QCheckBox* m_checkClient;
	QPushButton* m_pbutAdd;
	QPushButton* m_pbutEdit;
	QPushButton* m_pbutDel;
	QStandardItemModel* m_model;
public:
	quint8 m_byNo;
	QString m_strAddr;
	bool m_bClient;

private:
	/*!
	 * @brief 初始化控件内的成员
	 * @return void
	 * @since 2020/2/10 FanKaiyu
	 * 初始化控件内的成员，创建子控件并布局。以及子控件添加信号和槽函数。
	 */
	void Initialize();

signals:
	void AddNewDischarger(bool&);

	void DeleteDischarger(bool&);

	void EditDischarger(bool&);

private slots:
	/*!
	 * @brief 点击客户端按钮
	 * @arg bool
	 * @return void
	 * @since 2020/2/21 FanKaiyu
	 * 点击客户端单选按钮时触发的槽函数
	 */
	void OnClickCheckButton(bool checked);

	/*!
	 * @brief 编辑框修改完成
	 * @return void
	 * @since 2020/2/21 FanKaiyu
	 * 编辑框接收enter、return或失去焦点时触发的槽函数
	 */
	void EditFinished();

	/*!
	 * @brief 释放添加按钮
	 * @return void
	 * @since 2020/2/21 FanKaiyu
	 * 添加按钮释放后触发的槽函数
	 */
	void PressedAddButton();

	/*!
	 * @brief 释放删除按钮
	 * @return void
	 * @since 2020/2/21 FanKaiyu
	 * 删除按钮释放时触发的槽函数
	 */
	void PressedDeleteButton();

	/*!
	 * @brief 释放编辑按钮
	 * @return void
	 * @since 2020/2/21 FanKaiyu
	 * 编辑按钮释放时触发的槽函数
	 */
	void PressedEditButton();

	/*!
	 * @brief 选择Item
	 * @arg const QModelIndex &
	 * @arg const QModelIndex &
	 * @return void
	 * @since 2020/2/21 FanKaiyu
	 * 当前选择的Item发生改变时触发的槽函数
	 */
	void OnSelectItem(const QModelIndex& current);

public:
	/*!
	 * @brief 添加新的分盘机
	 * @arg quint8 分盘机编号
	 * @arg QString 分盘机地址
	 * @arg bool 分盘机模式
	 * @return bool 添加成功返回true,否则返回false
	 * @since 2020/2/21 FanKaiyu
	 * 向列表中添加新的分盘机
	 */
	bool AddNewDischarger(quint8 no, QString addr, bool client);

	/*!
	 * @brief 添加新的分盘机
	 * @arg quint8 分盘机编号
	 * @arg QString 分盘机地址
	 * @arg quint16 分盘机端口
	 * @arg bool 分盘机模式
	 * @return bool 添加成功返回true,否则返回false
	 * @since 2020/2/21 FanKaiyu
	 * 向列表中添加新的分盘机
	 */
	bool AddNewDischarger(quint8 no, QString addr, quint16 port, bool client);

	/*!
	 * @brief 删除分盘机
	 * @arg quint8 分盘机编号
	 * @return void
	 * @since 2020/2/21 FanKaiyu
	 * 从列表中将分盘机删除
	 */
	void DeleteDischarger(quint8 no);

	/*!
	 * @brief 编辑分盘机
	 * @arg quint8 分盘机编号
	 * @arg QString 分盘机地址
	 * @arg bool 分盘机模式
	 * @return bool 编辑成功返回true,否则返回false
	 * @since 2020/2/21 FanKaiyu
	 * 修改列表中分盘机的属性参数
	 */
	bool EditDischarger(quint8 no, QString addr, bool client);

	/*!
	 * @brief 编辑分盘机
	 * @arg quint8 分盘机编号
	 * @arg QString 分盘机地址
	 * @arg quint16 分盘机端口
	 * @arg bool 分盘机模式
	 * @return bool 编辑成功返回true,否则返回false
	 * @since 2020/2/21 FanKaiyu
	 * 修改列表中分盘机的属性参数
	 */
	bool EditDischarger(quint8 no, QString addr, quint16 port, bool client);

	/*!
	 * @brief 更新分盘机状态
	 * @arg quint8 分盘机编号
	 * @arg bool 分盘机的连接状态
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 更新分盘机的连接状态
	 */
	void Update(quint8 no, bool connected);

	/*!
	 * @brief 更新分盘机的状态
	 * @arg quint8 分盘机编号
	 * @arg QString 分盘机的状态信息
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 更新分盘机的状态
	 */
	void Update(quint8 no, QString status);

	/*!
	 * @brief 更新分盘机的状态
	 * @arg quint8 分盘机编号
	 * @arg quint8 分盘机的状态码
	 * @return void
	 * @since 2020/2/23 FanKaiyu
	 * 更新分盘机的状态
	 */
	void Update(quint8 no, quint8 status);

	/*!
	 * @brief 更新分盘机状态
	 * @arg quint8
	 * @arg bool
	 * @arg QString
	 * @return void
	 * @since 2020/2/26 FanKaiyu
	 * 更新分盘机的请求状态
	 */
	void Update(quint8 no, bool request, QString order);

	void Clear();
};
