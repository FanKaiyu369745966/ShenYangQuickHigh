#include "ServerForm.h"
#include <QTextEdit>
#include <QDialog>
#include <QTextStream>
#include <QTextCodec>

ServerForm::ServerForm(const QString& addr, QWidget* parent)
	: QWidget(parent)
	, m_addr(addr)
	, m_listened(false)
	, m_leditAddr(nullptr)
	, m_pbutListen(nullptr)
{
	//ui.setupUi(this);
	Initialize();
}

ServerForm::~ServerForm()
{
}

void ServerForm::Initialize()
{
	QLabel* _labAddr = new QLabel(QString::fromLocal8Bit("地址："), this);				/*!< 服务端地址标签 */
	m_leditAddr = new QLineEdit(this);													/*!< 服务端地址编辑栏 */
	m_pbutListen = new QPushButton(QString::fromLocal8Bit("监听"), this);				/*!< 服务端监听按钮 */
	QPushButton* _pbutDetail = new QPushButton(QString::fromLocal8Bit("详情"), this);	/*!< 服务端详情按钮 */

	QHBoxLayout* _lay = new QHBoxLayout();												/*!< 服务端属性配置控件布局 */

	// 为服务端属性配置空格键布局添加控件
	_lay->addWidget(_labAddr);
	_lay->addWidget(m_leditAddr);
	_lay->addWidget(m_pbutListen);
	_lay->addWidget(_pbutDetail);

	setLayout(_lay);

	// 增加编辑框提示信息
	m_leditAddr->setPlaceholderText(QString::fromLocal8Bit("地址:端口 例如:127.0.0.1:8008"));

	m_leditAddr->setText(m_addr);

	// 为控件添加信号和槽函数
	QObject::connect(m_leditAddr, &QLineEdit::editingFinished, this, &ServerForm::slotEditFinished);
	QObject::connect(m_pbutListen, &QPushButton::released, this, &ServerForm::slotReleaseListenButton);
	QObject::connect(_pbutDetail, &QPushButton::released, this, &ServerForm::slotReleaseDetailButton);

	return;
}

void ServerForm::slotReleaseListenButton()
{
	if (m_listened == false)
	{
		emit signalListen(m_listened);

		if (m_listened)
		{
			m_pbutListen->setText(QString::fromLocal8Bit("关闭"));
			m_leditAddr->setEnabled(false);
		}

		return;
	}

	emit signalClose();

	m_pbutListen->setText(QString::fromLocal8Bit("监听"));
	m_leditAddr->setEnabled(true);
	m_listened = false;

	return;
}

void ServerForm::slotReleaseDetailButton()
{
	// 创建对话框,并显示服务端的历史纪录
	QDialog* _dialog = new QDialog(this);

	QTextEdit* _textEdit = new QTextEdit(_dialog);

	QVBoxLayout* _lay = new QVBoxLayout(_dialog);

	_lay->addWidget(_textEdit);

	_dialog->setLayout(_lay);

	_dialog->setWindowTitle(QString::fromLocal8Bit("服务端详情"));
	_dialog->setMinimumSize(800, 600);

	_textEdit->setReadOnly(true);

	QFile file("Log/Server.log");

	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream stream(&file);
		stream.setCodec(QTextCodec::codecForName("GB2312"));

		_textEdit->append(stream.readAll());
	}

	_dialog->show();

	return;
}

void ServerForm::slotEditFinished()
{
	m_addr = m_leditAddr->text();

	emit signalEditFinished(m_addr);

	return;
}
