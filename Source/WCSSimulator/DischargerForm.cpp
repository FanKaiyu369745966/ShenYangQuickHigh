#include "DischargerForm.h"

#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QStandardItemModel>

DischargerForm::DischargerForm(QWidget* parent)
	: QWidget(parent)
{
	//ui.setupUi(this);
	Initialize();
}

DischargerForm::~DischargerForm()
{
}

void DischargerForm::Initialize()
{
	QPushButton* _pbutAdd = new QPushButton(QString::fromLocal8Bit("添加"), this);		/*!< 添加按钮 */
	QPushButton* _pbutEdit = new QPushButton(QString::fromLocal8Bit("修改"), this);			/*!< 编辑按钮 */
	QPushButton* _pbutDel = new QPushButton(QString::fromLocal8Bit("删除"), this);			/*!< 删除按钮 */
	QLabel* _labNo = new QLabel(QString::fromLocal8Bit("序号："), this);					/*!< 序号标签 */
	QLabel* _labAddr = new QLabel(QString::fromLocal8Bit("地址："), this);					/*!< 地址标签 */
	//QLabel* _labStatus = new QLabel(QString::fromLocal8Bit("状态："), this);				/*!< 状态标签 */
	QLineEdit* _leditNo = new QLineEdit(this);												/*!< 序号编辑框 */
	QLineEdit* _leditAddr = new QLineEdit(this);											/*!< 地址编辑框 */
	//QComboBox* _combStatus = new QComboBox(this);											/*!< 状态下拉列表 */

	QTableView* _table = new QTableView(this);												/*!< 表单控件 */

	QHBoxLayout* _hlay = new QHBoxLayout();													/*!< 水平布局 */
	QVBoxLayout* _vlay = new QVBoxLayout();													/*!< 垂直布局 */

	// 为布局添加控件
	_hlay->addWidget(_labNo);
	_hlay->addWidget(_leditNo);
	_hlay->addWidget(_labAddr);
	_hlay->addWidget(_leditAddr);
	_hlay->addWidget(_pbutAdd);
	_hlay->addWidget(_pbutEdit);
	_hlay->addWidget(_pbutDel);

	_vlay->addLayout(_hlay);
	_vlay->addWidget(_table);

	setLayout(_vlay);

	// 增加编辑框提示信息
	_leditNo->setPlaceholderText(QString::fromLocal8Bit("仅支持>0并且<255的数字"));
	_leditAddr->setPlaceholderText(QString::fromLocal8Bit("地址:端口 例如:127.0.0.1:8008"));

	QStandardItemModel* _model = new QStandardItemModel();	/*!< 分盘机表单成员模板 */

	// 为模板设置列头
	int _index = 0;
	// 为分盘机模板设置列头
	_model->setColumnCount(4);
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("序号"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("地址"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("连接"));
	_model->setHeaderData(_index++, Qt::Horizontal, QString::fromLocal8Bit("状态"));

	_table->setModel(_model);

	return;
}
