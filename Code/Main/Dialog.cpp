#include "Dialog.h"
#include "ui_dialog.h"
#include "Dialog.h"
#include "PostWidget/PostWidget.h"
#include <QTime>
#include <qdebug>

MainDialog::MainDialog()
{
	_ui = new Ui::Dialog;
	_ui->setupUi(this);
	auto pw = new PostWidget;
	auto c = pw->getWhole();
//	auto g = Post1Widget::getGraphWidget();
//	_ui->controlLayout->addWidget(c);
	_ui->graphLayout->addWidget(c);;
	
//	QString f("F:\\PostDemo\\Code\\Main\\temp_022w.hot");
	QString f("F:\\PostDemo\\Code\\Main\\yuanguan_temperature_exodus.e");
//	QString f("E:\\wangfan_stress_master_exodus.e");
	qDebug() << QTime::currentTime();
	pw->openFile(f);
	qDebug() << QTime::currentTime();

}

MainDialog::~MainDialog()
{
	if (_ui != nullptr) delete _ui;
}
