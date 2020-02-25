#include "DischargerForm.h"
#include "Discharger.h"

DischargerForm::DischargerForm(QWidget* parent)
	: QWidget(parent)
	, m_leditNo(nullptr)
	, m_leditAddr(nullptr)
	, m_checkClient(nullptr)
	, m_pbutAdd(nullptr)
	, m_pbutEdit(nullptr)
	, m_pbutDel(nullptr)
	, m_model(nullptr)
	, m_byNo(0)
	, m_strAddr("")
	, m_bClient(false)
{
	//ui.setupUi(this);
	Initialize();
}

DischargerForm::~DischargerForm()
{
}

void DischargerForm::Initialize()
{
	m_pbutAdd = new QPushButton(QString::fromLocal8Bit("添加"), this);						/*!< 添加按钮 */
	m_pbutEdit = new QPushButton(QString::fromLocal8Bit("修改"), this);						/*!< 编辑按钮 */
	m_pbutDel = new QPushButton(QString::fromLocal8Bit("删除"), this);						/*!< 删除按钮 */
	QLabel* _labNo = new QLabel(QString::fromLocal8Bit("序号："), this);					/*!< 序号标签 */
	QLabel* _labAddr = new QLabel(QString::fromLocal8Bit("地址："), this);					/*!< 地址标签 */
	//QLabel* _labStatus = new QLabel(QString::fromLocal8Bit("状态："), this);				/*!< 状态标签 */
	m_leditNo = new QLineEdit(this);														/*!< 序号编辑框 */
	m_leditAddr = new QLineEdit(this);														/*!< 地址编辑框 */
	//QComboBox* _combStatus = new QComboBox(this);											/*!< 状态下拉列表 */
	m_checkClient = new QCheckBox(QString::fromLocal8Bit("客户端"), this);		/*!< 客户端模式单选按钮 */

	QTableView* _table = new QTableView(this);												/*!< 表单控件 */

	QHBoxLayout* _hlay = new QHBoxLayout();													/*!< 水平布局 */
	QVBoxLayout* _vlay = new QVBoxLayout();													/*!< 垂直布局 */

	// 为布局添加控件
	_hlay->addWidget(_labNo);
	_hlay->addWidget(m_leditNo);
	_hlay->addWidget(_labAddr);
	_hlay->addWidget(m_leditAddr);
	_hlay->addWidget(m_checkClient);
	_hlay->addWidget(m_pbutAdd);
	_hlay->addWidget(m_pbutEdit);
	_hlay->addWidget(m_pbutDel);

	_vlay->addLayout(_hlay);
	_vlay->addWidget(_table);

	setLayout(_vlay);

	// 增加编辑框提示信息
	m_leditNo->setPlaceholderText(QString::fromLocal8Bit("仅支持>0并且<255的数字"));
	m_leditAddr->setPlaceholderText(QString::fromLocal8Bit("地址:端口 例如:127.0.0.1:8008"));

	m_checkClient->setChecked(m_bClient);

	m_model = new QStandardItemModel(this);	/*!< 分盘机表单成员模板 */

	// 为模板设置列头
	int _index = 0;
	// 为分盘机模板设置列头
	m_model->setColumnCount(5);
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("序号"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("地址"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("模式"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("连接"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("状态"));

	QItemSelectionModel* _selModel = new QItemSelectionModel(m_model);

	_table->setModel(m_model);
	_table->setSelectionModel(_selModel);
	_table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	_table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

	// 为控件添加信号和槽函数
	QObject::connect(m_checkClient, &QCheckBox::toggled, this, &DischargerForm::OnClickCheckButton);
	QObject::connect(m_leditNo, &QLineEdit::editingFinished, this, &DischargerForm::EditFinished);
	QObject::connect(m_leditAddr, &QLineEdit::editingFinished, this, &DischargerForm::EditFinished);
	QObject::connect(m_pbutAdd, &QPushButton::pressed, this, &DischargerForm::PressedAddButton);
	QObject::connect(m_pbutDel, &QPushButton::pressed, this, &DischargerForm::PressedDeleteButton);
	QObject::connect(m_pbutEdit, &QPushButton::pressed, this, &DischargerForm::PressedEditButton);
	QObject::connect(_selModel, &QItemSelectionModel::currentChanged, this, &DischargerForm::OnSelectItem);

	return;
}

void DischargerForm::OnClickCheckButton(bool checked)
{
	m_bClient = checked;

	return;
}

void DischargerForm::EditFinished()
{
	m_byNo = m_leditNo->text().toInt();
	m_strAddr = m_leditAddr->text();

	return;
}

void DischargerForm::PressedAddButton()
{
	if (m_byNo <= 0 || m_byNo >= 255)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加分盘机"), QString::fromLocal8Bit("添加分盘机失败！无效的分盘机编号。\n注意：编号仅支持大于0且小于255的值。"));
		return;
	}

	QString _addr(m_strAddr.section(':', 0, -2));
	quint16 _port = static_cast<quint16>(m_strAddr.section(':', -1, -1).toUInt());

	QHostAddress _host;
	if (_host.setAddress(_addr) == false)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加分盘机"), QString::fromLocal8Bit("添加分盘机失败！无效的分盘机地址。"));
		return;
	}

	if (_port > 65535)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加分盘机"), QString::fromLocal8Bit("添加分盘机失败！无效的分盘机端口。\n注意：端口号仅支持小于65535的正整数"));
		return;
	}

	if (m_bClient == false && _port == 0)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加分盘机"), QString::fromLocal8Bit("添加分盘机失败！无效的分盘机端口。\n注意：服务端模式下端口号不能等于0"));
		return;
	}

	bool _result = false;

	emit AddNewDischarger(_result);

	if (_result == false)
	{
		return;
	}

	AddNewDischarger(m_byNo, m_strAddr, m_bClient);

	return;
}

void DischargerForm::PressedDeleteButton()
{
	if (m_byNo <= 0 || m_byNo >= 255)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("删除分盘机"), QString::fromLocal8Bit("删除分盘机失败！无效的分盘机编号。\n注意：编号仅支持大于0且小于255的值。"));
		return;
	}

	bool _result = false;

	emit DeleteDischarger(_result);

	if (_result == false)
	{
		return;
	}

	DeleteDischarger(m_byNo);

	m_byNo = m_leditNo->text().toInt();
	m_strAddr = m_leditAddr->text();
	m_bClient = m_checkClient->isChecked();

	return;
}

void DischargerForm::PressedEditButton()
{
	if (m_byNo <= 0 || m_byNo >= 255)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("编辑分盘机"), QString::fromLocal8Bit("编辑分盘机失败！无效的分盘机编号。\n注意：编号仅支持大于0且小于255的值。"));
		return;
	}

	QString _addr(m_strAddr.section(':', 0, -2));
	quint16 _port = static_cast<quint16>(m_strAddr.section(':', -1, -1).toUInt());

	QHostAddress _host;
	if (_host.setAddress(_addr) == false)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("编辑分盘机"), QString::fromLocal8Bit("编辑分盘机失败！无效的分盘机地址。"));
		return;
	}

	if (_port > 65535)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("编辑分盘机"), QString::fromLocal8Bit("编辑分盘机失败！无效的分盘机端口。\n注意：端口号仅支持小于65535的正整数"));
		return;
	}

	if (m_bClient == false && _port == 0)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("编辑分盘机"), QString::fromLocal8Bit("编辑分盘机失败！无效的分盘机端口。\n注意：服务端模式下端口号不能等于0"));
		return;
	}

	bool _result = false;

	emit EditDischarger(_result);

	if (_result == false)
	{
		return;
	}

	EditDischarger(m_byNo, m_strAddr, m_bClient);

	return;
}

void DischargerForm::OnSelectItem(const QModelIndex& current, const QModelIndex& previous)
{
	if (current.isValid())
	{
		// 将单元格的内容填入属性配置信息中

		m_leditNo->setText(m_model->item(current.row(), 0)->text());

		m_leditAddr->setText(m_model->item(current.row(), 1)->text());

		QString _model = m_model->item(current.row(), 2)->text();

		if (_model == QString::fromLocal8Bit("客户端"))
		{
			m_checkClient->setChecked(true);
		}
		else if (_model == QString::fromLocal8Bit("服务端"))
		{
			m_checkClient->setChecked(false);
		}
	}

	m_byNo = m_leditNo->text().toInt();
	m_strAddr = m_leditAddr->text();
	m_bClient = m_checkClient->isChecked();

	return;
}

bool DischargerForm::AddNewDischarger(quint8 no, QString addr, bool client)
{
	QString _addr(addr.section(':', 0, -2));
	quint16 _port = static_cast<quint16>(addr.section(':', -1, -1).toUInt());

	return AddNewDischarger(no, _addr, _port, client);
}

bool DischargerForm::AddNewDischarger(quint8 no, QString addr, quint16 port, bool client)
{
	if (no <= 0 || no >= 255)
	{
		return false;
	}

	QHostAddress _host;
	if (_host.setAddress(addr) == false)
	{
		return false;
	}

	if (port > 65535)
	{
		return false;
	}

	if (client == false && port == 0)
	{
		return false;
	}

	// 向列表中添加分盘机
	QList<QStandardItem*> _list;
	_list.push_back(new QStandardItem(QString::fromLocal8Bit("%1").arg(no)));
	_list.push_back(new QStandardItem(QString::fromLocal8Bit("%1:%2").arg(addr).arg(port)));

	if (client)
	{
		_list.push_back(new QStandardItem(QString::fromLocal8Bit("客户端")));
	}
	else
	{
		_list.push_back(new QStandardItem(QString::fromLocal8Bit("服务端")));
	}

	_list.push_back(new QStandardItem(QString::fromLocal8Bit("未连接")));
	_list.push_back(new QStandardItem(Discharger::status(Discharger::NotReady)));

	m_model->appendRow(_list);

	for (QList<QStandardItem*>::iterator it = _list.begin(); it != _list.end(); ++it)
	{
		(*it)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		(*it)->setEditable(false);
		(*it)->setToolTip((*it)->text());
	}

	return true;
}

void DischargerForm::DeleteDischarger(quint8 no)
{
	if (no <= 0 || no >= 255)
	{
		return;
	}

	// 从列表中删除该编号的分盘机
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text().toInt() == no)
		{
			m_model->removeRow(i);

			return;
		}
	}

	return;
}

bool DischargerForm::EditDischarger(quint8 no, QString addr, bool client)
{
	QString _addr(addr.section(':', 0, -2));
	quint16 _port = static_cast<quint16>(addr.section(':', -1, -1).toUInt());

	return EditDischarger(no, _addr, _port, client);
}

bool DischargerForm::EditDischarger(quint8 no, QString addr, quint16 port, bool client)
{
	if (no <= 0 || no >= 255)
	{
		return false;
	}

	QHostAddress _host;
	if (_host.setAddress(addr) == false)
	{
		return false;
	}

	if (port > 65535)
	{
		return false;
	}

	if (client == false && port == 0)
	{
		return false;
	}

	// 修改列表中该编号的分盘机属性
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text().toInt() != no)
		{
			continue;
		}

		m_model->item(i, 1)->setText(QString::fromLocal8Bit("%1:%2").arg(addr).arg(port));

		if (client)
		{
			m_model->item(i, 2)->setText(QString::fromLocal8Bit("客户端"));
		}
		else
		{
			m_model->item(i, 2)->setText(QString::fromLocal8Bit("服务端"));
		}
	}

	return true;
}

void DischargerForm::Update(quint8 no, bool connected)
{
	if (no <= 0 || no >= 255)
	{
		return;
	}

	// 修改列表中该编号的分盘机属性
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text().toInt() != no)
		{
			continue;
		}

		if (connected)
		{
			m_model->item(i, 3)->setText(QString::fromLocal8Bit("已连接"));
		}
		else
		{
			m_model->item(i, 3)->setText(QString::fromLocal8Bit("未连接"));
		}
	}

	return;
}

void DischargerForm::Update(quint8 no, QString status)
{
	if (no <= 0 || no >= 255)
	{
		return;
	}

	// 修改列表中该编号的分盘机属性
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text().toInt() != no)
		{
			continue;
		}

		m_model->item(i, 4)->setText(status);
	}

	return;
}

void DischargerForm::Update(quint8 no, quint8 status)
{
	if (no <= 0 || no >= 255)
	{
		return;
	}

	// 修改列表中该编号的分盘机属性
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text().toInt() != no)
		{
			continue;
		}

		m_model->item(i, 4)->setText(Discharger::status(status));
	}

	return;
}
