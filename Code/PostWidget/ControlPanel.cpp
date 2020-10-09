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
	connect(PostData::getInstance(), SIGNAL(readFinished()), this, SLOT(onReadFinish()));
}

ControlPanel::~ControlPanel()
{
	if (_ui != nullptr) delete _ui;
}

void ControlPanel::openFile(QString f)
{
	PostData::getInstance()->read(f);
	

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
	int typeInt = _ui->VariableComboBox->currentData().toInt();
	vtkDataSet* obj = PostData::getInstance()->getData();
	vtkDataSet* data = vtkDataSet::SafeDownCast(obj);
	_graphWidget->viewCounter(obj, va, typeInt);
}

void ControlPanel::on_displayChanged(int index)
{
	_graphWidget->setDisplay(index);
}

void ControlPanel::on_ImagButton_clicked()
{
	QString f = QFileDialog::getSaveFileName(this, "Save Pic", "", "PNG(*.png)");
	_graphWidget->savePic(f);
}

void ControlPanel::onReadFinish()
{
	if (PostData::getInstance()->getData() == nullptr) return;

	QStringList pointVariables = PostData::getInstance()->getVariableName();
	QStringList cellVariables = PostData::getInstance()->getVariableName(1);

	updateVariableCombox(pointVariables, cellVariables);
	on_variableChanged(0);
}

void ControlPanel::updateVariableCombox(QStringList pvas, QStringList cvas)
{
	_ui->VariableComboBox->blockSignals(true);
	_ui->VariableComboBox->clear();
	
	for (QString va : pvas)
	{
		_ui->VariableComboBox->addItem(QIcon(""), va, 0);
	}
	for (QString va : cvas)
	{
		_ui->VariableComboBox->addItem(QIcon(""), va, 1);
	}
	_ui->VariableComboBox->blockSignals(false);
}

