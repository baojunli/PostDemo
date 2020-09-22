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
	
	//��ȡ�ļ�
	bool read(const QString& file);
	void setData(vtkMultiBlockDataSet* mulitData);
	//��ȡ����
	vtkDataSet* getData();
	//��ȡ���ݷ�Χ  type 0-�ڵ�ֵ 1-��Ԫֵ
	void getRange(QString va, double* range, int type =0);
	//��ȡ��������  type 0-�ڵ�ֵ 1-��Ԫֵ
	QStringList getVariableName(int type = 0);

private:
	PostData() = default;
	~PostData() = default;

	void getDataObject(vtkMultiBlockDataSet* md, QList<vtkDataObject*>& dataList);
	
private:
	static PostData* _instance;
	vtkDataSet* _data{};
};