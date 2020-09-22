#pragma  once

#include "PostDataAPI.h"
#include <QStringList>

class vtkMultiBlockDataSet;
class vtkDataSet;
class vtkDataObject;

class PostDataAPI PostData
{
public :
	static PostData* getInstance();
	
	//读取文件
	bool read(const QString& file);
	void setData(vtkMultiBlockDataSet* mulitData);
	//获取数据
	vtkDataSet* getData();
	//获取数据范围  type 0-节点值 1-单元值
	void getRange(QString va, double* range, int type =0);
	//获取变量名称  type 0-节点值 1-单元值
	QStringList getVariableName(int type = 0);

private:
	PostData() = default;
	~PostData() = default;

	void getDataObject(vtkMultiBlockDataSet* md, QList<vtkDataObject*>& dataList);
	
private:
	static PostData* _instance;
	vtkDataSet* _data{};
};