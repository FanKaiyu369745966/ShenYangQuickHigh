#pragma once

#include <QtWidgets/QMainWindow>
#include <QTcpServer>
#include <QSqlDatabase>
#include <QFile>
#include "ServerForm.h"
#include "DischargerForm.h"
#include "SortTableForm.h"
#include "ShipmentPortForm.h"
#include "OrderForm.h"
#include "DatabaseForm.h"
#include "Discharger.h"
//#include "ui_WCSSimulator.h"

class WCSSimulator : public QMainWindow
{
	Q_OBJECT

public:
	WCSSimulator(QWidget* parent = Q_NULLPTR);

private:
	//Ui::WCSSimulatorClass ui;
private:
	ServerForm* m_wServer;
	DatabaseForm* m_wDatabase;
	DischargerForm* m_wDischarger;
	SortTableForm* m_wSortTable;
	ShipmentPortForm* m_wShipment;
	OrderForm* m_wOrder;
private:
	QTcpServer* m_server;
	QSqlDatabase m_database;
private:
	/*!
	 * @brief 初始化主窗口
	 * @return void
	 * @since 2020/2/8 FanKaiyu
	 * 初始化主窗口以及创建窗口中的控件，并为控件进行布局
	 */
	void Initialize();

	/*!
	 * @brief 获取当前系统时间
	 * @return QString 返回格式为YY/MM/DD hh:mm:ss的时间字符串
	 * @since 2020/2/14 FanKaiyu
	 * 生成格式为YY/MM/DD hh:mm:ss的时间字符串
	*/
	QString GetCurrentTime();

	/*!
	 * @brief 关闭事件
	 * @arg QCloseEvent * 关闭事件指针
	 * @return void
	 * @since 2020/2/15 FanKaiyu
	 * 重载QMainWindow的关闭事件。在程序关闭前储存配置文件。
	 */
	void closeEvent(QCloseEvent* event);
private slots:
	/*!
	 * @brief 启动监听
	 * @arg bool& 监听成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/14 FanKaiyu
	 * 启动服务器监听的槽函数
	 */
	void slotStartListen(bool&);

	/*!
	 * @brief 关闭监听
	 * @return void
	 * @since 2020/2/14 FanKaiyu
	 * 关闭服务器监听的槽函数
	 */
	void slotEndListen();

	/*!
	 * @brief 修改服务端地址
	 * @arg QString
	 * @return void
	 * @since 2020/2/14 FanKaiyu
	 * 当服务端地址发生改变时触发的槽函数
	 */
	void slotSrvEditFinished(QString);

	/*!
	 * @brief 新的客户端接入
	 * @return void
	 * @since 2020/2/14 FanKaiyu
	 * 当有新的客户端请求接入时触发的槽函数
	 */
	void slotNewConnection();

	/*!
	 * @brief 接收异常
	 * @arg QAbstractSocket::SocketError 异常信息
	 * @return void
	 * @since 2020/2/14 FanKaiyu
	 * 当服务端发生接收异常时触发的槽函数
	 */
	void slotSrvAcceptError(QAbstractSocket::SocketError);

	/*!
	 * @brief 储存配置信息
	 * @return void
	 * @since 2020/2/14 FanKaiyu
	 * 将配置信心转换为JSON格式并写入文档
	 */
	void slotSave();

	/*!
	 * @brief 连接数据库
	 * @arg bool
	 * @return void
	 * @since 2020/2/16 FanKaiyu
	 * 创建数据库表，读取数据库信息。
	 */
	void slotLinkDatabase(bool&);

	/*!
	 * @brief 关闭数据库
	 * @return void
	 * @since 2020/2/16 FanKaiyu
	 * 终端与数据库的连接
	 */
	void slotCloseDatabase();

	/*!
	 * @brief 添加新的分盘机
	 * @arg bool& 添加成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 添加分盘机按钮释放时触发的槽函数
	 */
	void slotAddNewDischarger(bool&);

	/*!
	 * @brief 删除分盘机
	 * @arg bool& 删除成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 删除分盘机按钮释放时触发的槽函数
	 */
	void slotDeleteDischarger(bool&);

	/*!
	 * @brief 编辑分盘机
	 * @arg bool& 修改成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 修改分盘机按钮释放时触发的槽函数
	 */
	void slotEditDischarger(bool&);

	/*!
	 * @brief 添加新的分捡台
	 * @arg bool& 添加成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 添加分捡台按钮释放时触发的槽函数
	 */
	void slotAddNewSortTable(bool&);

	/*!
	 * @brief 删除分捡台
	 * @arg bool& 删除成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 删除分捡台按钮释放时触发的槽函数
	 */
	void slotDeleteSortTable(bool&);

	/*!
	 * @brief 编辑分捡台
	 * @arg bool& 修改成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 编辑分捡台按钮释放时触发的槽函数
	 */
	void slotEditSortTable(bool&);

	/*!
	 * @brief 添加出货口
	 * @arg bool& 添加成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 添加出货口按钮释放时触发的槽函数
	 */
	void slotAddNewShipmentPort(bool&);

	/*!
	 * @brief 删除出货口
	 * @arg bool& 删除成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 删除出货口按钮释放时触发的槽函数
	 */
	void slotDeleteShipmentPort(bool&);

	/*!
	 * @brief 编辑出货口
	 * @arg bool& 修改成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 编辑出货口按钮释放时触发的槽函数
	 */
	void slotEditShipmentPort(bool&);

	/*!
	 * @brief 添加订单
	 * @arg bool& 添加成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 添加订单按钮释放时触发的槽函数
	 */
	void slotAddNewOrder(bool&);

	/*!
	 * @brief 删除订单
	 * @arg bool& 删除成功返回true,否则返回false
	 * @return void
	 * @since 2020/2/24 FanKaiyu
	 * 删除订单按钮释放时触发的槽函数
	 */
	void slotDeleteOrder(bool&);
};
