#include "dialog.h"
#include <qapplication>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainDialog d;
	d.show();
	return app.exec();

}