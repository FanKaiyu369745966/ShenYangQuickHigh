#include "ShipmentPortForm.h"

ShipmentPortForm::ShipmentPortForm(QWidget* parent)
	: QWidget(parent)
	, m_pbutAdd(nullptr)
	, m_pbutEdit(nullptr)
	, m_pbutDel(nullptr)
	, m_leditNo(nullptr)
	, m_leditName(nullptr)
	, m_combStatus(nullptr)
	, m_model(nullptr)
	, m_byNo(0)
	, m_strName("")
	, m_bFull(false)
{
	//ui.setupUi(this);
	Initialize();
}

ShipmentPortForm::~ShipmentPortForm()
{
}

void ShipmentPortForm::Initialize()
{
	m_pbutAdd = new QPushButton(QString::fromLocal8Bit("添加"), this);						/*!< 添加按钮 */
	m_pbutEdit = new QPushButton(QString::fromLocal8Bit("修改"), this);						/*!< 编辑按钮 */
	m_pbutDel = new QPushButton(QString::fromLocal8Bit("删除"), this);						/*!< 删除按钮 */
	QLabel* _labNo = new QLabel(QString::fromLocal8Bit("序号："), this);					/*!< 序号标签 */
	QLabel* _labName = new QLabel(QString::fromLocal8Bit("名称："), this);					/*!< 名称标签 */
	QLabel* _labStatus = new QLabel(QString::fromLocal8Bit("状态："), this);				/*!< 状态标签 */
	m_leditNo = new QLineEdit(this);														/*!< 序号编辑框 */
	m_leditName = new QLineEdit(this);														/*!< 地址编辑框 */
	m_combStatus = new QComboBox(this);														/*!< 状态选择下拉菜单 */

	QTableView* _table = new QTableView(this);												/*!< 表单控件 */

	QHBoxLayout* _hlay = new QHBoxLayout();													/*!< 水平布局 */
	QVBoxLayout* _vlay = new QVBoxLayout();													/*!< 垂直布局 */

	// 为布局添加控件
	_hlay->addWidget(_labNo);
	_hlay->addWidget(m_leditNo);
	_hlay->addWidget(_labName);
	_hlay->addWidget(m_leditName);
	_hlay->addWidget(_labStatus);
	_hlay->addWidget(m_combStatus);
	_hlay->addWidget(m_pbutAdd);
	_hlay->addWidget(m_pbutEdit);
	_hlay->addWidget(m_pbutDel);

	_vlay->addLayout(_hlay);
	_vlay->addWidget(_table);

	setLayout(_vlay);

	// 增加编辑框提示信息
	m_leditNo->setPlaceholderText(QString::fromLocal8Bit("仅支持>0并且<255的数字"));

	m_combStatus->setEditable(false);

	m_combStatus->insertItem(0, QString::fromLocal8Bit("空闲"));
	m_combStatus->insertItem(1, QString::fromLocal8Bit("满载"));

	m_combStatus->setCurrentIndex(-1);

	m_model = new QStandardItemModel();	/*!< 分盘机表单成员模板 */

	// 为模板设置列头
	int _index = 0;
	// 为分盘机模板设置列头
	m_model->setColumnCount(3);
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("序号"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("名称"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("状态"));

	_table->setModel(m_model);
	_table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	_table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

	// 为控件添加信号和槽函数
	QObject::connect(m_leditNo, &QLineEdit::editingFinished, this, &ShipmentPortForm::EditFinished);
	QObject::connect(m_leditName, &QLineEdit::editingFinished, this, &ShipmentPortForm::EditFinished);
	QObject::connect(m_pbutAdd, &QPushButton::pressed, this, &ShipmentPortForm::PressedAddButton);
	QObject::connect(m_pbutDel, &QPushButton::pressed, this, &ShipmentPortForm::PressedDeleteButton);
	QObject::connect(m_pbutEdit, &QPushButton::pressed, this, &ShipmentPortForm::PressedEditButton);
	QObject::connect(_table, &QTableView::clicked, this, &ShipmentPortForm::OnSelectItem);
	QObject::connect(m_combStatus, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ShipmentPortForm::OnComboSelect);

	return;
}

void ShipmentPortForm::EditFinished()
{
	m_byNo = m_leditNo->text().toInt();
	m_strName = m_leditName->text();

	return;
}

void ShipmentPortForm::PressedAddButton()
{
	if (m_byNo <= 0 || m_byNo >= 255)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加出货口"), QString::fromLocal8Bit("添加出货口失败！无效的出货口编号。\n注意：编号仅支持大于0且小于255的值。"));
		return;
	}

	bool _result = false;

	emit AddNewShipmentPort(_result);

	if (_result == false)
	{
		return;
	}

	AddNewShipmentPort(m_byNo, m_strName, m_bFull);

	return;
}

void ShipmentPortForm::PressedDeleteButton()
{
	if (m_byNo <= 0 || m_byNo >= 255)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("删除出货口"), QString::fromLocal8Bit("删除出货口失败！无效的分捡台编号。\n注意：编号仅支持大于0且小于255的值。"));
		return;
	}

	bool _result = false;

	emit DeleteShipmentPort(_result);

	if (_result == false)
	{
		return;
	}

	DeleteShipmentPort(m_byNo);

	m_byNo = m_leditNo->text().toInt();
	m_strName = m_leditName->text();

	return;
}

void ShipmentPortForm::PressedEditButton()
{
	if (m_byNo <= 0 || m_byNo >= 255)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("编辑出货口"), QString::fromLocal8Bit("编辑出货口失败！无效的分捡台编号。\n注意：编号仅支持大于0且小于255的值。"));
		return;
	}

	bool _result = false;

	emit EditShipmentPort(_result);

	if (_result == false)
	{
		return;
	}

	EditShipmentPort(m_byNo, m_strName, m_bFull);

	return;
}

void ShipmentPortForm::OnSelectItem(const QModelIndex& current)
{
	if (current.isValid())
	{
		// 将单元格的内容填入属性配置信息中

		m_leditNo->setText(m_model->item(current.row(), 0)->text());

		m_leditName->setText(m_model->item(current.row(), 1)->text());

		if (m_model->item(current.row(), 2)->text() == QString::fromLocal8Bit("满载"))
		{
			m_combStatus->setCurrentIndex(1);
		}
		else
		{
			m_combStatus->setCurrentIndex(0);
		}
	}

	m_byNo = m_leditNo->text().toInt();
	m_strName = m_leditName->text();
	m_bFull = m_combStatus->currentIndex();

	return;
}

void ShipmentPortForm::OnComboSelect(int index)
{
	m_bFull = index;
	return;
}

bool ShipmentPortForm::AddNewShipmentPort(quint8 no, QString name, bool full)
{
	if (no <= 0 || no >= 255)
	{
		return false;
	}

	// 向列表中添加出货口
	QList<QStandardItem*> _list;
	_list.push_back(new QStandardItem(QString::fromLocal8Bit("%1").arg(no)));
	_list.push_back(new QStandardItem(name));

	if (full)
	{
		_list.push_back(new QStandardItem(QString::fromLocal8Bit("满载")));
	}
	else
	{
		_list.push_back(new QStandardItem(QString::fromLocal8Bit("空闲")));
	}

	m_model->appendRow(_list);

	for (QList<QStandardItem*>::iterator it = _list.begin(); it != _list.end(); ++it)
	{
		(*it)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		(*it)->setEditable(false);
		(*it)->setToolTip((*it)->text());
	}

	return true;
}

void ShipmentPortForm::DeleteShipmentPort(quint8 no)
{
	if (no <= 0 || no >= 255)
	{
		return;
	}

	// 从列表中删除该编号的出货口
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

bool ShipmentPortForm::EditShipmentPort(quint8 no, QString name)
{
	if (no <= 0 || no >= 255)
	{
		return false;
	}

	// 修改列表中该编号的出货口属性
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text().toInt() != no)
		{
			continue;
		}

		m_model->item(i, 1)->setText(name);
	}

	return true;
}

bool ShipmentPortForm::EditShipmentPort(quint8 no, bool full)
{
	if (no <= 0 || no >= 255)
	{
		return false;
	}

	// 修改列表中该编号的出货口属性
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text().toInt() != no)
		{
			continue;
		}

		if (full)
		{
			m_model->item(i, 2)->setText(QString::fromLocal8Bit("满载"));
		}
		else
		{
			m_model->item(i, 2)->setText(QString::fromLocal8Bit("空闲"));
		}

	}

	return true;
}

bool ShipmentPortForm::EditShipmentPort(quint8 no, QString name, bool full)
{
	if (no <= 0 || no >= 255)
	{
		return false;
	}

	// 修改列表中该编号的出货口属性
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text().toInt() != no)
		{
			continue;
		}

		m_model->item(i, 1)->setText(name);

		if (full)
		{
			m_model->item(i, 2)->setText(QString::fromLocal8Bit("满载"));
		}
		else
		{
			m_model->item(i, 2)->setText(QString::fromLocal8Bit("空闲"));
		}

	}

	return true;
}

void ShipmentPortForm::Clear()
{
	m_model->clear();

	// 为模板设置列头
	int _index = 0;
	// 为分盘机模板设置列头
	m_model->setColumnCount(3);
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("序号"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("名称"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("状态"));

	return;
}

bool ShipmentPortForm::IsVaild(quint8 no)
{
	if (no <= 0 || no >= 255)
	{
		return false;
	}

	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text().toInt() != no)
		{
			continue;
		}

		return true;

	}

	return false;
}

bool ShipmentPortForm::IsVaild(quint8 no, QString& name, bool& full)
{
	if (no <= 0 || no >= 255)
	{
		return false;
	}

	// 修改列表中该编号的出货口属性
	for (int i = 0; i < m_model->rowCount(); ++i)
	{
		QStandardItem* _aItem = m_model->item(i);

		if (_aItem->text().toInt() != no)
		{
			continue;
		}

		name = m_model->item(i, 1)->text();

		if (m_model->item(i, 2)->text() == QString::fromLocal8Bit("满载"))
		{
			full = true;
		}
		else
		{
			full = false;
		}
	}

	return true;
}
