#include "WCSSimulator.h"

#include <QLayout>
#include <QGroupBox>

WCSSimulator::WCSSimulator(QWidget* parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	Initialize();
}

void WCSSimulator::Initialize()
{
	QWidget* _wMain = new QWidget(this);													/*!< 主窗口中心控件 */
	ServerForm* _wServer = new ServerForm(_wMain);											/*!< 服务端控件 */
	DischargerForm* _wDischarger = new DischargerForm(_wMain);								/*!< 分盘机控件 */
	SortTableForm* _wSortTable = new SortTableForm(_wMain);									/*!< 分拣台控件 */
	ShipmentPortForm* _wShipment = new ShipmentPortForm(_wMain);							/*!< 出货口控件 */
	OrderForm* _wOrder = new OrderForm(_wMain);												/*!< 订单详情控件 */

	QGroupBox* _groupServer = new QGroupBox(QString::fromLocal8Bit("服务端"), this);		/*!< 服务端分组框 */
	QGroupBox* _groupDischarger = new QGroupBox(QString::fromLocal8Bit("分盘机"), this);	/*!< 分盘机分组框 */
	QGroupBox* _groupSort = new QGroupBox(QString::fromLocal8Bit("分拣台"), this);			/*!< 分拣台分组框 */
	QGroupBox* _groupShipment = new QGroupBox(QString::fromLocal8Bit("出库口"), this);		/*!< 出货口分组框 */
	QGroupBox* _groupOrder = new QGroupBox(QString::fromLocal8Bit("订单详情"), this);		/*!< 订单详情分组框 */

	//QTableView* _tableOrder = new QTableView(this);											/*!< 订单详情表单控件 */

	QHBoxLayout* _layGroupServer = new QHBoxLayout();										/*!< 服务端分组框布局 */
	QHBoxLayout* _layGroupDischarger = new QHBoxLayout();									/*!< 分盘机分组框布局 */
	QHBoxLayout* _layGroupSort = new QHBoxLayout();											/*!< 分拣台分组框布局 */
	QHBoxLayout* _layGroupShipment = new QHBoxLayout();										/*!< 出库口分组框布局 */
	QHBoxLayout* _layGroupOrder = new QHBoxLayout();										/*!< 订单详情分组框布局 */

	QGridLayout* _layGroup = new QGridLayout();												/*!< 设备信息控件布局 */

	QVBoxLayout* _layMain = new QVBoxLayout();												/*!< 主窗口全局布局 */

	// 为分组框布局添加控件
	_layGroupServer->addWidget(_wServer);
	_layGroupDischarger->addWidget(_wDischarger);
	_layGroupSort->addWidget(_wSortTable);
	_layGroupShipment->addWidget(_wShipment);
	_layGroupOrder->addWidget(_wOrder);

	// 为分组框添加布局
	_groupServer->setLayout(_layGroupServer);
	_groupDischarger->setLayout(_layGroupDischarger);
	_groupSort->setLayout(_layGroupSort);
	_groupShipment->setLayout(_layGroupShipment);
	_groupOrder->setLayout(_layGroupOrder);

	// 为设备信息控件布局添加控件
	_layGroup->addWidget(_groupDischarger, 0, 0);
	_layGroup->addWidget(_groupSort, 0, 1);
	_layGroup->addWidget(_groupShipment, 0, 2);

	// 设置分组框布局比例
	//_layGroup->setColumnStretch(0, 2);
	//_layGroup->setColumnStretch(1, 0);
	//_layGroup->setColumnStretch(2, 0);
	//_layGroup->setColumnStretch(3, 2);

	// 为主窗口布局添加控件
	// 添加服务端属性配置控件
	_layMain->addWidget(_groupServer);
	_layMain->addLayout(_layGroup);
	_layMain->addWidget(_groupOrder);

	// 为主窗口添加布局
	_wMain->setLayout(_layMain);

	// 设置主窗口中的中心控件
	setCentralWidget(_wMain);

	// 修改主窗口标题
	setWindowTitle(QString::fromLocal8Bit("WCS模拟器"));

	// 设置主窗口的最小尺寸
	setMinimumSize(1024, 720);

	// 为分组框设置外观样式
	//_groupServer->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	//_groupDischarger->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	//_groupSort->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	//_groupShipment->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	//_groupOrder->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	return;
}
