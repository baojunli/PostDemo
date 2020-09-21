#include "Dialog.h"
#include "ui_dialog.h"
#include "Dialog.h"
#include "PostWidget/PostWidget.h"

MainDialog::MainDialog()
{
	_ui = new Ui::Dialog;
	_ui->setupUi(this);
	PostWidget::init();
	auto c = PostWidget::getWhole();
//	auto g = PostWidget::getGraphWidget();
//	_ui->controlLayout->addWidget(c);
	_ui->graphLayout->addWidget(c);;
	
	QString f("F:\\PostDemo\\Code\\Main\\temp_022w.hot");
//	QString f("F:\\PostDemo\\Code\\Main\\yuanguan_temperature_exodus.e");
	PostWidget::openFile(f);
}

MainDialog::~MainDialog()
{
	if (_ui != nullptr) delete _ui;
}
