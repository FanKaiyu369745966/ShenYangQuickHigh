#include "ServerForm.h"

#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

ServerForm::ServerForm(QWidget* parent)
	: QWidget(parent)
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
	QLineEdit* _leditAddr = new QLineEdit(this);											/*!< 服务端地址编辑栏 */
	QPushButton* _pbutListen = new QPushButton(QString::fromLocal8Bit("监听"), this);	/*!< 服务端监听按钮 */
	QPushButton* _pbutDetail = new QPushButton(QString::fromLocal8Bit("详情"), this);	/*!< 服务端详情按钮 */

	QHBoxLayout* _lay = new QHBoxLayout();												/*!< 服务端属性配置控件布局 */

	// 为服务端属性配置空格键布局添加控件
	_lay->addWidget(_labAddr);
	_lay->addWidget(_leditAddr);
	_lay->addWidget(_pbutListen);
	_lay->addWidget(_pbutDetail);

	setLayout(_lay);

	// 增加编辑框提示信息
	_leditAddr->setPlaceholderText(QString::fromLocal8Bit("地址:端口 例如:127.0.0.1:8008"));

	return;
}
