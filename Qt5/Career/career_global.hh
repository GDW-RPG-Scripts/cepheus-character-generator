#ifndef CAREER_GLOBAL_HH
#define CAREER_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(CAREER_LIBRARY)
#  define CAREER_EXPORT Q_DECL_EXPORT
#else
#  define CAREER_EXPORT Q_DECL_IMPORT
#endif

#endif // CAREER_GLOBAL_HH
