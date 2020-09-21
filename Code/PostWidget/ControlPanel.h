#pragma once

#include <QWidget>

namespace Ui
{
	class ControlPanel;
}

class GraphWidget;

class ControlPanel : public QWidget
{
	Q_OBJECT

public:
	ControlPanel(GraphWidget * gw);
	~ControlPanel();

	void openFile(QString f);

private slots:
	void on_viewChanged(int index);
	void on_variableChanged(int index);
	void on_displayChanged(int index);

private:
	void updateVariableCombox(QStringList pvas, QStringList cvas);

private:
	Ui::ControlPanel* _ui{};
	GraphWidget* _graphWidget{};
};