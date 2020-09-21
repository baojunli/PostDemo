#include "ControlPanel.h"
#include "PostData/PostData.h"
#include "ui_ControlPanel.h"
#include "GraphWidget.h"
#include <QDebug>
#include <QFileDialog>
#include <QString>
#include <vtkExodusIIReader.h>
#include <vtkDataSet.h>


ControlPanel::ControlPanel(GraphWidget* gw)
	:_graphWidget(gw)
{
	_ui = new Ui::ControlPanel;
	_ui->setupUi(this);
	connect(_ui->ViewComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_viewChanged(int)));
	connect(_ui->VariableComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_variableChanged(int)));
	connect(_ui->DiaplayComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_displayChanged(int)));
}

ControlPanel::~ControlPanel()
{
	if (_ui != nullptr) delete _ui;
}

void ControlPanel::openFile(QString f)
{
	bool ok = PostData::getInstance()->read(f);
	if (!ok) return;
	QStringList names = PostData::getInstance()->getVariableName();
	updateVariableCombox(names);

	QString va = _ui->VariableComboBox->currentText();
	vtkDataObject* obj = PostData::getInstance()->getData();
	vtkDataSet* data = vtkDataSet::SafeDownCast(obj);
	_graphWidget->viewCounter(data, va);

}

void ControlPanel::on_viewChanged(int index)
{
	int view[3] = { 0,0,0 };
	switch (index)
	{
	case 0:
		_graphWidget->fitView();
		return;
	case 1: view[0] = 1; break;
	case 2: view[0] = -1; break;
	case 3: view[1] = 1; break;
	case 4: view[1] = -1; break;
	case 5: view[2] = 1; break;
	case 6: view[2] = -1; break;
	}
	_graphWidget->setView(view[0], view[1], view[2]);
}

void ControlPanel::on_variableChanged(int index)
{
	QString va = _ui->VariableComboBox->currentText();
	vtkDataSet* obj = PostData::getInstance()->getData();
//	vtkDataSet* data = vtkDataSet::SafeDownCast(obj);
	_graphWidget->viewCounter(obj, va);
}

void ControlPanel::on_displayChanged(int index)
{
	_graphWidget->setDisplay(index);
}

void ControlPanel::updateVariableCombox(QStringList vas)
{
	_ui->VariableComboBox->clear();
	_ui->VariableComboBox->addItems(vas);

}

