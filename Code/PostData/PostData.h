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
	
	//��ȡ�ļ�
	void read(const QString& file);
	void setData(vtkDataSet* data);
	//��ȡ����
	vtkDataSet* getData();
	//��ȡ���ݷ�Χ  type 0-�ڵ�ֵ 1-��Ԫֵ
	void getRange(QString va, double* range, int type =0);
	//��ȡ��������  type 0-�ڵ�ֵ 1-��Ԫֵ
	QStringList getVariableName(int type = 0);
	//�������
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