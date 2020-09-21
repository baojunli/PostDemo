#include "GraphWidget.h"
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkDataSetMapper.h>
#include <vtkPointData.h>
#include <vtkActor.h>
#include <vtkDataSet.h>
#include <vtkProperty.h>
#include <QDebug>
#include <vtkFloatArray.h>
#include <vtkUnstructuredGrid.h>
#include <vtkTextProperty.h>
#include <vtkScalarBarWidget.h>
#include <vtkScalarBarActor.h>
#include <vtkBorderRepresentation.h>
#include <vtkLookupTable.h>

GraphWidget::GraphWidget()
{
	_renderWindow = this->GetRenderWindow();
	_render = vtkSmartPointer<vtkRenderer>::New();
	_render->SetGradientBackground(true);
	_render->SetBackground2(0.0, 0.333, 1.0);
	_render->SetBackground(1.0, 1.0, 1.0);
	_renderWindow->AddRenderer(_render);
	_interactor = _renderWindow->GetInteractor();

	this->initAxis();
	this->initLegand();
}

void GraphWidget::setView(int xv, int yv, int zv)
{
	vtkCamera* c = _render->GetActiveCamera();
	c->SetViewUp(0, 0, 1);
	c->SetPosition(xv, yv, zv);
	c->SetFocalPoint(0, 0, 0);
	_render->ResetCamera();
	_renderWindow->Render();
}

void GraphWidget::fitView()
{
	_render->ResetCamera();
	_renderWindow->Render();
}


void GraphWidget::initAxis()
{
	vtkSmartPointer<vtkAxesActor> axesActor = vtkSmartPointer<vtkAxesActor>::New();
	_axesWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	_axesWidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
	_axesWidget->SetOrientationMarker(axesActor);
	_axesWidget->SetInteractor(_interactor);
	_axesWidget->SetViewport(0.0, 0.0, 0.2, 0.2);
	_axesWidget->SetEnabled(1);
	_axesWidget->InteractiveOff();
}

void GraphWidget::initLegand()
{
	vtkSmartPointer<vtkTextProperty> propLable = vtkSmartPointer<vtkTextProperty>::New();
	propLable->SetBold(0);
	propLable->SetItalic(0);
	propLable->SetShadow(0);
	propLable->SetJustification(VTK_TEXT_LEFT);
	propLable->SetColor(0, 0, 0);
	propLable->SetFontSize(14);

	vtkLookupTable *lut = vtkLookupTable::New();
	lut->SetNumberOfTableValues(50);
	//ÉèÖÃÑÕÉ«Ó³ÉäµÄ·¶Î§
	lut->SetTableRange(0, 10);
	lut->Build();

	_scalarBarWidget = vtkSmartPointer<vtkScalarBarWidget>::New();
	_scalarBarWidget->GetScalarBarActor()->SetVerticalTitleSeparation(1);
	_scalarBarWidget->GetScalarBarActor()->SetBarRatio(0.02);
	_scalarBarWidget->GetBorderRepresentation()->SetPosition(0.90, 0.05);
	_scalarBarWidget->GetBorderRepresentation()->SetPosition2(0.91, 0.45);
	_scalarBarWidget->GetBorderRepresentation()->SetShowBorderToOff();
	_scalarBarWidget->GetScalarBarActor()->SetTitleTextProperty(propLable);
	_scalarBarWidget->GetScalarBarActor()->SetLabelTextProperty(propLable);
	_scalarBarWidget->GetScalarBarActor()->SetUnconstrainedFontSize(true);
	_scalarBarWidget->GetScalarBarActor()->SetLookupTable(lut);
	_scalarBarWidget->SetInteractor(_interactor);
	_scalarBarWidget->Off();
}

void GraphWidget::viewCounter(vtkDataSet* data, QString variable)
{
 	qDebug() << variable;

	data->GetPointData()->SetActiveScalars(variable.toStdString().data());
	double* range = data->GetScalarRange();
	qDebug() << range[0] << "  " << range[1];
//	_scalarBarWidget->GetScalarBarActor()->SetTitle(variable.toStdString().data());
	vtkScalarsToColors* lut = _scalarBarWidget->GetScalarBarActor()->GetLookupTable();
	lut ->SetRange(range);
	_scalarBarWidget->On();

	if (_actoors.contains(data))
	{
 		vtkActor* actor = _actoors.value(data);
		actor->GetMapper()->SetLookupTable(lut);
		actor->GetMapper()->SetScalarRange(range);
	}
	else
	{
		vtkDataSetMapper* mapper = vtkDataSetMapper::New();
		mapper->SetInputData(data);
	    mapper->SetLookupTable(lut);
		mapper->SetScalarRange(range);
		vtkActor* ac = vtkActor::New();
		ac->SetMapper(mapper);
		_render->AddActor(ac);
		_render->ResetCamera();
		_actoors.insert(data, ac);
	}

	
	_renderWindow->Render();
}

void GraphWidget::setDisplay(int type)
{
	QList<vtkActor*> actorList = _actoors.values();
	for (vtkActor* ac : actorList)
	{
		auto prop = ac->GetProperty();
		switch (type)
		{
		case 0:
			prop->SetRepresentationToSurface();
			prop->EdgeVisibilityOff();
			break;
		case 1:
			prop->SetRepresentationToSurface();
			prop->EdgeVisibilityOn();
			break;
		case 2:
			prop->SetRepresentationToWireframe();
			break;
		case 3:
			prop->SetRepresentationToPoints();
			break;
		default:
			break;
		}
		_renderWindow->Render();
	}
}

void GraphWidget::savePic()
{
	
}
