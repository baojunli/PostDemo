#pragma  once

#include <QThread>
#include <QString>
#include <QList>

class vtkMultiBlockDataSet;
class vtkDataObject;

class ReadThread: public QThread
{
public:
	ReadThread(const QString & file);
	~ReadThread();
	
private:
	void run()override;
	void mergeData(vtkMultiBlockDataSet* mulitData);
	void getDataObject(vtkMultiBlockDataSet* md, QList<vtkDataObject*>& dataList);


private:
	QString _fileName{};
};