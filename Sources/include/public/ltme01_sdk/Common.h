#ifndef COMMON_H
#define COMMON_H

#ifdef _WIN32
#ifdef LTME01_SDK_EXPORTS
#define LTME01_SDK_API __declspec(dllexport)
#elif defined(LTME01_SDK_STATIC)
#define LTME01_SDK_API
#else
#define LTME01_SDK_API __declspec(dllimport)
#endif
#else
#define LTME01_SDK_API
#endif

#endif
