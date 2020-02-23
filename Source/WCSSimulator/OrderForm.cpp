#include "OrderForm.h"

#include <chrono>
#include <cstdio>
#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>

OrderForm::OrderForm(QWidget* parent)
	: QWidget(parent)
	, m_pbutAdd(nullptr)
	//, m_pbutEdit(nullptr)
	, m_pbutDel(nullptr)
	, m_leditNo(nullptr)
	, m_leditTary(nullptr)
	, m_model(nullptr)
	, m_strOrder("")
	, m_strTray("")
	, m_strShipmentPort("")
{
	//ui.setupUi(this);
	Initialize();
}

OrderForm::~OrderForm()
{
}

void OrderForm::Initialize()
{
	m_pbutAdd = new QPushButton(QString::fromLocal8Bit("添加"), this);						/*!< 添加按钮 */
	//m_pbutEdit = new QPushButton(QString::fromLocal8Bit("修改"), this);						/*!< 编辑按钮 */
	m_pbutDel = new QPushButton(QString::fromLocal8Bit("删除"), this);						/*!< 删除按钮 */
	QPushButton* _pbutSel = new QPushButton(QString::fromLocal8Bit("选择"), this);			/*!< 选择按钮 */
	QLabel* _labNo = new QLabel(QString::fromLocal8Bit("订单号："), this);					/*!< 订单号标签 */
	QLabel* _labTray = new QLabel(QString::fromLocal8Bit("托盘码："), this);				/*!< 托盘码标签 */
	QLabel* _labSort = new QLabel(QString::fromLocal8Bit("分拣台："), this);				/*!< 分拣台标签 */
	QLabel* _labShipment = new QLabel(QString::fromLocal8Bit("出货口："), this);			/*!< 出货口标签 */
	m_leditNo = new QLineEdit(this);														/*!< 订单号编辑框 */
	m_leditTary = new QLineEdit(this);														/*!< 托盘码编辑框 */
	m_leditSort = new QLineEdit(this);														/*!< 分拣台编辑框 */
	QCheckBox* _cbutAuto = new QCheckBox(QString::fromLocal8Bit("自动生成"), this);			/*!< 自动生成订单号按钮 */
	m_leditShipment = new QLineEdit(this);													/*!< 出货口编辑框 */

	QTableView* _table = new QTableView(this);												/*!< 表单控件 */

	QHBoxLayout* _hlay = new QHBoxLayout();													/*!< 水平布局 */
	QVBoxLayout* _vlay = new QVBoxLayout();													/*!< 垂直布局 */

	// 为布局添加控件
	_hlay->addWidget(_labNo);
	_hlay->addWidget(m_leditNo);
	_hlay->addWidget(_cbutAuto);
	_hlay->addWidget(_labTray);
	_hlay->addWidget(m_leditTary);
	_hlay->addWidget(_labSort);
	_hlay->addWidget(m_leditSort);
	_hlay->addWidget(_pbutSel);
	_hlay->addWidget(_labShipment);
	_hlay->addWidget(m_leditShipment);

	_hlay->addWidget(m_pbutAdd);
	//_hlay->addWidget(m_pbutEdit);
	_hlay->addWidget(m_pbutDel);

	_vlay->addLayout(_hlay);
	_vlay->addWidget(_table);

	setLayout(_vlay);

	// 增加编辑框提示信息
	m_leditSort->setPlaceholderText(QString::fromLocal8Bit("使用:分割分拣台编号。例如：1:2:3:4。"));
	m_leditShipment->setPlaceholderText(QString::fromLocal8Bit("仅支持>0并且<255的数字"));

	// 设置下拉列表样式
	//_combShipment->setEditable(true);

	m_model = new QStandardItemModel();	/*!< 分盘机表单成员模板 */

	// 为模板设置列头
	int _index = 0;
	// 为分盘机模板设置列头
	m_model->setColumnCount(9);
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("订单号"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("托盘码"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("分盘机"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("分拣台"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("出货口"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("执行者"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("状态"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("下单时间"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("完成时间"));

	QItemSelectionModel* _selModel = new QItemSelectionModel(m_model);

	_table->setModel(m_model);
	_table->setSelectionModel(_selModel);
	_table->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	_table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

	// 为控件添加信号和槽函数
	QObject::connect(_cbutAuto, &QCheckBox::toggled, this, &OrderForm::OnClickCheckButton);
	QObject::connect(m_leditNo, &QLineEdit::editingFinished, this, &OrderForm::EditFinished);
	QObject::connect(m_leditTary, &QLineEdit::editingFinished, this, &OrderForm::EditFinished);
	QObject::connect(m_leditSort, &QLineEdit::editingFinished, this, &OrderForm::EditFinished);
	QObject::connect(m_leditShipment, &QLineEdit::editingFinished, this, &OrderForm::EditFinished);
	QObject::connect(m_pbutAdd, &QPushButton::pressed, this, &OrderForm::PressedAddButton);
	QObject::connect(m_pbutDel, &QPushButton::pressed, this, &OrderForm::PressedDeleteButton);
	//QObject::connect(m_pbutEdit, &QPushButton::pressed, this, &OrderForm::PressedEditButton);
	QObject::connect(_selModel, &QItemSelectionModel::currentChanged, this, &OrderForm::OnSelectItem);
	QObject::connect(_pbutSel, &QPushButton::pressed, this, &OrderForm::PressedSelectButton);
	return;
}

void OrderForm::OnClickCheckButton(bool checked)
{
	if (checked)
	{
		using namespace std;

		chrono::system_clock::time_point tpCur = chrono::system_clock::now();

		time_t tt = chrono::system_clock::to_time_t(tpCur);
		tm* t = localtime(&tt);

		auto timeNow = chrono::duration_cast<chrono::milliseconds>(tpCur.time_since_epoch());

		QString str = QString("%1%2%3%4%5%6%7")
			.arg(t->tm_year + 1900, 4, 10, QLatin1Char('0'))
			.arg(t->tm_mon + 1, 2, 10, QLatin1Char('0'))
			.arg(t->tm_mday, 2, 10, QLatin1Char('0'))
			.arg(t->tm_hour, 2, 10, QLatin1Char('0'))
			.arg(t->tm_min, 2, 10, QLatin1Char('0'))
			.arg(t->tm_sec, 2, 10, QLatin1Char('0'))
			.arg(timeNow.count() % 1000, 3, 10, QLatin1Char('0'));

		m_leditNo->setText(QString("%1").arg(str, 18, QLatin1Char('0')));

		m_leditNo->setReadOnly(true);

		m_strOrder = m_leditNo->text();
	}
	else
	{
		m_leditNo->setReadOnly(false);
	}

	return;
}

void OrderForm::EditFinished()
{
	m_strOrder = m_leditNo->text();
	m_strTray = m_leditTary->text();
	m_strlSortTable = m_leditSort->text().split(';');
	m_strShipmentPort = m_leditShipment->text();

	return;
}

void OrderForm::PressedAddButton()
{
}

void OrderForm::PressedDeleteButton()
{
}

void OrderForm::OnSelectItem(const QModelIndex& current, const QModelIndex& previous)
{
	if (current.isValid())
	{
		// 将单元格的内容填入属性配置信息中

		m_leditNo->setText(m_model->item(current.row(), 0)->text());

		m_leditTary->setText(m_model->item(current.row(), 1)->text());

		m_leditSort->setText(m_model->item(current.row(), 3)->text());

		m_leditShipment->setText(m_model->item(current.row(), 4)->text());
	}

	m_strOrder = m_leditNo->text();
	m_strTray = m_leditTary->text();
	m_strlSortTable = m_leditSort->text().split(';');
	m_strShipmentPort = m_leditShipment->text();

	return;
}

void OrderForm::PressedSelectButton()
{
	QDialog* _dialog = new QDialog(this);
	_dialog->setWindowTitle(QString::fromLocal8Bit("选择分捡台"));
	_dialog->setMinimumSize(200, 200);
	_dialog->setMaximumSize(800, 600);

	QGroupBox* _gbox = new QGroupBox(QString::fromLocal8Bit("分捡台"), _dialog);
	_gbox->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	QDialogButtonBox* _dbutbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Orientation::Horizontal, _dialog);
	//QPushButton* _pbutCancel = new QPushButton(QString::fromLocal8Bit("取消"), _dialog);

	_dbutbox->setCenterButtons(true);

	QHBoxLayout* _layoutCheck = new QHBoxLayout();

	QMap<quint8, QCheckBox*> _mapCheckSort;

	for (QSet<quint8>::iterator it = m_setSort.begin(); it != m_setSort.end(); ++it)
	{
		quint8 _no = *it;

		_mapCheckSort[_no] = new QCheckBox(QString::fromLocal8Bit("分捡台%1").arg(_no), _dialog);

		_layoutCheck->addWidget(_mapCheckSort[_no]);
	}

	_gbox->setLayout(_layoutCheck);

	QVBoxLayout* _layoutMain = new QVBoxLayout();

	_layoutMain->addWidget(_gbox);
	_layoutMain->addWidget(_dbutbox);

	_dialog->setLayout(_layoutMain);

	for (QStringList::iterator it = m_strlSortTable.begin(); it != m_strlSortTable.end(); ++it)
	{
		quint8 _no = it->toInt();

		if (_mapCheckSort.find(_no) == _mapCheckSort.end())
		{
			continue;
		}

		_mapCheckSort[_no]->setChecked(true);
	}

	QObject::connect(_dbutbox, &QDialogButtonBox::accepted, _dialog, &QDialog::accept);
	QObject::connect(_dbutbox, &QDialogButtonBox::rejected, _dialog, &QDialog::reject);

	int result = _dialog->exec();

	if (result == 0)
	{
		delete _dialog;
		return;
	}

	// 将选中的分捡台，填入编辑框中
	QString _list = "";

	for (QMap<quint8, QCheckBox*>::iterator it = _mapCheckSort.begin(); it != _mapCheckSort.end(); ++it, _list += ";")
	{
		quint8 _no = it.key();

		if (it.value()->isChecked() == false)
		{
			continue;
		}

		_list += QString::fromLocal8Bit("%1").arg(_no);
	}

	m_leditSort->setText(_list);
	m_strlSortTable = m_leditSort->text().split(';');

	delete _dialog;

	return;
}

void OrderForm::AddNewSortTable(quint8 no)
{
	if (m_setSort.find(no) != m_setSort.end())
	{
		return;
	}

	m_setSort.insert(no);

	return;
}

void OrderForm::DeleteSortTable(quint8 no)
{
	if (m_setSort.find(no) == m_setSort.end())
	{
		return;
	}

	m_setSort.erase(m_setSort.find(no));

	return;
}
