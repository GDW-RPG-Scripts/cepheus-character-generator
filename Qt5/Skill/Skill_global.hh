#ifndef SKILL_GLOBAL_HH
#define SKILL_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(SKILL_LIBRARY)
#  define SKILL_EXPORT Q_DECL_EXPORT
#else
#  define SKILL_EXPORT Q_DECL_IMPORT
#endif

#endif // SKILL_GLOBAL_HH
