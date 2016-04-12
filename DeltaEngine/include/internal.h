#pragma once

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

#if defined(_WIN32)
#	define DELTAENGINE_PLATFORM_WINDOWS
#elif defined(__unix__) || defined(__GNUC__) || defined(__GNUG__)
#	define DELTAENGINE_PLATFORM_LINUX
#elif defined(__APPLE__)
#	define DELTAENGINE_PLATFORM_MAC
#else
#	define DELTAENGINE_PLATFORM_UNKNOWN
#endif

#define DELTAENGINE_NOT_INITIALIZED	0
#define DELTAENGINE_VERSION_0_0_1	1
#define DELTAENGINE_VERSION_0_1_0	10

#define DELTAENGINE_BUILD_TIME		__TIMESTAMP__
#define DELTAENGINE_VERSION_MAJOR	0
#define DELTAENGINE_VERSION_MINOR	1
#define DELTAENGINE_VERSION_REV		0

// string versions
#define DELTAENGINE_VERSION_S		"0.1.0"
#define DELTAENGINE_PHASE_S			"Alpha"

#define DELTAENGINE_VERSION			DELTAENGINE_VERSION_0_1_0


// we will use this naming convention for versions
//#define DELTAENGINE_VERSION_1_0_0	100

#ifdef _DEBUG
#define DELTAENGINE_DEBUG
#endif