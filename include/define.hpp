#ifndef EXPORT
#   if defined(_MSC_VER) // Microsoft
#       define EXPORT __declspec(dllexport)
#       define IMPORT __declspec(dllimport)
#   elif defined(__GNUC__) // GCC
#       define EXPORT __attribute__((visibility("default")))
#       define IMPORT
#   else
#       define EXPORT
#       define IMPORT
#       pragma warning Unknown dynamic link import/export semantics.
#   endif /* !_MSC_VER */
#endif /* !EXPORT */

#ifndef elementsof
#   define elementsof(x) (sizeof(x) / sizeof((x)[0]))
#endif /* !elementsof */

#ifndef FILE_EXISTS
#   define FILE_EXISTS ()
#endif /* !FILE_EXISTS */
