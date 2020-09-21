#pragma once
#include "PostWidgetAPI.h"
#include <QString>

class QWidget;

class PostWidgetAPI  PostWidget
{
public:
	static void init();
	static QWidget* getGraphWidget();
	static QWidget* getControlPanel();
	static void openFile(const QString file);
	static QWidget* getWhole();

private:
	static QWidget* _graphWidget;
	static QWidget* _controlPanel;
	static QWidget* _whole;
};