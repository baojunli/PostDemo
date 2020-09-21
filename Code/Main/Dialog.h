#pragma once
#include <QDialog>

namespace Ui
{
	class Dialog;
}

class MainDialog : public QDialog
{
public:
	MainDialog();
	~MainDialog();

private:
	Ui::Dialog* _ui{};
};