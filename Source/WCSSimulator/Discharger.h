﻿#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>

class Discharger : public QObject
{
	Q_OBJECT

public:
	Discharger(const quint8& no, const QString& addr, bool client = true, QObject* parent = nullptr);
	Discharger(const quint8& no, const QString& addr, const quint16& port = 0, bool client = true, QObject* parent = nullptr);
	~Discharger();
public:
	/*!
	 * @brief 分盘机的状态信息码
	 * @since 2020/2/10 FanKaiyu
	 * 描述分盘机不同状态的码值
	 */
	enum Status
	{
		NotReady,			/*!< 分盘机未就绪，即分盘机未分盘托盘并且没有储备托盘 */
		Prepare,			/*!< 分盘机准备中，即分盘机未分盘托盘但有储备托盘，准备分盘托盘 */
		AllReady,			/*!< 分盘机已就绪，即分盘机已分盘托盘 */
		AddrError,			/*!< 分盘机地址错误引起的异常 */
		PortError,			/*!< 分盘机端口错误引起的异常 */
	};
private:
	quint8 m_no;			/*!< 序号 */
private:
	quint8 m_status;		/*!< 状态 */
	QString m_addr;			/*!< 地址 */
	quint16 m_port;			/*!< 端口 */
	bool m_client;			/*!< 客户端标识 */
public:
	QByteArray m_buffer;	/*!< 数据接收的缓存区  */
private:
	QTcpSocket* m_socket;	/*!< TCP远程端通信指针 */
private:
	/*!
	 * @brief 数据处理
	 * @arg QByteArray& 接收到的数据
	 * @return QT_NAMESPACE::QByteArrayList 处理数据后获得的报文列表
	 * @since 2020/2/10 FanKaiyu
	 * 处理接收到的数据，并返回接收到的报文
	 */
	QByteArrayList Process(QByteArray&);

	/*!
	 * @brief 报文响应
	 * @arg const QByteArrayList& 报文列表
	 * @return void
	 * @since 2020/2/10 FanKaiyu
	 * 响应接收到的报文
	 */
	void Answer(const QByteArrayList&);
public:
	/*!
	 * @brief 向分盘机请求托盘
	 * @return void
	 * @since 2020/2/10 FanKaiyu
	 * 生成托盘请求报文，并向分盘机发送。
	 */
	void AskTray();

	/*!
	 * @brief 获取分盘机状态的文本信息
	 * @return QT_NAMESPACE::QString 分盘机的状态信息
	 * @since 2020/2/10 FanKaiyu
	 * 将分盘机状态转换为用户可读的文本文字信息
	 */
	QString	GetStatusText() const;

	/*!
	 * @brief 获取分盘机状态
	 * @return QT_NAMESPACE::quint8 分盘机状态码
	 * @since 2020/2/10 FanKaiyu
	 * 返回分盘机状态码
	 */
	quint8 GetStatus() const { return m_status; }

	/*!
	 * @brief 分盘机状态码转换
	 * @arg const quint8& 分盘机状态码
	 * @return QT_NAMESPACE::QString 分盘机状态信息
	 * @since 2020/2/10 FanKaiyu
	 * 将分盘机状态码转换为用户可读的文本文字信息
	 */
	static QString status(const quint8&);

	/*!
	 * @brief 设置分盘机的地址
	 * @arg const QString& 地址信息。格式: 地址:端口 例如:127.0.0.1:8008
	 * @return void
	 * @since 2020/2/11 FanKaiyu
	 * 设置分盘机的地址和端口号
	 */
	void SetAddress(const QString&);

	/*!
	 * @brief 设置分盘机地址
	 * @arg const QString& 地址信息
	 * @arg const quint16& 端口
	 * @return void
	 * @since 2020/2/11 FanKaiyu
	 * 设置分盘机的地址以及端口号
	 */
	void SetAddress(const QString&, const quint16&);

	/*!
	 * @brief 获取分盘机地址
	 * @arg QString& 返回地址信息
	 * @arg quint16& 返回端口号
	 * @return void
	 * @since 2020/2/11 FanKaiyu
	 * 获取分盘机的地址以及端口号
	 */
	void GetAddress(QString&, quint16&) const;

	/*!
	 * @brief 获取分盘机地址
	 * @return QT_NAMESPACE::QString 返回地址信息。格式: 地址:端口 例如:127.0.0.1:8008
	 * @since 2020/2/11 FanKaiyu
	 * 获取分盘机的地址以及端口号
	 */
	QString GetAddress() const;

	/*!
	 * @brief 设置分盘机模式
	 * @arg const bool& 分盘机模式，为true时是客户端，为false时是服务端
	 * @return void
	 * @since 2020/2/11 FanKaiyu
	 * 修改分盘机模式信息
	 */
	void SetMode(const bool&);

	/*!
	 * @brief 获取分盘机模式
	 * @return bool 客户端模式返回true,服务端模式返回false
	 * @since 2020/2/11 FanKaiyu
	 * 返回分盘机模式信息
	 */
	bool GetMode() const { return m_client; }

	/*!
	 * @brief 判断分盘机是否已经连接
	 * @return bool 已连接返回true,否则返回false
	 * @since 2020/2/11 FanKaiyu
	 * 判断分盘机是否已经连接
	 */
	bool IsConnected() const;
signals:
	/*!
	 * @brief 分盘机更新信号
	 * @return void
	 * @since 2020/2/10 FanKaiyu
	 * 当分盘机状态发生改变时，发出此信号。
	 */
	void Update();
private slots:
	/*!
	 * @brief 读取数据
	 * @return void
	 * @since 2020/2/10 FanKaiyu
	 * 当TCP有数据可以读取时触发的槽函数。
	 */
	void slotRead();

	/*!
	 * @brief 中断连接
	 * @return void
	 * @since 2020/2/11 FanKaiyu
	 * 当分盘机通信中断时触发此槽函数
	 */
	void slotDisconnected();
};