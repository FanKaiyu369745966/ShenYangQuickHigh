#include "WCSSimulator.h"

#include <QLayout>
#include <QGroupBox>
#include <QDir>
#include <QMessageBox>
#include <chrono>
#include <ctime>
#include <QCloseEvent>
#include <QJsonObject>
#include <QJsonDocument>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>

WCSSimulator::WCSSimulator(QWidget* parent)
	: QMainWindow(parent)
	, m_wServer(nullptr)
	, m_wDatabase(nullptr)
	, m_wDischarger(nullptr)
	, m_wSortTable(nullptr)
	, m_server(nullptr)
	, m_database(QSqlDatabase::addDatabase("QODBC3"))
	, m_nCount(0)
{
	//ui.setupUi(this);

	m_timer.setInterval(1000);

	moveToThread(&m_thread);
	m_thread.start();

	QObject::connect(&m_timer, &QTimer::timeout, this, &WCSSimulator::slotThread);

	m_timer.start();

	Initialize();


}

void WCSSimulator::Initialize()
{
	// 读取配置信息
	QString _srvAddr = "", _dbHost = "", _dbName = "", _dbUser = "", _dbPwd = "";

	QFile _fileSrvConfig("Config/Config.ini");

	// 清空文件中的数据，若没有文件，则创建文件 并打开文件
	if (_fileSrvConfig.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QJsonDocument _jdoc = QJsonDocument::fromJson(_fileSrvConfig.readAll());
		QJsonObject _jobjRoot = _jdoc.object();

		QJsonObject _jobjSrv = _jobjRoot.value("Server").toObject();
		QJsonObject _jobjDb = _jobjRoot.value("Database").toObject();

		_srvAddr = _jobjSrv.value("Address").toString();
		_dbHost = _jobjDb.value("Host").toString();
		_dbName = _jobjDb.value("DatabaseName").toString();
		_dbUser = _jobjDb.value("User").toString();
		_dbPwd = _jobjDb.value("Password").toString();
	}

	// 初始化子控件

	QWidget* _wMain = new QWidget(this);														/*!< 主窗口中心控件 */
	m_wDatabase = new DatabaseForm(_dbHost, _dbName, _dbUser, _dbPwd, _wMain);				/*!< 数据库控件 */
	m_wServer = new ServerForm(_srvAddr, _wMain);											/*!< 服务端控件 */
	m_wDischarger = new DischargerForm(_wMain);												/*!< 分盘机控件 */
	m_wSortTable = new SortTableForm(_wMain);												/*!< 分拣台控件 */
	m_wShipment = new ShipmentPortForm(_wMain);												/*!< 出货口控件 */
	m_wOrder = new OrderForm(_wMain);														/*!< 订单详情控件 */

	QGroupBox* _groupDatabase = new QGroupBox(QString::fromLocal8Bit("数据库"), this);		/*!< 数据库分组框 */
	QGroupBox* _groupServer = new QGroupBox(QString::fromLocal8Bit("服务端"), this);			/*!< 服务端分组框 */
	QGroupBox* _groupDischarger = new QGroupBox(QString::fromLocal8Bit("分盘机"), this);		/*!< 分盘机分组框 */
	QGroupBox* _groupSort = new QGroupBox(QString::fromLocal8Bit("分拣台"), this);			/*!< 分拣台分组框 */
	QGroupBox* _groupShipment = new QGroupBox(QString::fromLocal8Bit("出库口"), this);		/*!< 出货口分组框 */
	QGroupBox* _groupOrder = new QGroupBox(QString::fromLocal8Bit("订单详情"), this);		/*!< 订单详情分组框 */

	//QTableView* _tableOrder = new QTableView(this);											/*!< 订单详情表单控件 */

	QHBoxLayout* _layGroupDatabase = new QHBoxLayout();										/*!< 数据库分组框布局 */
	QHBoxLayout* _layGroupServer = new QHBoxLayout();										/*!< 服务端分组框布局 */
	QHBoxLayout* _layGroupDischarger = new QHBoxLayout();									/*!< 分盘机分组框布局 */
	QHBoxLayout* _layGroupSort = new QHBoxLayout();											/*!< 分拣台分组框布局 */
	QHBoxLayout* _layGroupShipment = new QHBoxLayout();										/*!< 出库口分组框布局 */
	QHBoxLayout* _layGroupOrder = new QHBoxLayout();										/*!< 订单详情分组框布局 */

	QGridLayout* _layGroup = new QGridLayout();												/*!< 设备信息控件布局 */

	QVBoxLayout* _layMain = new QVBoxLayout();												/*!< 主窗口全局布局 */

	// 为分组框布局添加控件
	_layGroupDatabase->addWidget(m_wDatabase);
	_layGroupServer->addWidget(m_wServer);
	_layGroupDischarger->addWidget(m_wDischarger);
	_layGroupSort->addWidget(m_wSortTable);
	_layGroupShipment->addWidget(m_wShipment);
	_layGroupOrder->addWidget(m_wOrder);

	// 为分组框添加布局
	_groupDatabase->setLayout(_layGroupDatabase);
	_groupServer->setLayout(_layGroupServer);
	_groupDischarger->setLayout(_layGroupDischarger);
	_groupSort->setLayout(_layGroupSort);
	_groupShipment->setLayout(_layGroupShipment);
	_groupOrder->setLayout(_layGroupOrder);

	// 为设备信息控件布局添加控件
	_layGroup->addWidget(_groupDischarger, 0, 0, 1, 2);
	_layGroup->addWidget(_groupSort, 1, 0);
	_layGroup->addWidget(_groupShipment, 1, 1);

	// 设置分组框布局比例
	//_layGroup->setColumnStretch(0, 2);
	//_layGroup->setColumnStretch(1, 0);
	//_layGroup->setColumnStretch(2, 0);
	//_layGroup->setColumnStretch(3, 2);

	// 为主窗口布局添加控件
	// 添加服务端属性配置控件
	_layMain->addWidget(_groupDatabase);
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

	// 为控件添加信号和槽函数
	QObject::connect(m_wServer, &ServerForm::signalListen, this, &WCSSimulator::slotStartListen);
	QObject::connect(m_wServer, &ServerForm::signalClose, this, &WCSSimulator::slotEndListen);
	QObject::connect(m_wDatabase, &DatabaseForm::OnButtonLink, this, &WCSSimulator::slotLinkDatabase);
	QObject::connect(m_wDatabase, &DatabaseForm::OnButtonClose, this, &WCSSimulator::slotCloseDatabase);

	QObject::connect(m_wDischarger, static_cast<void (DischargerForm::*)(bool&)>(&DischargerForm::AddNewDischarger), this, &WCSSimulator::slotAddNewDischarger);
	QObject::connect(m_wDischarger, static_cast<void (DischargerForm::*)(bool&)>(&DischargerForm::DeleteDischarger), this, &WCSSimulator::slotDeleteDischarger);
	QObject::connect(m_wDischarger, static_cast<void (DischargerForm::*)(bool&)>(&DischargerForm::EditDischarger), this, &WCSSimulator::slotEditDischarger);

	QObject::connect(m_wSortTable, static_cast<void (SortTableForm::*)(bool&)>(&SortTableForm::AddNewSortTable), this, &WCSSimulator::slotAddNewSortTable);
	QObject::connect(m_wSortTable, static_cast<void (SortTableForm::*)(bool&)>(&SortTableForm::DeleteSortTable), this, &WCSSimulator::slotDeleteSortTable);
	QObject::connect(m_wSortTable, static_cast<void (SortTableForm::*)(bool&)>(&SortTableForm::EditSortTable), this, &WCSSimulator::slotEditSortTable);

	QObject::connect(m_wShipment, static_cast<void (ShipmentPortForm::*)(bool&)>(&ShipmentPortForm::AddNewShipmentPort), this, &WCSSimulator::slotAddNewShipmentPort);
	QObject::connect(m_wShipment, static_cast<void (ShipmentPortForm::*)(bool&)>(&ShipmentPortForm::DeleteShipmentPort), this, &WCSSimulator::slotDeleteShipmentPort);
	QObject::connect(m_wShipment, static_cast<void (ShipmentPortForm::*)(bool&)>(&ShipmentPortForm::EditShipmentPort), this, &WCSSimulator::slotEditShipmentPort);

	QObject::connect(m_wOrder, static_cast<void (OrderForm::*)(bool&)>(&OrderForm::AddNewOrder), this, &WCSSimulator::slotAddNewOrder);
	QObject::connect(m_wOrder, static_cast<void (OrderForm::*)(bool&)>(&OrderForm::DeleteOrder), this, &WCSSimulator::slotDeleteOrder);

	// 创建子目录
	QDir _dir(".");
	QDir _dirLog("Log");
	QDir _dirConfig("Config");

	// 创建日志存放目录
	if (_dirLog.exists() == false)
	{
		_dir.mkdir("Log");
	}

	// 创建配置存放目录
	if (_dirConfig.exists() == false)
	{
		_dir.mkdir("Config");
	}

	// 创建服务端log文件
	QFile _fileSrvLog("Log/Server.log");

	// 保留文件中的数据并打开文件
	//if (_fileSrvLog.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::OpenModeFlag::Append))

	// 清空文件中的数据，若没有文件，则创建文件 并打开文件
	if (_fileSrvLog.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		_fileSrvLog.close();
	}

	// 创建服务端
	m_server = new QTcpServer(this);

	// 为服务端添加信号和槽函数
	QObject::connect(m_server, &QTcpServer::acceptError, this, &WCSSimulator::slotSrvAcceptError);
	QObject::connect(m_server, &QTcpServer::newConnection, this, &WCSSimulator::slotNewConnection);
	QObject::connect(m_server, &QTcpServer::newConnection, this, &WCSSimulator::slotNewConnection);

	return;
}

QString WCSSimulator::GetCurrentTime()
{
	using namespace std;

	chrono::system_clock::time_point tpCur = chrono::system_clock::now();

	time_t tt = chrono::system_clock::to_time_t(tpCur);
	tm* t = localtime(&tt);

	auto timeNow = chrono::duration_cast<chrono::milliseconds>(tpCur.time_since_epoch());

	QString str = QString("%1/%2/%3 %4:%5:%6")
		.arg(t->tm_year + 1900, 4, 10, QLatin1Char('0'))
		.arg(t->tm_mon + 1, 2, 10, QLatin1Char('0'))
		.arg(t->tm_mday, 2, 10, QLatin1Char('0'))
		.arg(t->tm_hour, 2, 10, QLatin1Char('0'))
		.arg(t->tm_min, 2, 10, QLatin1Char('0'))
		.arg(t->tm_sec, 2, 10, QLatin1Char('0'));

	return str;
}

void WCSSimulator::closeEvent(QCloseEvent* event)
{
	m_thread.quit();
	m_thread.wait();
	m_timer.stop();

	slotSave();
	event->accept();

	return;
}

void WCSSimulator::InitDatabase()
{
	QSqlQuery _query(m_database);

	// 创建数据库表

	// 创建分盘机表单
	QString _sql = QString::fromLocal8Bit("\
Create Table WCS_INFO_DISCHARGER(\
disc_no int not null primary key,\
disc_addr nvarchar(50) not null,\
disc_port int not null default 0,\
disc_client bit not null default 1,\
disc_status int not null default 0,\
disc_request bit not null default 0,\
disc_order nvarchar(50) null\
); \
");

	if (_query.exec(_sql) == false)
	{
		qDebug() << QString::fromLocal8Bit("创建WCS_INFO_DISCHARGER表单失败：") << _query.lastError().text();
	}

	// 创建分捡台表单
	_sql = QString::fromLocal8Bit("\
Create Table WCS_INFO_SORTTABLE(\
table_no int not null primary key,\
table_name nvarchar(50) not null,\
);\
");

	if (_query.exec(_sql) == false)
	{
		qDebug() << QString::fromLocal8Bit("创建WCS_INFO_SORTTABLE表单失败：") << _query.lastError().text();
	}

	// 创建出货口表单
	_sql = QString::fromLocal8Bit("\
Create Table WCS_INFO_SHIPMENTPORT(\
port_no int not null primary key,\
port_name nvarchar(50) not null,\
port_full bit not null default 0,\
);\
");

	if (_query.exec(_sql) == false)
	{
		qDebug() << QString::fromLocal8Bit("创建WCS_INFO_SHIPMENTPORT表单失败：") << _query.lastError().text();
	}

	// 创建CHECK

	_sql = QString::fromLocal8Bit("ALTER Table WCS_INFO_DISCHARGER add CONSTRAINT chk_disc_no check(disc_no>0 and disc_no<255);");

	if (_query.exec(_sql) == false)
	{
		qDebug() << _query.lastError().text();
	}

	_sql = QString::fromLocal8Bit("ALTER Table WCS_INFO_DISCHARGER add CONSTRAINT chk_disc_port check(disc_port>-1 and disc_no<65536);");

	if (_query.exec(_sql) == false)
	{
		qDebug() << _query.lastError().text();
	}

	_sql = QString::fromLocal8Bit("ALTER Table WCS_INFO_SORTTABLE add CONSTRAINT chk_table_no check(table_no>0 and table_no<255);");

	if (_query.exec(_sql) == false)
	{
		qDebug() << _query.lastError().text();
	}

	_sql = QString::fromLocal8Bit("ALTER Table WCS_INFO_SHIPMENTPORT add CONSTRAINT chk_port_no check(port_no>0 and port_no<255);");

	if (_query.exec(_sql) == false)
	{
		qDebug() << _query.lastError().text();
	}

	// 创建约束

	_sql = QString::fromLocal8Bit("ALTER Table WCS_INFO_SORTTABLE add CONSTRAINT uc_table_name unique (table_name);");

	if (_query.exec(_sql) == false)
	{
		qDebug() << _query.lastError().text();
	}

	_sql = QString::fromLocal8Bit("ALTER Table WCS_INFO_SHIPMENTPORT add CONSTRAINT uc_port_name unique (port_name);");

	if (_query.exec(_sql) == false)
	{
		qDebug() << _query.lastError().text();
	}

	// 读取数据库中的数据
	LoadDatabase();

	return;
}

void WCSSimulator::LoadDatabase()
{
	m_wDischarger->Clear();
	m_wSortTable->Clear();
	m_wShipment->Clear();

	// 删除分盘机
	for (QMap<quint8, Discharger*>::iterator it = m_mapDischarger.begin(); it != m_mapDischarger.end(); it = m_mapDischarger.erase(it))
	{
		it.value()->Disconnect();

		it.value()->deleteLater();
	}

	QSqlQuery _query(m_database);

	QString _sql = "select * from WCS_INFO_DISCHARGER order by disc_no";

	if (_query.exec(_sql))
	{
		while (_query.next())
		{
			quint8 _no = _query.value("disc_no").toInt();
			QString _addr = _query.value("disc_addr").toString();
			quint16 _port = _query.value("disc_port").toInt();
			bool _client = _query.value("disc_client").toBool();
			quint8 _status = _query.value("disc_status").toInt();
			bool _request = _query.value("disc_request").toBool();
			QString _order = _query.value("disc_request").toString();

			// 添加分盘机
			if (m_mapDischarger.find(_no) != m_mapDischarger.end())
			{
				continue;
			}

			m_mapDischarger[_no] = new Discharger(_no, _addr, _port, _client, _order, _request, this);

			QObject::connect(m_mapDischarger[_no], &Discharger::Update, this, &WCSSimulator::slotUpdateDischarger);

			m_wDischarger->AddNewDischarger(_no, _addr, _port, _client);
			m_wDischarger->Update(_no, _status);
			m_wDischarger->Update(_no, _request, _order);
		}
	}

	_sql = "select * from WCS_INFO_SORTTABLE order by table_no";

	if (_query.exec(_sql))
	{
		while (_query.next())
		{
			quint8 _no = _query.value("table_no").toInt();
			QString _name = _query.value("table_name").toString();

			m_wSortTable->AddNewSortTable(_no, _name);
			m_wOrder->AddNewSortTable(_no, _name);
		}
	}

	_sql = "select * from WCS_INFO_SHIPMENTPORT order by port_no";

	if (_query.exec(_sql))
	{
		while (_query.next())
		{
			quint8 _no = _query.value("port_no").toInt();
			QString _name = _query.value("port_name").toString();
			bool _full = _query.value("port_full").toBool();

			m_wShipment->AddNewShipmentPort(_no, _name, _full);
		}
	}

	m_wOrder->UpdateData();

	return;
}

void WCSSimulator::slotStartListen(bool& listened)
{
	QString _curTime = GetCurrentTime();

	QFile _fileSrvLog("Log/Server.log");

	_fileSrvLog.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::OpenModeFlag::Append);

	//_fileSrvLog.(SEEK_END);

	QTextStream _out(&_fileSrvLog);

	QString _addr(m_wServer->m_addr.section(':', 0, -2));
	quint16 _port = static_cast<quint16>(m_wServer->m_addr.section(':', -1, -1).toUInt());

	QHostAddress _host;

	if (_host.setAddress(_addr) == false || _port == 0 || _port > 65535)
	{
		listened = false;

		QMessageBox::critical(this, QString::fromLocal8Bit("服务端监听"), QString::fromLocal8Bit("监听启动失败！无效的地址信息"));

		_out << QString::fromLocal8Bit("%1 监听启动失败！无效的地址信息").arg(_curTime) << endl;

		_fileSrvLog.close();

		return;
	}

	if (m_server == nullptr)
	{
		m_server = new QTcpServer(this);

		QObject::connect(m_server, &QTcpServer::acceptError, this, &WCSSimulator::slotSrvAcceptError);
		QObject::connect(m_server, &QTcpServer::newConnection, this, &WCSSimulator::slotNewConnection);
	}

	if (m_server->isListening())
	{
		if (m_server->serverAddress().toString() == _addr && m_server->serverPort() == _port)
		{
			listened = true;

			return;
		}

		m_server->close();
	}

	listened = m_server->listen(_host, _port);

	// 向服务端日志中填写日志
	if (listened)
	{
		_out << QString::fromLocal8Bit("%1 监听启动").arg(_curTime) << endl;
	}
	else
	{
		_out << QString::fromLocal8Bit("%1 监听启动失败：").arg(_curTime) << m_server->errorString() << endl;
	}

	_fileSrvLog.close();

	return;
}

void WCSSimulator::slotEndListen()
{
	QString _curTime = GetCurrentTime();

	QFile _fileSrvLog("Log/Server.log");

	_fileSrvLog.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::OpenModeFlag::Append);

	//_fileSrvLog.seek(SEEK_END);

	QTextStream _out(&_fileSrvLog);

	if (m_server == nullptr)
	{
		_fileSrvLog.close();

		return;
	}

	if (m_server->isListening())
	{
		m_server->close();

		_out << QString::fromLocal8Bit("%1 监听关闭").arg(_curTime) << endl;
	}

	_fileSrvLog.close();

	return;
}

void WCSSimulator::slotSrvEditFinished(QString addr)
{
	QString _curTime = GetCurrentTime();

	QFile _fileSrvLog("Log/Server.log");

	_fileSrvLog.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::OpenModeFlag::Append);

	//_fileSrvLog.seek(SEEK_END);

	QTextStream _out(&_fileSrvLog);

	_out << QString::fromLocal8Bit("%1 修改地址信息为：[%2]").arg(_curTime).arg(addr) << endl;

	_fileSrvLog.close();

	return;

}

void WCSSimulator::slotNewConnection()
{
	QString _curTime = GetCurrentTime();

	QFile _fileSrvLog("Log/Server.log");

	_fileSrvLog.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::OpenModeFlag::Append);

	//_fileSrvLog.(SEEK_END);

	QTextStream _out(&_fileSrvLog);

	while (m_server->hasPendingConnections())
	{
		QTcpSocket* _socket = m_server->nextPendingConnection();

		_out << QString::fromLocal8Bit("%1 连线客户端：[%2:%3]").arg(_curTime).arg(_socket->peerAddress().toString()).arg(_socket->peerPort()) << endl;

		// 连接分盘机
		bool _connected = false;

		for (QMap<quint8, Discharger*>::iterator it = m_mapDischarger.begin(); it != m_mapDischarger.end(); ++it)
		{
			if (it.value()->Connect(_socket) == false)
			{
				continue;
			}

			_connected = true;

			break;
		}

		if (_connected == false)
		{
			_out << QString::fromLocal8Bit("%1 客户端：[%2:%3]离线").arg(_curTime).arg(_socket->peerAddress().toString()).arg(_socket->peerPort()) << endl;

			_socket->close();
		}
	}

	_fileSrvLog.close();

	return;
}

void WCSSimulator::slotSrvAcceptError(QAbstractSocket::SocketError error)
{
	QString _curTime = GetCurrentTime();

	QFile _fileSrvLog("Log/Server.log");

	_fileSrvLog.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::OpenModeFlag::Append);

	//_fileSrvLog.(SEEK_END);

	QTextStream _out(&_fileSrvLog);

	_out << QString::fromLocal8Bit("%1 异常：%2").arg(_curTime).arg(m_server->errorString()) << endl;

	_fileSrvLog.close();

	if (m_wServer->m_listened)
	{
		m_wServer->slotReleaseListenButton();
	}

	switch (error)
	{
	case QAbstractSocket::ConnectionRefusedError:
		break;
	case QAbstractSocket::RemoteHostClosedError:
		break;
	case QAbstractSocket::HostNotFoundError:
		break;
	case QAbstractSocket::SocketAccessError:
		break;
	case QAbstractSocket::SocketResourceError:
		break;
	case QAbstractSocket::SocketTimeoutError:
		break;
	case QAbstractSocket::DatagramTooLargeError:
		break;
	case QAbstractSocket::NetworkError:
		break;
	case QAbstractSocket::AddressInUseError:
		break;
	case QAbstractSocket::SocketAddressNotAvailableError:
		break;
	case QAbstractSocket::UnsupportedSocketOperationError:
		break;
	case QAbstractSocket::UnfinishedSocketOperationError:
		break;
	case QAbstractSocket::ProxyAuthenticationRequiredError:
		break;
	case QAbstractSocket::SslHandshakeFailedError:
		break;
	case QAbstractSocket::ProxyConnectionRefusedError:
		break;
	case QAbstractSocket::ProxyConnectionClosedError:
		break;
	case QAbstractSocket::ProxyConnectionTimeoutError:
		break;
	case QAbstractSocket::ProxyNotFoundError:
		break;
	case QAbstractSocket::ProxyProtocolError:
		break;
	case QAbstractSocket::OperationError:
		break;
	case QAbstractSocket::SslInternalError:
		break;
	case QAbstractSocket::SslInvalidUserDataError:
		break;
	case QAbstractSocket::TemporaryError:
		break;
	case QAbstractSocket::UnknownSocketError:
		break;
	}

	return;
}

void WCSSimulator::slotSave()
{
	// 储存配置信息

	QJsonObject	_jobjRoot, _jobjSrv, _jobjDb;

	_jobjSrv.insert("Address", m_wServer->m_addr);

	_jobjDb.insert("Host", m_wDatabase->m_strHost);
	_jobjDb.insert("DatabaseName", m_wDatabase->m_strDbName);
	_jobjDb.insert("User", m_wDatabase->m_strUser);
	_jobjDb.insert("Password", m_wDatabase->m_strPassword);

	_jobjRoot.insert("Server", _jobjSrv);
	_jobjRoot.insert("Database", _jobjDb);

	// 创建配置文件
	QFile _fileSrvConfig("Config/Config.ini");

	// 清空文件中的数据，若没有文件，则创建文件 并打开文件
	if (_fileSrvConfig.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		_fileSrvConfig.write(QJsonDocument(_jobjRoot).toJson());
	}

	return;
}

void WCSSimulator::slotLinkDatabase(bool& linked)
{
	if (m_wDatabase->m_strHost.isNull() || m_wDatabase->m_strHost.isEmpty()
		|| m_wDatabase->m_strDbName.isNull() || m_wDatabase->m_strDbName.isEmpty()
		|| m_wDatabase->m_strUser.isNull() || m_wDatabase->m_strUser.isEmpty())
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("数据库连接"), QString::fromLocal8Bit("数据库连接失败！主机名、数据库名称、用户名不能为空"));

		return;
	}

	if (m_database.isOpen())
	{
		m_database.close();

		m_wOrder->CloseDatabase();
	}

	m_database.setDatabaseName(QString("DRIVER={SQL SERVER};"
		"SERVER=%1;"
		"DATABASE=%2;"
		"UID=%3;"
		"PWD=%4;").arg(m_wDatabase->m_strHost).arg(m_wDatabase->m_strDbName).arg(m_wDatabase->m_strUser).arg(m_wDatabase->m_strPassword));

	linked = m_database.open();

	if (linked == false)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("数据库连接"), QString::fromLocal8Bit("数据库连接失败！%1").arg(m_database.lastError().text()));

		return;
	}

	m_wOrder->OpenDatabase(m_wDatabase->m_strHost, m_wDatabase->m_strDbName, m_wDatabase->m_strUser, m_wDatabase->m_strPassword);

	InitDatabase();

	return;
}

void WCSSimulator::slotCloseDatabase()
{
	if (m_database.isOpen())
	{
		m_database.close();

		m_wOrder->CloseDatabase();
	}

	return;
}

void WCSSimulator::slotAddNewDischarger(bool& result)
{
	// 将数据添加进数据库表中
	QSqlQuery _query(m_database);

	QString _addr(m_wDischarger->m_strAddr.section(':', 0, -2));
	quint16 _port = static_cast<quint16>(m_wDischarger->m_strAddr.section(':', -1, -1).toUInt());

	QString _sql = QString("insert into WCS_INFO_DISCHARGER(disc_no,disc_addr,disc_port,disc_client) values(%1,'%2',%3,%4)")
		.arg(m_wDischarger->m_byNo)
		.arg(_addr)
		.arg(_port)
		.arg(m_wDischarger->m_bClient);

	result = _query.exec(_sql);

	if (result == false)
	{
		qDebug() << "insert into WCS_INFO_DISCHARGER failed:" << _query.lastError().text();

		QMessageBox::critical(this, QString::fromLocal8Bit("添加分盘机"), QString::fromLocal8Bit("添加分盘机失败！已存在相同的编号。\n%1")
			.arg(_query.lastError().text()));

		return;
	}

	// 添加分盘机
	if (m_mapDischarger.find(m_wDischarger->m_byNo) != m_mapDischarger.end())
	{
		m_mapDischarger[m_wDischarger->m_byNo]->SetAddress(m_wDischarger->m_strAddr);
		m_mapDischarger[m_wDischarger->m_byNo]->SetMode(m_wDischarger->m_bClient);

		return;
	}

	m_mapDischarger[m_wDischarger->m_byNo] = new Discharger(m_wDischarger->m_byNo, _addr, _port, m_wDischarger->m_bClient, "", false, this);

	QObject::connect(m_mapDischarger[m_wDischarger->m_byNo], &Discharger::Update, this, &WCSSimulator::slotUpdateDischarger);

	return;
}

void WCSSimulator::slotDeleteDischarger(bool& result)
{
	// 将数据从数据库表中删除
	QSqlQuery _query(m_database);

	QString _sql = QString("delete from WCS_INFO_DISCHARGER where disc_no=%1").arg(m_wDischarger->m_byNo);

	result = _query.exec(_sql);

	if (result == false)
	{
		qDebug() << "delete from WCS_INFO_DISCHARGER failed:" << _query.lastError().text();
		return;
	}

	// 删除分盘机
	if (m_mapDischarger.find(m_wDischarger->m_byNo) == m_mapDischarger.end())
	{
		return;
	}

	m_mapDischarger[m_wDischarger->m_byNo]->Disconnect();
	m_mapDischarger[m_wDischarger->m_byNo]->deleteLater();

	m_mapDischarger.erase(m_mapDischarger.find(m_wDischarger->m_byNo));

	return;
}

void WCSSimulator::slotEditDischarger(bool& result)
{
	// 修改数据表中的数据
	QSqlQuery _query(m_database);

	QString _addr(m_wDischarger->m_strAddr.section(':', 0, -2));
	quint16 _port = static_cast<quint16>(m_wDischarger->m_strAddr.section(':', -1, -1).toUInt());

	QString _sql = QString("update WCS_INFO_DISCHARGER set disc_addr='%1',disc_port=%2,disc_client=%3 where disc_no=%4")
		.arg(_addr)
		.arg(_port)
		.arg(m_wDischarger->m_bClient)
		.arg(m_wDischarger->m_byNo);

	result = _query.exec(_sql);

	if (result == false)
	{
		qDebug() << "update WCS_INFO_DISCHARGER failed:" << _query.lastError().text();
		return;
	}

	// 修改分盘机属性
	if (m_mapDischarger.find(m_wDischarger->m_byNo) == m_mapDischarger.end())
	{
		return;
	}

	m_mapDischarger[m_wDischarger->m_byNo]->SetAddress(m_wDischarger->m_strAddr);
	m_mapDischarger[m_wDischarger->m_byNo]->SetMode(m_wDischarger->m_bClient);

	return;
}

void WCSSimulator::slotAddNewSortTable(bool& result)
{
	// 将数据添加进数据库表中
	QSqlQuery _query(m_database);

	QString _sql = QString("if not exists(select * from WCS_INFO_SHIPMENTPORT where port_name='%1')\
 insert into WCS_INFO_SORTTABLE(table_no,table_name) values(%2,'%3')")
		.arg(m_wSortTable->m_strName)
		.arg(m_wSortTable->m_byNo)
		.arg(m_wSortTable->m_strName);

	_query.exec(_sql);

	if (_query.numRowsAffected() > 0)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	if (result == false)
	{
		qDebug() << "insert into WCS_INFO_SORTTABLE failed:" << _query.lastError().text();

		QMessageBox::critical(this, QString::fromLocal8Bit("添加分捡台"), QString::fromLocal8Bit("添加分捡台失败！已存在相同的编号或名称。\n%1")
			.arg(_query.lastError().text()));

		return;
	}

	m_wOrder->AddNewSortTable(m_wSortTable->m_byNo, m_wSortTable->m_strName);

	return;
}

void WCSSimulator::slotDeleteSortTable(bool& result)
{
	// 将数据从数据库表中删除
	QSqlQuery _query(m_database);

	QString _sql = QString("delete from WCS_INFO_SORTTABLE where table_no=%1")
		.arg(m_wSortTable->m_byNo);

	result = _query.exec(_sql);

	if (result == false)
	{
		qDebug() << "delete from WCS_INFO_SORTTABLE failed:" << _query.lastError().text();
		return;
	}

	m_wOrder->DeleteSortTable(m_wSortTable->m_byNo);

	return;
}

void WCSSimulator::slotEditSortTable(bool& result)
{
	// 修改数据表中的数据
	QSqlQuery _query(m_database);

	QString _sql = QString("if not exists(select * from WCS_INFO_SHIPMENTPORT where port_name='%1')\
 update WCS_INFO_SORTTABLE set table_name='%2' where table_no=%3")
		.arg(m_wSortTable->m_strName)
		.arg(m_wSortTable->m_strName)
		.arg(m_wSortTable->m_byNo);

	_query.exec(_sql);

	if (_query.numRowsAffected() > 0)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	if (result == false)
	{
		qDebug() << "update WCS_INFO_SORTTABLE failed:" << _query.lastError().text();

		QMessageBox::critical(this, QString::fromLocal8Bit("编辑分捡台"), QString::fromLocal8Bit("修改分捡台名称失败！已存在相同的或名称。\n%1")
			.arg(_query.lastError().text()));

		return;
	}

	return;
}

void WCSSimulator::slotAddNewShipmentPort(bool& result)
{
	// 将数据添加进数据库表中
	QSqlQuery _query(m_database);

	QString _sql = QString("if not exists(select * from WCS_INFO_SORTTABLE where table_name='%1')\
 insert into WCS_INFO_SHIPMENTPORT(port_no,port_name,port_full) values(%2,'%3',%4)")
		.arg(m_wShipment->m_strName)
		.arg(m_wShipment->m_byNo)
		.arg(m_wShipment->m_strName)
		.arg(m_wShipment->m_bFull);

	_query.exec(_sql);

	if (_query.numRowsAffected() > 0)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	if (result == false)
	{
		qDebug() << "insert into WCS_INFO_SHIPMENTPORT failed:" << _query.lastError().text();

		QMessageBox::critical(this, QString::fromLocal8Bit("添加出货口"), QString::fromLocal8Bit("添加出货口失败！已存在相同的编号或名称。\n%1")
			.arg(_query.lastError().text()));

		return;
	}

	return;
}

void WCSSimulator::slotDeleteShipmentPort(bool& result)
{
	// 将数据从数据库表中删除
	QSqlQuery _query(m_database);

	QString _sql = QString("delete from WCS_INFO_SHIPMENTPORT where port_no=%1")
		.arg(m_wShipment->m_byNo);

	result = _query.exec(_sql);

	if (result == false)
	{
		qDebug() << "delete from WCS_INFO_SHIPMENTPORT failed:" << _query.lastError().text();
		return;
	}

	return;
}

void WCSSimulator::slotEditShipmentPort(bool& result)
{
	// 修改数据表中的数据
	QSqlQuery _query(m_database);

	QString _sql = QString("if not exists(select * from WCS_INFO_SORTTABLE where table_name='%1')\
 update WCS_INFO_SHIPMENTPORT set port_name='%2',port_full=%3 where table_no=%4")
		.arg(m_wShipment->m_strName)
		.arg(m_wShipment->m_strName)
		.arg(m_wShipment->m_bFull)
		.arg(m_wShipment->m_byNo);

	_query.exec(_sql);

	if (_query.numRowsAffected() > 0)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	if (result == false)
	{
		qDebug() << "update WCS_INFO_SHIPMENTPORT failed:" << _query.lastError().text();

		QMessageBox::critical(this, QString::fromLocal8Bit("编辑出货口"), QString::fromLocal8Bit("修改出货口名称失败！已存在相同的或名称。\n%1")
			.arg(_query.lastError().text()));

		return;
	}

	return;
}

void WCSSimulator::slotAddNewOrder(bool& result)
{
	QSqlQuery _query(m_database);

	QString _sql = "";

	quint8 _discharger = 0;

	// 确定数据表中不包含当前订单号的订单
	_sql = QString::fromLocal8Bit("select * from AGVDB_TASK_CURRENT where task_order='%1'").arg(m_wOrder->m_strOrder);

	if (_query.exec(_sql) == false)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加订单"), QString::fromLocal8Bit("添加订单失败！查询订单表单失败。\n%1")
			.arg(_query.lastError().text()));

		return;
	}

	if (_query.next())
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加订单"), QString::fromLocal8Bit("添加订单失败！已经存在了相同的订单号码的订单。"));

		return;
	}

	// 确定分盘机的状态，并为订单分配分盘机
	for (int index = m_nCount + 1; ; ++index)
	{
		if (index == 255)
		{
			index = 0;
		}

		if (index == m_nCount)
		{
			break;
		}

		if (index == 0)
		{
			continue;
		}

		if (m_mapDischarger.find(index) == m_mapDischarger.end())
		{
			continue;
		}

		Discharger* _disc = m_mapDischarger[index];
		quint8 _status = _disc->GetStatus();

		if (_status == Discharger::NotReady || _disc->IsConnected() == false)
		{
			continue;
		}

		_discharger = index;
		m_nCount = _discharger;

		break;
	}

	// 创建订单
	if (_discharger == 0)
	{// 没有可分配的分盘机

		QMessageBox::critical(this, QString::fromLocal8Bit("添加订单"), QString::fromLocal8Bit("添加订单失败！未找到可用以分配的分盘机。"));

		return;
	}

	// 创建分盘机上料任务
	_sql = QString::fromLocal8Bit(
		"insert into AGVDB_TASK_CURRENT(task_order,task_tray,task_target,task_mission) values('%1','%2','%3','%4');")
		.arg(m_wOrder->m_strOrder)
		.arg(m_wOrder->m_strTray)
		.arg(QString::fromLocal8Bit("分盘机%1").arg(_discharger))
		.arg(QString::fromLocal8Bit("上料"));

	// 创建分拣机停靠任务
	for (QStringList::iterator it = m_wOrder->m_strlSortTable.begin(); it != m_wOrder->m_strlSortTable.end(); ++it)
	{
		QString _name = "";

		if (m_wSortTable->IsVaild((*it).toInt(), _name) == false)
		{
			QMessageBox::critical(this, QString::fromLocal8Bit("添加订单"), QString::fromLocal8Bit("添加订单失败！未找到分捡台%1。").arg(*it));

			return;
		}

		if (_name.isNull() || _name.isEmpty())
		{
			_name = QString::fromLocal8Bit("分捡台%1").arg(*it);
		}

		_sql += QString::fromLocal8Bit(
			"insert into AGVDB_TASK_CURRENT(task_order,task_tray,task_target,task_mission) values('%1','%2','%3','%4');")
			.arg(m_wOrder->m_strOrder)
			.arg(m_wOrder->m_strTray)
			.arg(_name)
			.arg(QString::fromLocal8Bit("停靠"));
	}

	// 创建出货口下料任务
	QString _name = "";
	bool _full = "";

	if (m_wShipment->IsVaild(m_wOrder->m_byShipmentPort, _name, _full) == false)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加订单"), QString::fromLocal8Bit("添加订单失败！未找到出货口。"));

		return;
	}

	if (_full)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加订单"), QString::fromLocal8Bit("添加订单失败！出货口已满载，无法使用。"));

		return;
	}

	if (_name.isNull() || _name.isEmpty())
	{
		_name = QString::fromLocal8Bit("出货口%1").arg(m_wOrder->m_byShipmentPort);
	}

	_sql += QString::fromLocal8Bit(
		"insert into AGVDB_TASK_CURRENT(task_order,task_tray,task_target,task_mission) values('%1','%2','%3','%4');")
		.arg(m_wOrder->m_strOrder)
		.arg(m_wOrder->m_strTray)
		.arg(_name)
		.arg(QString::fromLocal8Bit("下料"));

	// 创建结束任务
	_sql += QString::fromLocal8Bit(
		"insert into AGVDB_TASK_CURRENT(task_order,task_tray,task_target,task_mission) values('%1','%2','%3','%4');")
		.arg(m_wOrder->m_strOrder)
		.arg(m_wOrder->m_strTray)
		.arg(QString::fromLocal8Bit("无"))
		.arg(QString::fromLocal8Bit("结束"));

	result = _query.exec(_sql);

	if (result == false)
	{
		qDebug() << "insert into AGVDB_TASK_CURRENT failed:" << _query.lastError().text();

		QMessageBox::critical(this, QString::fromLocal8Bit("添加订单"), QString::fromLocal8Bit("添加订单失败！\n%1")
			.arg(_query.lastError().text()));

		return;
	}

	return;
}

void WCSSimulator::slotDeleteOrder(bool& result)
{
	// 将数据从数据库表中删除
	QSqlQuery _query(m_database);

	QString _sql = QString::fromLocal8Bit("update AGVDB_TASK_CURRENT set task_status='%1',task_finish=getdate() where task_order=%2")
		.arg(QString::fromLocal8Bit("取消订单"))
		.arg(m_wOrder->m_strOrder);

	result = _query.exec(_sql);

	if (result == false)
	{
		qDebug() << "update WCS_INFO_SHIPMENTPORT failed:" << _query.lastError().text();

		return;
	}

	return;
}

void WCSSimulator::slotThread()
{
	if (m_database.isOpen() == false)
	{
		return;
	}

	m_wOrder->UpdateData();

	QSqlQuery _query(QString::fromLocal8Bit("select * from AGVDB_TASK_CURRENT where task_mission='%1' and task_status='%2' order by task_publish")
		.arg(QString::fromLocal8Bit("上料"))
		.arg(QString::fromLocal8Bit("执行中"))
		, m_database);

	while (_query.next())
	{
		QString _order = _query.value("task_order").toString();
		QString _name = _query.value("task_target").toString();

		quint8 _no = _name.section(QString::fromLocal8Bit("分盘机"), -1, -1).toInt();

		if (m_mapDischarger.find(_no) == m_mapDischarger.end())
		{
			continue;
		}

		m_mapDischarger[_no]->RequestTray(_order);
	}

	return;
}

void WCSSimulator::slotUpdateDischarger(quint8 no)
{
	if (m_mapDischarger.find(no) == m_mapDischarger.end())
	{
		return;
	}

	QSqlQuery _query(m_database);

	QString _order = "";
	bool _request = m_mapDischarger[no]->IsRequested(_order);
	bool _connect = m_mapDischarger[no]->IsConnected();
	quint8 _status = m_mapDischarger[no]->GetStatus();

	QString _sql = QString("update WCS_INFO_DISCHARGER set disc_status=%1,disc_request=%2,disc_order='%3' where disc_no=%4")
		.arg(_status)
		.arg(_request)
		.arg(_order)
		.arg(no);

	if (_query.exec(_sql) == false)
	{
		qDebug() << "update WCS_INFO_DISCHARGER failed:" << _query.lastError().text();
		return;
	}

	m_wDischarger->Update(no, _status);
	m_wDischarger->Update(no, _connect);
	m_wDischarger->Update(no, _request, _order);

	return;
}
