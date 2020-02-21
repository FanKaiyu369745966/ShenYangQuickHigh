#include "Discharger.h"

#include <cstdio>
#include <QDebug>
#include <QHostAddress>

Discharger::Discharger(const quint8& no, const QString& addr, const bool& client, const QString& order, const bool requested, QObject* parent)
	: QObject(parent)
	, m_no(no)
	, m_socket(nullptr)
	, m_status(NotReady)
	, m_order(order)
	, m_requested(requested)
{
	moveToThread(&m_thread);
	m_thread.start();

	m_timer.setInterval(1000);
	QObject::connect(&m_timer, &QTimer::timeout, this, &Discharger::slotThread);

	SetAddress(addr);
	SetMode(client);

	m_timer.start();
}

Discharger::Discharger(const quint8& no, const QString& addr, const quint16& port, const bool& client, const QString& order, const bool requested, QObject* parent)
	: QObject(parent)
	, m_no(no)
	, m_socket(nullptr)
	, m_status(NotReady)
	, m_order(order)
	, m_requested(requested)
{
	moveToThread(&m_thread);
	m_thread.start();

	m_timer.setInterval(1000);
	QObject::connect(&m_timer, &QTimer::timeout, this, &Discharger::slotThread);

	SetAddress(addr, port);
	SetMode(client);

	m_timer.start();
}

Discharger::~Discharger()
{
	m_timer.stop();
	m_thread.quit();
	m_thread.wait();
}

QByteArrayList Discharger::Process(QByteArray& data)
{
	QString _debug;

	for (int i = 0; i < data.size(); ++i)
	{
		_debug += QString(" %1").arg(static_cast<quint8>(data.at(i)), 2, 16, QLatin1Char('0'));
	}

	qDebug() << QString::fromLocal8Bit("接收数据:") << _debug;
	_debug = "";

	using namespace std;

	int _length = data.size();					/*!< 全部数据的长度 */
	quint8* _data = new quint8[_length];		/*!< 全部数据 */

	// 将数据转换为无符号形式
	memcpy(_data, data.data(), _length);

	// 清空缓存区
	data.clear();

	QByteArrayList _list;		/*!< 报文列表 */

	const quint8 _pkgHead = 0x8E/*!< 报文头 */, _pkgTail = 0x8F/*!< 报文尾 */;

	quint8* _result = _data;		/*!< 数据头 */
	int _size = _length;			/*!< 数据长度 */

	quint8* _head = nullptr;		/*!< 指向报文头的地址 */

	while (true)
	{
		if (_size <= 0)
		{
			break;
		}

		// 从剩余数据中获取报文头
		_head = static_cast<quint8*>(memchr(_result, _pkgHead, _size));

		// 剩余的数据中不包含报文头
		if (_head == nullptr)
		{
			// 舍弃剩余的数据并退出循环
			_size = 0;

			break;
		}

		// 剩余的数据中包含报文头

		quint8* _tail = nullptr;	/*!< 报文尾 */

		// 从剩余数据中获取报文尾
		_tail = static_cast<quint8*>(memchr(_result + 1, _pkgTail, _size - 1));

		// 剩余的数据中不包含报文尾
		if (_tail == nullptr)
		{
			// 保留剩余的数据并退出循环
			_result = _head;
			_size = _length - (_result - _data);

			break;
		}

		// 剩余的数据中包含报文尾

		_result = _tail + 1;
		_size = _length - (_result - _data);

		int _pkgSize = (_tail - _head) - 1;

		_list.push_back(QByteArray(reinterpret_cast<char*>(_head + 1), _pkgSize));

		for (int i = 0; i < _pkgSize + 2; ++i)
		{
			_debug += QString(" %1").arg(*(_head + i), 2, 16, QLatin1Char('0'));
		}

		qDebug() << QString::fromLocal8Bit("接收报文:") << _debug;
		_debug = "";
	}

	if (_size > 0)
	{
		data = QByteArray(reinterpret_cast<char*>(_result), _size);
	}

	delete[] _data;

	return _list;
}

void Discharger::Answer(const QByteArrayList& list)
{
	for (QByteArrayList::const_iterator it = list.begin(); it != list.end(); ++it)
	{
		const char* _data = it->data();

		quint8 _no = *_data;			/*!< 设备编号 */
		quint8 _func = *(_data + 1);	/*!< 功能码 */

		if (_no != m_no)
		{
			// 设备编号不匹配，舍弃报文
			continue;
		}

		switch (_func)
		{
		case 0x1F:
		{
			// 分盘机状态报文

			quint8 _param = *(_data + 2);	/*!< 功能参数 */

			// 更新分盘机状态
			m_status = _param;

			emit Update();
			break;
		}
		case 0x2F:
		{
			// 托盘请求回复报文

			// 停止继续发送托盘请求报文。
			m_requested = true;
			//m_timer.stop();

			emit Update();

			break;
		}
		}
	}

	return;
}

void Discharger::RequestTray(const QString& order)
{
	if (order == m_order)
	{
		// 订单号未发生改变
		return;
	}

	m_order = order;
	m_requested = false;

	//m_timer.start();

	emit Update();

	return;
}

void Discharger::ResetRequest()
{
	m_requested = false;

	//m_timer.start();

	emit Update();

	return;
}

QString Discharger::GetStatusText() const
{
	return status(m_status);
}

QString Discharger::status(const quint8& status)
{
	switch (status)
	{
	case NotReady:
		return QString::fromLocal8Bit("未就绪");
	case Prepare:
		return QString::fromLocal8Bit("准备中");
	case AllReady:
		return QString::fromLocal8Bit("已就绪");
	case AddressError:
		return QString::fromLocal8Bit("地址信息错误，无法连接");
	case PortError:
		return QString::fromLocal8Bit("端口信息错误，无法连接");
	case PowerError:
		return QString::fromLocal8Bit("缺少权限，无法连接");
	}

	return QString("");
}

void Discharger::SetAddress(const QString& addr)
{
	QString _addr(addr.section(':', 0, -2));
	quint16 _port = static_cast<quint16>(addr.section(':', -1, -1).toUInt());

	QHostAddress _host;

	if (_host.setAddress(_addr) == false)
	{
		return;
	}

	m_addr = _addr;
	m_port = _port;

	if (m_socket)
	{
		m_socket->close();
	}

	return;
}

void Discharger::SetAddress(const QString& addr, const quint16& port)
{
	QHostAddress _host;

	if (_host.setAddress(addr) == false)
	{
		return;
	}

	m_addr = addr;
	m_port = port;

	if (m_socket)
	{
		m_socket->close();

		m_socket = nullptr;
	}

	return;
}

void Discharger::GetAddress(QString& addr, quint16& port) const
{
	addr = m_addr;
	port = m_port;

	return;
}

QString Discharger::GetAddress() const
{
	return QString("%1:%2").arg(m_addr).arg(m_port);
}

void Discharger::SetMode(const bool& client)
{
	m_client = client;

	if (m_socket)
	{
		m_socket->close();

		m_socket = nullptr;
	}

	return;
}

bool Discharger::IsConnected() const
{
	if (m_socket == nullptr)
	{
		return false;
	}

	QAbstractSocket::SocketState state = m_socket->state();

	bool flag = false;

	switch (state)
	{
	case QAbstractSocket::UnconnectedState:
		break;
	case QAbstractSocket::HostLookupState:
		break;
	case QAbstractSocket::ConnectingState:
		break;
	case QAbstractSocket::ConnectedState:
		flag = true;
		break;
	case QAbstractSocket::BoundState:
		break;
	case QAbstractSocket::ListeningState:
		break;
	case QAbstractSocket::ClosingState:
		break;
	}

	return flag;
}

bool Discharger::IsRequested() const
{
	return m_requested;
}

bool Discharger::Connect(QTcpSocket* socket)
{
	if (socket == nullptr)
	{
		// 无效的指针
		return false;
	}

	if (m_client == false)
	{
		// 模式不匹配
		return false;
	}

	if (socket->peerAddress().toString() != m_addr)
	{
		// IP地址不匹配
		return false;
	}

	if (m_port != 0 && socket->peerPort() != m_port)
	{
		// 端口号不匹配
		return false;
	}

	if (m_socket)
	{
		// 关闭现有客户端连接
		m_socket->close();

		m_socket = nullptr;
	}

	// 连接客户端
	m_socket = socket;

	// 连接客户端信号和槽函数
	QObject::connect(m_socket, &QTcpSocket::disconnected, this, &Discharger::slotDisconnected);
	QObject::connect(m_socket, &QTcpSocket::readyRead, this, &Discharger::slotRead);

	return true;
}

void Discharger::slotDisconnected()
{
	if (!m_client)
	{
		m_socket->deleteLater();
	}

	emit Update();

	return;
}

void Discharger::slotConnected()
{
	emit Update();

	return;
}

void Discharger::slotError(QAbstractSocket::SocketError error)
{
	qDebug() << QString::fromLocal8Bit("%1:%2 异常:").arg(m_socket->peerName()).arg(m_socket->peerPort()) << m_socket->errorString();

	switch (error)
	{
	case QAbstractSocket::ConnectionRefusedError:
	{
		m_socket->deleteLater();
		m_socket = nullptr;
		break;
	}
	case QAbstractSocket::RemoteHostClosedError:
	{
		m_socket->deleteLater();
		m_socket = nullptr;
		break;
	}
	case QAbstractSocket::HostNotFoundError:
	{
		m_status = AddressError;

		break;
	}
	case QAbstractSocket::SocketAccessError:
	{
		m_status = PowerError;

		break;
	}
	case QAbstractSocket::SocketResourceError:
		break;
	case QAbstractSocket::SocketTimeoutError:
		break;
	case QAbstractSocket::DatagramTooLargeError:
		break;
	case QAbstractSocket::NetworkError:
	{
		m_socket->deleteLater();
		m_socket = nullptr;
		break;
	}
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
	{
		m_socket->deleteLater();
		m_socket = nullptr;
		break;
	}
	case QAbstractSocket::ProxyConnectionRefusedError:
	{
		m_socket->deleteLater();
		m_socket = nullptr;
		break;
	}
	case QAbstractSocket::ProxyConnectionClosedError:
	{
		m_socket->deleteLater();
		m_socket = nullptr;
		break;
	}
	case QAbstractSocket::ProxyConnectionTimeoutError:
	{
		m_socket->deleteLater();
		m_socket = nullptr;
		break;
	}
	case QAbstractSocket::ProxyNotFoundError:
		break;
	case QAbstractSocket::ProxyProtocolError:
	{
		m_socket->deleteLater();
		m_socket = nullptr;
		break;
	}
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
	default:
		break;
	}

	emit Update();

	return;
}

void Discharger::slotRead()
{
	if (m_socket->isReadable())
	{
		Answer(Process(m_buffer += m_socket->readAll()));
	}

	return;
}

void Discharger::slotRequestTray()
{
	if (m_socket == nullptr)
	{
		return;
	}

	if (m_requested)
	{
		return;
	}

	quint8 _pkg[4];
	_pkg[0] = 0x8E;
	_pkg[1] = m_no;
	_pkg[2] = 0x2F;
	_pkg[3] = 0x8F;

	m_socket->write(reinterpret_cast<char*>(_pkg), 4);

	m_socket->flush();

	return;
}

void Discharger::slotConnect()
{
	if (m_client)
	{
		return;
	}

	if (m_socket)
	{
		return;
	}

	m_socket = new QTcpSocket(this);

	QHostAddress _addr;

	if (_addr.setAddress(m_addr) == false)
	{
		m_socket->deleteLater();
		m_socket = nullptr;

		if (m_status != AddressError)
		{
			m_status = AddressError;

			emit Update();
		}

		return;
	}

	if (m_port == 0)
	{
		m_socket->deleteLater();
		m_socket = nullptr;

		if (m_status != PortError)
		{
			m_status = PortError;

			emit Update();
		}

		return;
	}

	// 连接客户端信号和槽函数
	QObject::connect(m_socket, &QTcpSocket::disconnected, this, &Discharger::slotDisconnected);
	QObject::connect(m_socket, &QTcpSocket::readyRead, this, &Discharger::slotRead);
	QObject::connect(m_socket, &QTcpSocket::connected, this, &Discharger::slotConnected);
	// static_cast< 返回值 (作用域::*)(参数)>(函数指针)
	QObject::connect(m_socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &Discharger::slotError);

	m_socket->connectToHost(_addr, m_port);

	return;
}

void Discharger::slotThread()
{
	if (!m_client)
	{
		slotConnect();
	}

	if (!m_requested)
	{
		if (m_order.isNull() || m_order.isEmpty())
		{
			return;
		}

		slotRequestTray();
	}

	return;
}
