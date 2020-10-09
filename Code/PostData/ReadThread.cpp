#include "ReadThread.h"
#include "PostData.h"
#include <QFileInfo>
#include <vtkPointData.h>
#include <vtkCellData.h>
#include <vtkFieldData.h>
#include <vtkDataArray.h>
#include <vtkAppendFilter.h>
#include <vtkExodusIIReader.h>
#include <vtkTecplotReader.h>
#include <QString>
#include <vtkSmartPointer.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkDataSet.h>
#include <vtkDataObject.h>
#include <vtkUnstructuredGrid.h>
#include <QDebug>

ReadThread::ReadThread(const QString & file)
{
	_fileName = file;
}

ReadThread::~ReadThread()
{

}

void ReadThread::run()
{
	QFileInfo f(_fileName);
	if (!f.exists()) return;
	const QString suffix = f.suffix();
	QByteArray array = _fileName.toLatin1();
	char* fileName = array.data();
	const QString ss = suffix.simplified().toLower();
	if (ss == "e")
	{
		vtkSmartPointer<vtkExodusIIReader> reader = vtkSmartPointer<vtkExodusIIReader>::New();
		if (!reader->CanReadFile(fileName)) return;
		reader->SetFileName(fileName);
		reader->Update();
		vtkMultiBlockDataSet* data = reader->GetOutput();
		this->mergeData(data);
		return ;
	}
	else if (ss == "hot" || ss == "pre")
	{
		vtkSmartPointer<vtkTecplotReader> reader = vtkSmartPointer<vtkTecplotReader>::New();
		reader->SetFileName(fileName);
		reader->Update();
		vtkMultiBlockDataSet* data = reader->GetOutput();
		this->mergeData(data);
		return;
	}
}

void ReadThread::mergeData(vtkMultiBlockDataSet* mulitData)
{
	QList<vtkDataObject*> objs;
	getDataObject(mulitData, objs);
	vtkSmartPointer<vtkAppendFilter> app = vtkSmartPointer<vtkAppendFilter>::New();
	for (auto obj : objs)
	{
		app->AddInputData(obj);
	}

	app->Update();
	vtkUnstructuredGrid* gird = app->GetOutput();
	if(gird !=nullptr)
		PostData::getInstance()->setData(gird);
}

void ReadThread::getDataObject(vtkMultiBlockDataSet* md, QList<vtkDataObject*>& dataList)
{
	if (md == nullptr) return;
	const int n = md->GetNumberOfBlocks();
	for (int i = 0; i < n; ++i)
	{
		vtkDataObject*obj = md->GetBlock(i);
		if (obj == nullptr) continue;
		if (obj->IsA("vtkMultiBlockDataSet"))
		{
			vtkMultiBlockDataSet* mublock = vtkMultiBlockDataSet::SafeDownCast(obj);
			if (mublock != nullptr)
				getDataObject(mublock, dataList);
		}
		else
		{
			obj->Print(std::cout);
			dataList.append(obj);
			vtkDataSet* dataset = vtkDataSet::SafeDownCast(obj);
			if (dataset == nullptr) continue;
			qDebug() << dataset->GetNumberOfPoints();
			qDebug() << dataset->GetNumberOfCells();
			vtkPointData* pointdata = dataset->GetPointData();
			if (pointdata != nullptr)
			{
				const int n = pointdata->GetNumberOfArrays();
				for (int i = 0; i < n; ++i)
				{
					const char* name = pointdata->GetArrayName(i);
					qDebug() << QString("P %1 :  ").arg(i) << QString(name);
				}
			}
			vtkCellData* celldata = dataset->GetCellData();
			if (celldata != nullptr)
			{
				const int n = celldata->GetNumberOfArrays();
				for (int i = 0; i < n; ++i)
				{
					const char* name = celldata->GetArrayName(i);
					qDebug() << QString("C %1 :  ").arg(i) << QString(name);
				}
			}
			vtkFieldData* filddata = dataset->GetFieldData();
			if (filddata != nullptr)
			{
				const int n = filddata->GetNumberOfArrays();
				for (int i = 0; i < n; ++i)
				{
					const char* name = filddata->GetArrayName(i);
					qDebug() << QString("F %1 :  ").arg(i) << QString(name);
				}
			}
		}
	}
}

