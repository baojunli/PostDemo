#include "PostData.h"
#include <QFileInfo>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkMultiBlockDataSet.h>
#include <QDebug>
#include <vtkDataSet.h>
#include <vtkUnstructuredGrid.h>
#include "ReadThread.h"


PostData* PostData::_instance = nullptr;

PostData* PostData::getInstance()
{
	if (_instance == nullptr)
		_instance = new PostData;
	return _instance;
}

void PostData::read(const QString& file)
{
	if (_data != nullptr)
	{
		_data->Delete();
		_data = nullptr;
	}
	if (_readThread != nullptr) return;
	_readThread = new ReadThread(file);
	connect(_readThread, SIGNAL(finished()), this, SLOT(on_readFinished()));
	_readThread->start();
}

void PostData::setData(vtkDataSet* data)
{
	_data = vtkUnstructuredGrid::New();
	_data->DeepCopy(data);
}

vtkDataSet* PostData::getData()
{
	return _data;
}


void PostData::getRange(QString va, double* range, int type)
{

}

QStringList PostData::getVariableName(int type)
{
	QStringList names{};
	auto d = vtkDataSet::SafeDownCast(_data);
	if (d == nullptr) return names;
	if(type == 0)
	{
		vtkPointData* pd = d->GetPointData();
		const int na = pd->GetNumberOfArrays();
		for (int i =0;i<na; ++i)
		{
			const char* name = pd->GetArrayName(i);
			names.append(name);
		}
	}
	else if (type == 1)
	{
		vtkCellData* pd = d->GetCellData();
		const int na = pd->GetNumberOfArrays();
		for (int i = 0; i < na; ++i)
		{
			const char* name = pd->GetArrayName(i);
			names.append(name);
		}
	}

	return names;

}

void PostData::clearData()
{
	if (_data != nullptr)
	{
		_data->Delete();
		_data = nullptr;
	}
}

void PostData::on_readFinished()
{
	delete _readThread;
	_readThread = nullptr;

	emit this->readFinished();
}

