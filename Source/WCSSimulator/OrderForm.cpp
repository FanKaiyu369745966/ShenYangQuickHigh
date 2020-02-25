#include "OrderForm.h"

#include <chrono>
#include <cstdio>
#include <QDebug>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDateTime>

OrderForm::OrderForm(QWidget* parent)
	: QWidget(parent)
	, m_pbutAdd(nullptr)
	//, m_pbutEdit(nullptr)
	, m_pbutDel(nullptr)
	, m_leditNo(nullptr)
	, m_leditTary(nullptr)
	, m_table(nullptr)
	, m_model(nullptr)
	, m_strOrder("")
	, m_strTray("")
	, m_byShipmentPort(0)
	, m_database(QSqlDatabase::addDatabase("QODBC3", "Order"))
	, m_bSearch(false)
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
	//m_pbutEdit = new QPushButton(QString::fromLocal8Bit("修改"), this);					/*!< 编辑按钮 */
	m_pbutDel = new QPushButton(QString::fromLocal8Bit("删除"), this);						/*!< 删除按钮 */
	QPushButton* _pbutSel = new QPushButton(QString::fromLocal8Bit("选择"), this);			/*!< 选择按钮 */
	QLabel* _labNo = new QLabel(QString::fromLocal8Bit("订单号："), this);					/*!< 订单号标签 */
	QLabel* _labTray = new QLabel(QString::fromLocal8Bit("托盘码："), this);					/*!< 托盘码标签 */
	QLabel* _labSort = new QLabel(QString::fromLocal8Bit("分拣台："), this);					/*!< 分拣台标签 */
	QLabel* _labShipment = new QLabel(QString::fromLocal8Bit("出货口："), this);				/*!< 出货口标签 */
	m_leditNo = new QLineEdit(this);															/*!< 订单号编辑框 */
	m_leditTary = new QLineEdit(this);														/*!< 托盘码编辑框 */
	m_leditSort = new QLineEdit(this);														/*!< 分拣台编辑框 */
	QCheckBox* _cbutAuto = new QCheckBox(QString::fromLocal8Bit("自动生成"), this);			/*!< 自动生成订单号按钮 */
	m_leditShipment = new QLineEdit(this);													/*!< 出货口编辑框 */
	QPushButton* _pbutSearch = new QPushButton(QString::fromLocal8Bit("搜索"), this);		/*!< 搜索按钮 */

	m_table = new QTableView(this);															/*!< 表单控件 */

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

	_hlay->addWidget(_pbutSearch);
	_hlay->addWidget(m_pbutAdd);
	//_hlay->addWidget(m_pbutEdit);
	_hlay->addWidget(m_pbutDel);

	_vlay->addLayout(_hlay);
	_vlay->addWidget(m_table);

	setLayout(_vlay);

	// 增加编辑框提示信息
	m_leditSort->setPlaceholderText(QString::fromLocal8Bit("使用:分割分拣台编号。例如：1:2:3:4。"));
	m_leditShipment->setPlaceholderText(QString::fromLocal8Bit("仅支持>0并且<255的数字"));

	// 设置下拉列表样式
	//_combShipment->setEditable(true);

	m_model = new QStandardItemModel(this);

	// 为模板设置列头
	int _index = 0;

	m_model->setColumnCount(12);
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("订单号"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("任务号"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("托盘码"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("目的地"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("任务内容"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("执行者"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("状态"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("发布时间"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("执行时间"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("完成时间"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("异常信息"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("备注"));

	m_table->setModel(m_model);

	// 单选
	m_table->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
	// 选中整行
	m_table->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	// 自动拉伸
	m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

	// 不可编辑
	m_table->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

	// 为控件添加信号和槽函数
	QObject::connect(_cbutAuto, &QCheckBox::toggled, this, &OrderForm::OnClickCheckButton);
	QObject::connect(m_leditNo, &QLineEdit::editingFinished, this, &OrderForm::EditFinished);
	QObject::connect(m_leditTary, &QLineEdit::editingFinished, this, &OrderForm::EditFinished);
	QObject::connect(m_leditSort, &QLineEdit::editingFinished, this, &OrderForm::EditFinished);
	QObject::connect(m_leditShipment, &QLineEdit::editingFinished, this, &OrderForm::EditFinished);
	QObject::connect(m_pbutAdd, &QPushButton::pressed, this, &OrderForm::PressedAddButton);
	QObject::connect(m_pbutDel, &QPushButton::pressed, this, &OrderForm::PressedDeleteButton);
	//QObject::connect(m_pbutEdit, &QPushButton::pressed, this, &OrderForm::PressedEditButton);
	QObject::connect(_pbutSel, &QPushButton::pressed, this, &OrderForm::PressedSelectButton);
	QObject::connect(m_table, &QTableView::clicked, this, &OrderForm::OnSelectItem);
	QObject::connect(_pbutSearch, &QPushButton::pressed, this, &OrderForm::PressedSearchButton);
	QObject::connect(m_table, &QTableView::doubleClicked, this, &OrderForm::PressedSearchButton);

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
	m_byShipmentPort = m_leditShipment->text().toInt();

	if ((m_strOrder.isNull() || m_strOrder.isEmpty()) && (m_strTray.isNull() || m_strTray.isEmpty()))
	{
		m_bSearch = false;

		UpdateData();
		return;
	}

	return;
}

void OrderForm::PressedAddButton()
{
	if (m_strOrder.isNull() || m_strOrder.isEmpty())
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加订单"), QString::fromLocal8Bit("添加订单失败！无效的订单编号。"));
		return;
	}

	if (m_strlSortTable.size() == 0)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加订单"), QString::fromLocal8Bit("添加订单失败！未选择分捡台。"));
		return;
	}

	if (m_byShipmentPort <= 0 || m_byShipmentPort >= 255)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("添加订单"), QString::fromLocal8Bit("添加订单失败！无效的出货口编号。\n注意：编号仅支持大于0且小于255的值。"));
		return;
	}

	bool _result = false;

	emit AddNewOrder(_result);

	if (_result == false)
	{
		return;
	}

	UpdateData();

	return;
}

void OrderForm::PressedDeleteButton()
{
	if (m_strOrder.isNull() || m_strOrder.isEmpty())
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("删除订单"), QString::fromLocal8Bit("删除订单失败！无效的订单编号。"));
		return;
	}

	bool _result = false;

	emit DeleteOrder(_result);

	if (_result == false)
	{
		return;
	}

	UpdateData();

	m_strOrder = m_leditNo->text();
	m_strTray = m_leditTary->text();
	m_strlSortTable = m_leditSort->text().split(';');
	m_byShipmentPort = m_leditShipment->text().toInt();

	return;
}

void OrderForm::OnSelectItem(const QModelIndex& current)
{
	if (current.isValid())
	{
		// 将单元格的内容填入属性配置信息中
		m_leditNo->setText(m_model->item(current.row(), 0)->text());

		m_leditTary->setText(m_model->item(current.row(), 2)->text());

		m_leditSort->setText("");

		m_leditShipment->setText("");
	}

	m_strOrder = m_leditNo->text();
	m_strTray = m_leditTary->text();
	m_strlSortTable = m_leditSort->text().split(';');
	m_byShipmentPort = m_leditShipment->text().toInt();

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

	QGridLayout* _layoutCheck = new QGridLayout();

	QMap<quint8, QCheckBox*> _mapCheckSort;

	int row = 0, col = 0;

	for (QMap<quint8, QString>::iterator it = m_mapSort.begin(); it != m_mapSort.end(); ++it, ++col)
	{
		if (col == 5)
		{
			++row;
			col = 0;
		}

		quint8 _no = it.key();
		QString _name = it.value();

		if (_name.isNull() || _name.isEmpty())
		{
			_mapCheckSort[_no] = new QCheckBox(QString::fromLocal8Bit("分捡台%1").arg(_no), _dialog);
		}
		else
		{
			_mapCheckSort[_no] = new QCheckBox(QString::fromLocal8Bit("%1:%2").arg(_no).arg(_name), _dialog);
		}

		_layoutCheck->addWidget(_mapCheckSort[_no], row, col);
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

	for (QMap<quint8, QCheckBox*>::iterator it = _mapCheckSort.begin(); it != _mapCheckSort.end(); ++it)
	{
		quint8 _no = it.key();

		if (it.value()->isChecked() == false)
		{
			continue;
		}

		_list += ";";

		_list += QString::fromLocal8Bit("%1").arg(_no);
	}

	m_leditSort->setText(_list);
	m_strlSortTable = m_leditSort->text().split(';');

	delete _dialog;

	return;
}

void OrderForm::PressedSearchButton()
{
	m_bSearch = true;

	UpdateData();

	return;
}

void OrderForm::AddNewSortTable(quint8 no, QString name)
{
	if (m_mapSort.find(no) != m_mapSort.end())
	{
		return;
	}

	m_mapSort[no] = name;

	return;
}

void OrderForm::DeleteSortTable(quint8 no)
{
	if (m_mapSort.find(no) == m_mapSort.end())
	{
		return;
	}

	m_mapSort.erase(m_mapSort.find(no));

	return;
}

void OrderForm::UpdateData()
{
	if (m_database.isOpen() == false)
	{
		return;
	}

	QSqlQuery _query(m_database);

	QString _sql = "select * from AGVDB_TASK_CURRENT";

	if (m_bSearch)
	{
		bool _where = false;

		if (m_strOrder.isNull() == false && m_strOrder.isEmpty() == false)
		{
			if (_where == false)
			{
				_sql += " where ";

				_where = true;
			}
			else
			{
				_sql += " and ";
			}

			_sql += QString::fromLocal8Bit("task_order like '%%1%'").arg(m_strOrder);
		}

		if (m_strTray.isNull() == false && m_strTray.isEmpty() == false)
		{
			if (_where == false)
			{
				_sql += " where ";

				_where = true;
			}
			else
			{
				_sql += " and ";
			}

			_sql += QString::fromLocal8Bit(" and task_tray like '%%1%'").arg(m_strTray);
		}
	}

	if (_query.exec(_sql) == false)
	{
		return;
	}

	m_model->clear();

	// 为模板设置列头
	int _index = 0;

	m_model->setColumnCount(12);
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("订单号"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("任务号"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("托盘码"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("目的地"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("任务内容"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("执行者"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("状态"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("发布时间"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("执行时间"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("完成时间"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("异常信息"));
	m_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("备注"));

	//m_model->(0, m_model->rowCount());

	while (_query.next())
	{
		QList<QStandardItem*> _list;
		_list.push_back(new QStandardItem(_query.value("task_order").toString()));
		_list.push_back(new QStandardItem(QString::fromLocal8Bit("%1").arg(_query.value("task_id").toInt())));
		_list.push_back(new QStandardItem(_query.value("task_tray").toString()));
		_list.push_back(new QStandardItem(_query.value("task_target").toString()));
		_list.push_back(new QStandardItem(_query.value("task_mission").toString()));
		_list.push_back(new QStandardItem(QString::fromLocal8Bit("%1").arg(_query.value("task_executer").toInt())));
		_list.push_back(new QStandardItem(_query.value("task_status").toString()));
		_list.push_back(new QStandardItem(_query.value("task_publish").toDateTime().toString("yyyy/MM/dd hh:mm:ss:zzz")));
		_list.push_back(new QStandardItem(_query.value("task_execution").toDateTime().toString("yyyy/MM/dd hh:mm:ss:zzz")));
		_list.push_back(new QStandardItem(_query.value("task_finish").toDateTime().toString("yyyy/MM/dd hh:mm:ss:zzz")));
		_list.push_back(new QStandardItem(_query.value("task_error").toString()));
		_list.push_back(new QStandardItem(_query.value("task_log").toString()));

		m_model->appendRow(_list);

		for (QList<QStandardItem*>::iterator it = _list.begin(); it != _list.end(); ++it)
		{
			(*it)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			(*it)->setEditable(false);
			(*it)->setToolTip((*it)->text());
		}

	} while (_query.next());

	return;
}

void OrderForm::OpenDatabase(QString host, QString name, QString user, QString password)
{
	m_database.setDatabaseName(QString("DRIVER={SQL SERVER};"
		"SERVER=%1;"
		"DATABASE=%2;"
		"UID=%3;"
		"PWD=%4;").arg(host).arg(name).arg(user).arg(password));

	m_database.open();

	return;
}

void OrderForm::CloseDatabase()
{
	if (m_database.isOpen())
	{
		m_database.close();
	}

	return;
}
