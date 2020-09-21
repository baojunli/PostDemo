#ifndef _POSTWIGETAPI_H_
#define _POSTWIGETAPI_H_
#include <QtCore/QtGlobal>


#if defined(PostWidget_API)
#define PostWidgetAPI Q_DECL_EXPORT
#else
#define PostWidgetAPI Q_DECL_IMPORT
#endif

#endif
