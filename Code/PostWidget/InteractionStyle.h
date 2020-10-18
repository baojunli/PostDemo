#pragma  once

#include <vtkInteractorStyleRubberBandPick.h>
#include <QObject>

class InteractionStyle : public QObject, public vtkInteractorStyleRubberBandPick
{
	Q_OBJECT
public:
	static InteractionStyle* New();
	vtkTypeMacro(InteractionStyle, vtkInteractorStyleRubberBandPick);



	void ctrlPress(bool p);

private:
	InteractionStyle() = default;
	~InteractionStyle() = default;

	void OnLeftButtonDown() override;
	void OnLeftButtonUp() override;

private:
	bool _ctrlPressed{ false };

};