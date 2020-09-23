#include "PostData.h"
#include <QFileInfo>
#include <vtkExodusIIReader.h>
#include <vtkTecplotReader.h>
#include <QString>
#include <vtkSmartPointer.h>
#include <vtkMultiBlockDataSet.h>
#include <QDebug>
#include <vtkDataSet.h>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkDataArray.h>
// #include <vtkCompositeDataPipeline.h>
// #include <vtkCompositeDataGeometryFilter.h>
#include <vtkAppendFilter.h>
#include <vtkUnstructuredGrid.h>
#include "PostData/PostData.h"



PostData* PostData::_instance = nullptr;

PostData* PostData::getInstance()
{
	if (_instance == nullptr)
		_instance = new PostData;
	return _instance;
}

bool PostData::read(const QString& file)
{
	QFileInfo f(file);
	if (!f.exists()) return false;
	const QString suffix = f.suffix();
	QByteArray array = file.toLatin1();
	char* fileName = array.data();
	const QString ss = suffix.simplified().toLower();
	if ( ss == "e")
	{
		vtkSmartPointer<vtkExodusIIReader> reader = vtkSmartPointer<vtkExodusIIReader>::New();
		if(!reader->CanReadFile(fileName)) return false;
		reader->SetFileName(fileName);
		reader->Update();
		vtkMultiBlockDataSet* data = reader->GetOutput();
		this->setData(data);
		return true;
	}
	else if(ss == "hot" || ss == "pre")
	{
		vtkSmartPointer<vtkTecplotReader> reader = vtkSmartPointer<vtkTecplotReader>::New();
		reader->SetFileName(fileName);
		reader->Update();
		vtkMultiBlockDataSet* data = reader->GetOutput();
		this->setData(data);
		return true;
	}

	return false;
}

void PostData::setData(vtkMultiBlockDataSet* mulitData)
{
	if (_data != nullptr) _data->Delete();
// 	const int nblock = mulitData->GetNumberOfBlocks();
 	vtkSmartPointer<vtkAppendFilter> app = vtkSmartPointer<vtkAppendFilter>::New();
// 	for (int i =0;i<nblock; ++i)
// 	{
// 		vtkDataObject* obj = mulitData->GetBlock(i);
// 		if (obj->IsA("vtkMultiBlockDataSet"))
// 		{
// 			vtkMultiBlockDataSet* sobj = vtkMultiBlockDataSet::SafeDownCast(obj);
// 			if(sobj == nullptr) continue;
// 			const int snbolck = sobj->GetNumberOfBlocks();
// 			for (int si = 0; si < snbolck; ++si)
// 			{
// 				vtkDataObject* ssb = sobj->GetBlock(si);
// 				if(ssb == nullptr) continue;
// 				if (!ssb->IsA("vtkMultiBlockDataSet"))
// 				{
// 					app->AddInputData(ssb);
// 					vtkDataSet* dset = vtkDataSet::SafeDownCast(ssb);
// 					if (dset == nullptr) continue;;
// 					qDebug() << dset->GetPointData()->GetNumberOfArrays();
// 					qDebug() << dset->GetCellData()->GetNumberOfArrays();
// 				}
// 					
// 			}
// 		}
// 		else
// 			app->AddInputData(obj);
// 	}
	QList<vtkDataObject*> objs;
	getDataObject(mulitData, objs);
	for (auto obj : objs)
	{
		app->AddInputData(obj);
	}

	app->Update();
	vtkUnstructuredGrid* gird = app->GetOutput();
	_data = vtkUnstructuredGrid::New();
	_data->DeepCopy(gird);
// 	qDebug() << _data->GetNumberOfPoints();
// 	qDebug() << _data->GetNumberOfCells();
// 	qDebug() << _data->GetPointData()->GetNumberOfArrays();
// 	qDebug() << _data->GetCellData()->GetArrayName(0);
}

vtkDataSet* PostData::getData()
{
	return _data;
}

void PostData::getDataObject(vtkMultiBlockDataSet* md, QList<vtkDataObject*>& dataList)
{
	if (md == nullptr) return;
	const int n = md->GetNumberOfBlocks();
	for (int i=0;i<n; ++i)
	{
		vtkDataObject*obj = md->GetBlock(i);
		if(obj == nullptr) continue;
		if (obj->IsA("vtkMultiBlockDataSet"))
		{
			vtkMultiBlockDataSet* mublock = vtkMultiBlockDataSet::SafeDownCast(obj);
			if (mublock != nullptr)
				getDataObject(mublock, dataList);
		}
		else
		{
			dataList.append(obj);
		}
	}
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

