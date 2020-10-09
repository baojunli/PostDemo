#pragma  once

#include "PostDataAPI.h"
#include <QStringList>
#include <QObject>

class vtkMultiBlockDataSet;
class vtkDataSet;
class vtkDataObject;
class  ReadThread;

class PostDataAPI PostData : public QObject
{
	Q_OBJECT

public :
	static PostData* getInstance();
	
	//读取文件
	void read(const QString& file);
	void setData(vtkDataSet* data);
	//获取数据
	vtkDataSet* getData();
	//获取数据范围  type 0-节点值 1-单元值
	void getRange(QString va, double* range, int type =0);
	//获取变量名称  type 0-节点值 1-单元值
	QStringList getVariableName(int type = 0);
	//清空数据
	void clearData();

signals:
	void readFinished();

private slots:
	void on_readFinished();

private:
	PostData() = default;
	~PostData() = default;

private:
	static PostData* _instance;
	vtkDataSet* _data{};

	ReadThread* _readThread{};
};