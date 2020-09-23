#pragma once
#include "PostWidgetAPI.h"
#include <QString>

class QWidget;

class PostWidgetAPI  PostWidget
{
public:
	PostWidget();
	~PostWidget();

	 QWidget* getGraphWidget();
	 QWidget* getControlPanel();
	 void openFile(const QString file);
	 QWidget* getWhole();

private:
	void init();

private:
	QWidget* _graphWidget{};
	QWidget* _controlPanel{};
	QWidget* _whole{};
};