#include "OrderForm.h"

#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QTableWidget>
#include <QStandardItemModel>

OrderForm::OrderForm(QWidget* parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	Initialize();
}

OrderForm::~OrderForm()
{
}

void OrderForm::Initialize()
{
	QPushButton* _pbutAdd = new QPushButton(QString::fromLocal8Bit("添加"), this);			/*!< 添加按钮 */
	QPushButton* _pbutEdit = new QPushButton(QString::fromLocal8Bit("修改"), this);			/*!< 编辑按钮 */
	QPushButton* _pbutDel = new QPushButton(QString::fromLocal8Bit("删除"), this);			/*!< 删除按钮 */
	QPushButton* _pbutSel = new QPushButton(QString::fromLocal8Bit("选择"), this);			/*!< 选择按钮 */
	QLabel* _labNo = new QLabel(QString::fromLocal8Bit("订单号："), this);					/*!< 订单号标签 */
	QLabel* _labTray = new QLabel(QString::fromLocal8Bit("托盘码："), this);				/*!< 托盘码标签 */
	QLabel* _labSort = new QLabel(QString::fromLocal8Bit("分拣台："), this);				/*!< 分拣台标签 */
	QLabel* _labShipment = new QLabel(QString::fromLocal8Bit("出货口："), this);			/*!< 出货口标签 */
	QLineEdit* _leditNo = new QLineEdit(this);												/*!< 订单号编辑框 */
	QLineEdit* _leditTary = new QLineEdit(this);											/*!< 托盘码编辑框 */
	QLineEdit* _leditSort = new QLineEdit(this);											/*!< 分拣台编辑框 */
	QCheckBox* _cbutAuto = new QCheckBox(QString::fromLocal8Bit("自动生成"), this);			/*!< 自动生成订单号按钮 */
	QComboBox* _combShipment = new QComboBox(this);											/*!< 出货口选项卡 */

	QTableView* _table = new QTableView(this);												/*!< 表单控件 */

	QHBoxLayout* _hlay = new QHBoxLayout();													/*!< 水平布局 */
	QVBoxLayout* _vlay = new QVBoxLayout();													/*!< 垂直布局 */

	// 为布局添加控件
	_hlay->addWidget(_labNo);
	_hlay->addWidget(_leditNo);
	_hlay->addWidget(_cbutAuto);
	_hlay->addWidget(_labTray);
	_hlay->addWidget(_leditTary);
	_hlay->addWidget(_labSort);
	_hlay->addWidget(_leditSort);
	_hlay->addWidget(_pbutSel);
	_hlay->addWidget(_labShipment);
	_hlay->addWidget(_combShipment);

	_hlay->addWidget(_pbutAdd);
	_hlay->addWidget(_pbutEdit);
	_hlay->addWidget(_pbutDel);

	_vlay->addLayout(_hlay);
	_vlay->addWidget(_table);

	setLayout(_vlay);

	// 增加编辑框提示信息
	_leditSort->setPlaceholderText(QString::fromLocal8Bit("使用:分割分拣台。例如：1:2:3:4。"));

	// 设置下拉列表样式
	_combShipment->setEditable(true);

	QStandardItemModel* _model = new QStandardItemModel();	/*!< 分盘机表单成员模板 */

	// 为模板设置列头
	int _index = 0;
	// 为分盘机模板设置列头
	_model->setColumnCount(9);
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("订单号"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("托盘码"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("分盘机"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("分拣台"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("出货口"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("执行者"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("状态"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("下单时间"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("完成时间"));

	_table->setModel(_model);

	return;
}
