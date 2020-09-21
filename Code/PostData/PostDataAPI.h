#ifndef _POSTDATAAPI_H_
#define _POSTDATAAPI_H_
#include <QtCore/QtGlobal>


#if defined(PostData_API)
#define PostDataAPI Q_DECL_EXPORT
#else
#define PostDataAPI Q_DECL_IMPORT
#endif

#endif
