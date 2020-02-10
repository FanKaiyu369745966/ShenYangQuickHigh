#include "Discharger.h"

#include <cstdio>
#include <QDebug>

Discharger::Discharger(const quint8& no, QObject* parent)
	: QObject(parent)
	, m_no(no)
{
}

Discharger::~Discharger()
{
}

QByteArrayList Discharger::Process(QByteArray& data)
{
	QString _debug;

	for (int i = 0; i < data.size(); ++i)
	{
		_debug += QString(" %1").arg(data.at(i), 2, 16, QLatin1Char('0'));
	}

	qDebug() << "接收数据:" << _debug;
	_debug = "";

	using namespace std;

	int _length = data.size();					/*!< 全部数据的长度 */
	quint8* _data = new quint8[_length];		/*!< 全部数据 */

	// 将数据转换为无符号形式
	memcpy(_data, data.data(), _length);

	// 清空缓存区
	data.clear();

	QByteArrayList _list;		/*!< 报文列表 */

	const quint8 _pkgHead = 0x8E/*!< 报文头 */, const _pkgTail = 0x8F/*!< 报文尾 */;

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

		qDebug() << "接收报文:" << _debug;
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

			emit UpdateStatus();
			break;
		}
		case 0x2F:
		{
			// 托盘请求回复报文

			// TODO 停止继续发送托盘请求报文。
			break;
		}
		}
	}

	return;
}

void Discharger::AskTray()
{
	quint8 _pkg[4];
	_pkg[0] = 0x8E;
	_pkg[1] = m_no;
	_pkg[2] = 0x2F;
	_pkg[3] = 0x8F;

	m_socket->write(reinterpret_cast<char*>(_pkg), 4);

	m_socket->flush();

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
	case 0:
		return QString::fromLocal8Bit("未就绪");
	case 1:
		return QString::fromLocal8Bit("准备中");
	case 2:
		return QString::fromLocal8Bit("已就绪");
	}

	return QString("");
}

void Discharger::slotRead()
{
	if (m_socket->isReadable())
	{
		Answer(Process(m_buffer += m_socket->readAll()));
	}

	return;
}
