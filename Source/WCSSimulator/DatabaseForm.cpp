#include "DatabaseForm.h"

DatabaseForm::DatabaseForm(QString host, QString dbname, QString user, QString password, QWidget* parent)
	: QWidget(parent)
	, m_leditHost(nullptr)
	, m_leditName(nullptr)
	, m_leditUser(nullptr)
	, m_leditPassword(nullptr)
	, m_pbutLink(nullptr)
	, m_strHost(host)
	, m_strDbName(dbname)
	, m_strUser(user)
	, m_strPassword(password)
	, m_bLinked(false)
{
	//ui.setupUi(this);
	Initialize();
}

DatabaseForm::~DatabaseForm()
{
}

void DatabaseForm::Initialize()
{
	QLabel* _labHost = new QLabel(QString::fromLocal8Bit("主机名："), this);
	QLabel* _labName = new QLabel(QString::fromLocal8Bit("数据库名称："), this);
	QLabel* _labUser = new QLabel(QString::fromLocal8Bit("用户名："), this);
	QLabel* _labPassword = new QLabel(QString::fromLocal8Bit("密码："), this);

	m_leditHost = new QLineEdit(this);
	m_leditName = new QLineEdit(this);
	m_leditUser = new QLineEdit(this);
	m_leditPassword = new QLineEdit(this);

	QCheckBox* _checkShow = new QCheckBox(QString::fromLocal8Bit("显示密码"), this);

	m_pbutLink = new QPushButton(QString::fromLocal8Bit("连接"), this);

	QHBoxLayout* _lay = new QHBoxLayout();

	_lay->addWidget(_labHost);
	_lay->addWidget(m_leditHost);
	_lay->addWidget(_labName);
	_lay->addWidget(m_leditName);
	_lay->addWidget(_labUser);
	_lay->addWidget(m_leditUser);
	_lay->addWidget(_labPassword);
	_lay->addWidget(m_leditPassword);
	_lay->addWidget(_checkShow);
	_lay->addWidget(m_pbutLink);

	setLayout(_lay);

	// 设置编辑框样式
	m_leditPassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);

	// 初始化编辑框文本
	m_leditHost->setText(m_strHost);
	m_leditName->setText(m_strDbName);
	m_leditUser->setText(m_strUser);
	m_leditPassword->setText(m_strPassword);

	// 为控件连接信号和槽函数
	QObject::connect(_checkShow, &QCheckBox::toggled, this, &DatabaseForm::slotCheckBoxToggle);
	QObject::connect(m_pbutLink, &QCheckBox::pressed, this, &DatabaseForm::slotPressedLinkButton);
	QObject::connect(m_leditHost, &QLineEdit::editingFinished, this, &DatabaseForm::slotHostEditFinished);
	QObject::connect(m_leditName, &QLineEdit::editingFinished, this, &DatabaseForm::slotDbNameEditFinished);
	QObject::connect(m_leditUser, &QLineEdit::editingFinished, this, &DatabaseForm::slotUserEditFinished);
	QObject::connect(m_leditPassword, &QLineEdit::editingFinished, this, &DatabaseForm::slotPasswordEditFinished);

	return;
}

void DatabaseForm::slotCheckBoxToggle(bool checked)
{
	if (checked)
	{
		m_leditPassword->setEchoMode(QLineEdit::Normal);

		return;
	}

	m_leditPassword->setEchoMode(QLineEdit::PasswordEchoOnEdit);

	return;
}

void DatabaseForm::slotPressedLinkButton()
{
	if (m_bLinked == false)
	{
		emit OnButtonLink(m_bLinked);

		if (m_bLinked)
		{
			m_leditHost->setEnabled(false);
			m_leditName->setEnabled(false);
			m_leditUser->setEnabled(false);
			m_leditPassword->setEnabled(false);

			m_pbutLink->setText(QString::fromLocal8Bit("中止"));
		}

	}
	else
	{
		emit OnButtonClose();

		m_leditHost->setEnabled(true);
		m_leditName->setEnabled(true);
		m_leditUser->setEnabled(true);
		m_leditPassword->setEnabled(true);

		m_pbutLink->setText(QString::fromLocal8Bit("连接"));

		m_bLinked = false;
	}

	return;
}

void DatabaseForm::slotHostEditFinished()
{
	m_strHost = m_leditHost->text();

	return;
}

void DatabaseForm::slotDbNameEditFinished()
{
	m_strDbName = m_leditName->text();

	return;
}

void DatabaseForm::slotUserEditFinished()
{
	m_strUser = m_leditUser->text();

	return;
}

void DatabaseForm::slotPasswordEditFinished()
{
	m_strPassword = m_leditPassword->text();

	return;
}
