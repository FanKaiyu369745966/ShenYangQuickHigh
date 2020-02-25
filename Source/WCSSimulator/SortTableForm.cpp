#include "SortTableForm.h"

SortTableForm::SortTableForm(QWidget* parent)
	: QWidget(parent)
	, m_pbutAdd(nullptr)
	, m_pbutEdit(nullptr)
	, m_pbutDel(nullptr)
	, m_leditNo(nullptr)
	, m_leditName(nullptr)
	, m_model(nullptr)
	, m_byNo(0)
	, m_strName("")
{
	//ui.setupUi(this);
	Initialize();
}

SortTableForm::~SortTableForm()
{
}

void SortTableForm::Initialize()
{
	m_pbutAdd = new QPushButton(QString::fromLocal8Bit("添加"), this);						/*!< 添加按钮 */
	m_pbutEdit = new QPushButton(QString::fromLocal8Bit("修改"), this);						/*!< 编辑按钮 */
	m_pbutDel = new QPushButton(QString::fromLocal8Bit("删除"), this);						/*!< 删除按钮 */
	QLabel* _labNo = new QLabel(QString::fromLocal8Bit("序号："), this);					/*!< 序号标签 */
	QLabel* _labName = new QLabel(QString::fromLocal8Bit("名称："), this);					/*!< 名称标签 */
	m_leditNo = new QLineEdit(this);														/*!< 序号编辑框 */
	m_leditName = new QLineEdit(this);														/*!< 地址编辑框 */

	QTableView* _table = new QTableView(this);												/*!< 表单控件 */

	QHBoxLayout* _hlay = new QHBoxLayout();													/*!< 水平布局 */
	QVBoxLayout* _vlay = new QVBoxLayout();													/*!< 垂直布局 */

	// 为布局添加控件
	_hlay->addWidget(_labNo);
	_hlay->addWidget(m_leditNo);
	_hlay->addWidget(_labName);
	_hlay->addWidget(m_leditName);
	_hlay->addWidget(m_pbutAdd);
	_hlay->addWidget(m_pbutEdit);
	_hlay->addWidget(m_pbutDel);

	_vlay->addLayout(_hlay);
	_vlay->addWidget(_table);

	setLayout(_vlay);

	// 增加编辑框提示信息
	m_leditNo->setPlaceholderText(QString::fromLocal8Bit("仅支持>0并且<255的数字"));

	m_model = new QStandardItemModel();	/*!< 分盘机表单成员模板 */

	// 为模板设置列头
	int _index = 0;
	// 为分盘机模板设置列头
	m_model->setColumnCount(2);
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("序号"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("名称"));

	QItemSelectionModel* _selModel = new QItemSelectionModel(m_model);

	_table->setModel(m_model);
	_table->setSelectionModel(_selModel);
	_table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	_table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

	// 为控件添加信号和槽函数
	QObject::connect(m_leditNo, &QLineEdit::editingFinished, this, &SortTableForm::EditFinished);
	QObject::connect(m_leditName, &QLineEdit::editingFinished, this, &SortTableForm::EditFinished);
	QObject::connect(m_pbutAdd, &QPushButton::pressed, this, &SortTableForm::PressedAddButton);
	QObject::connect(m_pbutDel, &QPushButton::pressed, this, &SortTableForm::PressedDeleteButton);
	QObject::connect(m_pbutEdit, &QPushButton::pressed, this, &SortTableForm::PressedEditButton);
	QObject::connect(_selModel, &QItemSelectionModel::currentChanged, this, &SortTableForm::OnSelectItem);

	return;
}

void SortTableForm::EditFinished()
{
	m_byNo = m_leditNo->text().toInt();
	m_strName = m_leditName->text();

	return;
}

void SortTableForm::PressedAddButton()
{
	if (m_byNo <= 0 || m_byNo >= 255)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加分捡台"), QString::fromLocal8Bit("添加分捡台失败！无效的分捡台编号。\n注意：编号仅支持大于0且小于255的值。"));
		return;
	}

	bool _result = false;

	emit AddNewSortTable(_result);

	if (_result == false)
	{
		return;
	}

	AddNewSortTable(m_byNo, m_strName);

	return;
}

void SortTableForm::PressedDeleteButton()
{
	if (m_byNo <= 0 || m_byNo >= 255)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("删除分捡台"), QString::fromLocal8Bit("删除分捡台失败！无效的分捡台编号。\n注意：编号仅支持大于0且小于255的值。"));
		return;
	}

	bool _result = false;

	emit DeleteSortTable(_result);

	if (_result == false)
	{
		return;
	}

	DeleteSortTable(m_byNo);

	m_byNo = m_leditNo->text().toInt();
	m_strName = m_leditName->text();

	return;
}

void SortTableForm::PressedEditButton()
{
	if (m_byNo <= 0 || m_byNo >= 255)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("编辑分捡台"), QString::fromLocal8Bit("编辑分捡台失败！无效的分捡台编号。\n注意：编号仅支持大于0且小于255的值。"));
		return;
	}

	bool _result = false;

	emit EditSortTable(_result);

	if (_result == false)
	{
		return;
	}

	EditSortTable(m_byNo, m_strName);

	return;
}

void SortTableForm::OnSelectItem(const QModelIndex& current, const QModelIndex& previous)
{
	if (current.isValid())
	{
		// 将单元格的内容填入属性配置信息中

		m_leditNo->setText(m_model->item(current.row(), 0)->text());

		m_leditName->setText(m_model->item(current.row(), 1)->text());
	}

	m_byNo = m_leditNo->text().toInt();
	m_strName = m_leditName->text();

	return;
}

bool SortTableForm::AddNewSortTable(quint8 no, QString name)
{
	if (no <= 0 || no >= 255)
	{
		return false;
	}

	// 向列表中添加分捡台
	QList<QStandardItem*> _list;
	_list.push_back(new QStandardItem(QString::fromLocal8Bit("%1").arg(no)));
	_list.push_back(new QStandardItem(name));

	m_model->appendRow(_list);

	for (QList<QStandardItem*>::iterator it = _list.begin(); it != _list.end(); ++it)
	{
		(*it)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		(*it)->setEditable(false);
		(*it)->setToolTip((*it)->text());
	}

	return true;
}

void SortTableForm::DeleteSortTable(quint8 no)
{
	if (no <= 0 || no >= 255)
	{
		return;
	}

	// 从列表中删除该编号的分捡台
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

bool SortTableForm::EditSortTable(quint8 no, QString name)
{
	if (no <= 0 || no >= 255)
	{
		return false;
	}

	// 修改列表中该编号的分捡台属性
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
