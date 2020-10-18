#include "InteractionStyle.h"

InteractionStyle* InteractionStyle::New()
{
	return new InteractionStyle;
}

void InteractionStyle::ctrlPress(bool p)
{
	_ctrlPressed = p;
}

void InteractionStyle::OnLeftButtonDown()
{
	if (_ctrlPressed)
		vtkInteractorStyleRubberBandPick::OnLeftButtonDown();
	else
		vtkInteractorStyleRubberBandPick::OnMiddleButtonDown();
}

void InteractionStyle::OnLeftButtonUp()
{
	vtkInteractorStyleRubberBandPick::OnMiddleButtonUp();
	vtkInteractorStyleRubberBandPick::OnLeftButtonUp();
}

