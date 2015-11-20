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

#define DELTAENGINE_BUILD_TIME		__TIMESTAMP__
#define DELTAENGINE_VERSION_MAJOR	0
#define DELTAENGINE_VERSION_MINOR	0
#define DELTAENGINE_VERSION_REV		1
#define DELTAENGINE_VERSION			"0.0.1"
#define DELTAENGINE_PHASE			"Pre-Alpha"

#ifdef DELTAENGINE_DEBUG

#include <Windows.h>
#include <iostream>

namespace DeltaEngine {

	inline int init(int argc, char *argv[])
	{
		//TODO: Check for parameters!

		if (glewInit() != GLEW_OK) return -1;

		std::cout << "DeltaEngine Version " << DELTAENGINE_VERSION " " << DELTAENGINE_PHASE << std::endl << std::endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		std::cout << "OpenGL:" << std::endl << std::endl;
		std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
		std::cout << "Vendor  : " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl << std::endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);

		return 0;
	}

}

#endif