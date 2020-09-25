#pragma  once

#include <QVTKWidget.h>
#include <vtkAutoInit.h>
#include <vtkSmartPointer.h>
#include <QHash>

VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkRenderingContextOpenGL2);
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
VTK_MODULE_INIT(vtkRenderingGL2PSOpenGL2);

class vtkRenderer;
class vtkRenderWindow;
class vtkRenderWindowInteractor;
class vtkOrientationMarkerWidget;
class vtkScalarBarWidget;
class vtkDataSet;
class vtkActor;

class GraphWidget : public QVTKWidget
{
public:
	GraphWidget();
	~GraphWidget() = default;

	void setView(int, int, int);
	void fitView();
	void viewCounter(vtkDataSet* data , QString variable, int vatype);
	void setDisplay(int type);
	void savePic(QString filename);
	void clearActors();
private:
	void initAxis();
	void initLegand();

private:
	vtkSmartPointer<vtkRenderer> _render{};
	vtkSmartPointer<vtkRenderWindow> _renderWindow{};
	vtkSmartPointer<vtkRenderWindowInteractor> _interactor{};
	vtkSmartPointer<vtkOrientationMarkerWidget> _axesWidget{};
	vtkSmartPointer<vtkScalarBarWidget> _scalarBarWidget{};

	QHash<vtkDataSet*, vtkActor*> _actoors{};
};