#pragma once

// DeltaEngine header files

// File-related files
#include "fileIO.h"

// Graphics-related files
#include "batchRenderable2d.h"
#include "batchRenderer2d.h"
#include "buffer.h"
#include "font.h"
#include "fontManager.h"
#include "indexBuffer.h"
#include "label.h"
#include "layer2d.h"
#include "renderable2d.h"
#include "renderer2d.h"
#include "shader.h"
//#include "sprite.h"
#include "texture.h"
#include "textureManager.h"
#include "vertexArray.h"
#include "window.h"

// Logging functions
#include "logger.h"

// Math-related files
#include "maths.h"
#include "matrix4.h"
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"

// Sound-related files
#include "sound.h"
#include "soundManager.h"

// Extra utilities
#ifdef _DEBUG
#	include "debug.h"
#endif
#include "stack.h"
#include "timer.h"
#include "types.h"
#include "utils.h"



namespace DeltaEngine {

	inline int init(int argc, char *argv[])
	{
		//TODO: Check for parameters!

		if (glewInit() != GLEW_OK) return DELTAENGINE_NOT_INITIALIZED;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);

		std::cout << "DeltaEngine Version " << DELTAENGINE_VERSION_S " " << DELTAENGINE_PHASE_S << std::endl << std::endl;

#ifdef DELTAENGINE_DEBUG
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0E);
		std::cout << "OpenGL:" << std::endl << std::endl;
		std::cout << "Version : " << glGetString(GL_VERSION) << std::endl;
		std::cout << "Vendor  : " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl << std::endl;
#endif
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);

		return DELTAENGINE_VERSION;
	}

}