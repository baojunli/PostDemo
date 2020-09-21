#include "PostWidget.h"
#include "ControlPanel.h"
#include "GraphWidget.h"
#include <QHBoxLayout>

QWidget* PostWidget::_controlPanel = nullptr;
QWidget* PostWidget::_graphWidget = nullptr;
QWidget* PostWidget::_whole = nullptr;

void PostWidget::init()
{
	auto g = new GraphWidget;
	_controlPanel = new ControlPanel(g);
	_graphWidget = g;

	_whole = new QWidget;
	QHBoxLayout* lay = new QHBoxLayout;
	lay->addWidget(_controlPanel);
	lay->addWidget(_graphWidget);
	_whole->setLayout(lay);
}

QWidget * PostWidget::getGraphWidget()
{
	return _graphWidget;
}

QWidget * PostWidget::getControlPanel()
{
	return _controlPanel;
}

void PostWidget::openFile(const QString file)
{
	if (_controlPanel == nullptr || _graphWidget == nullptr) return;
	auto c = dynamic_cast<ControlPanel*>(_controlPanel);
	c->openFile(file);
}

QWidget* PostWidget::getWhole()
{
	return _whole;

}
