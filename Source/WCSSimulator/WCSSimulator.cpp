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

WCSSimulator::WCSSimulator(QWidget* parent)
	: QMainWindow(parent)
	, m_wServer(nullptr)
	, m_wDatabase(nullptr)
	, m_server(nullptr)
	, m_database(QSqlDatabase::addDatabase("QODBC3", "main"))
{
	//ui.setupUi(this);
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

	QWidget* _wMain = new QWidget(this);													/*!< 主窗口中心控件 */
	m_wDatabase = new DatabaseForm(_dbHost, _dbName, _dbUser, _dbPwd, _wMain);				/*!< 数据库控件 */
	m_wServer = new ServerForm(_srvAddr, _wMain);											/*!< 服务端控件 */
	DischargerForm* _wDischarger = new DischargerForm(_wMain);								/*!< 分盘机控件 */
	SortTableForm* _wSortTable = new SortTableForm(_wMain);									/*!< 分拣台控件 */
	ShipmentPortForm* _wShipment = new ShipmentPortForm(_wMain);							/*!< 出货口控件 */
	OrderForm* _wOrder = new OrderForm(_wMain);												/*!< 订单详情控件 */

	QGroupBox* _groupDatabase = new QGroupBox(QString::fromLocal8Bit("数据库"), this);		/*!< 数据库分组框 */
	QGroupBox* _groupServer = new QGroupBox(QString::fromLocal8Bit("服务端"), this);		/*!< 服务端分组框 */
	QGroupBox* _groupDischarger = new QGroupBox(QString::fromLocal8Bit("分盘机"), this);	/*!< 分盘机分组框 */
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
	_layGroupDischarger->addWidget(_wDischarger);
	_layGroupSort->addWidget(_wSortTable);
	_layGroupShipment->addWidget(_wShipment);
	_layGroupOrder->addWidget(_wOrder);

	// 为分组框添加布局
	_groupDatabase->setLayout(_layGroupDatabase);
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
	slotSave();
	event->accept();

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

		// TODO 连接分盘机

		_out << QString::fromLocal8Bit("%1 客户端：[%2:%3]离线").arg(_curTime).arg(_socket->peerAddress().toString()).arg(_socket->peerPort()) << endl;

		_socket->close();
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

	// TODO 创建数据库表

	// TODO 读取数据库中的数据

	return;
}

void WCSSimulator::slotCloseDatabase()
{
	if (m_database.isOpen())
	{
		m_database.close();
	}

	return;
}
