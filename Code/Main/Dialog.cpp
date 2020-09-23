#include "Dialog.h"
#include "ui_dialog.h"
#include "Dialog.h"
#include "PostWidget/PostWidget.h"

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
	pw->openFile(f);
}

MainDialog::~MainDialog()
{
	if (_ui != nullptr) delete _ui;
}
