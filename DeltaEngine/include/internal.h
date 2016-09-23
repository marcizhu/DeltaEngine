#pragma once

#include <cstdint> // INTPTR_MAX, INT32_MAX & INT64_MAX

//Note: When using DELTAENGINE_STATIC, change application type to Static Library (*.lib)

#ifdef DELTAENGINE_STATIC
#	define DELTAENGINE_API
#else
#	ifdef DELTAENGINE_BUILD
#		define DELTAENGINE_API __declspec(dllexport)
#	else
#		define DELTAENGINE_API __declspec(dllimport)
#	endif
#endif

#if defined(_WIN32) || defined(_WIN64)
#	define DELTAENGINE_PLATFORM_WINDOWS
#elif defined(__linux__) || defined(__unix__) || defined(__GNUC__) || defined(__GNUG__)
#	define DELTAENGINE_PLATFORM_LINUX
#elif defined(__APPLE__)
#	define DELTAENGINE_PLATFORM_MAC
#else
#	define DELTAENGINE_PLATFORM_UNKNOWN
#endif

#if INTPTR_MAX == INT32_MAX
#	define DELTAENGINE_PLATFORM_X86
#elif INTPTR_MAX == INT64_MAX
#	define DELTAENGINE_PLATOFRM_X64
#else
#	define DELTAENGINE_PLATFORM_UNKNOWN
#endif

#if defined(_DEBUG) || defined(DEBUG)
#	define DELTAENGINE_DEBUG
#else
#	define DELTAENGINE_RELEASE
#endif

#ifdef DELTAENGINE_PLATFORM_UNKNOWN
#	error Unknown platform! Compilation aborted.
#endif

#define DELTAENGINE_NOT_INITIALIZED	0
#define DELTAENGINE_VERSION_0_0_1	1
#define DELTAENGINE_VERSION_0_1_0	10
#define DELTAENGINE_VERSION_0_2_0	20

#define DELTAENGINE_BUILD_TIME		Utils::printBuildTime()
#define DELTAENGINE_VERSION_MAJOR	0
#define DELTAENGINE_VERSION_MINOR	2
#define DELTAENGINE_VERSION_REV		0

// string versions
#define DELTAENGINE_VERSION_S		"0.2.0"
#define DELTAENGINE_PHASE_S			"Alpha"

#define DELTAENGINE_VERSION			DELTAENGINE_VERSION_0_2_0

// we will use this naming convention for versions
//#define DELTAENGINE_VERSION_1_0_0	100