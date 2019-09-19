#ifndef CHARACTER_GLOBAL_HH
#define CHARACTER_GLOBAL_HH

#include <QtCore/qglobal.h>

#if defined(CHARACTER_LIBRARY)
#  define CHARACTER_EXPORT Q_DECL_EXPORT
#else
#  define CHARACTER_EXPORT Q_DECL_IMPORT
#endif

#endif // CHARACTER_GLOBAL_HH
