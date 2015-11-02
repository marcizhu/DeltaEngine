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

#define DELTAENGINE_BUILD_TIME	__TIMESTAMP__
#define DELTAENGINE_VERSION		"0.0.1"
#define DELTAENGINE_PHASE		"Pre-Alpha"