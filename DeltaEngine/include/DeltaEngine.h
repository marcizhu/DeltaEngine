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
#include "group.h"
#include "indexBuffer.h"
#include "label.h"
#include "layer2d.h"
#include "line.h"
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
#include "aabb.h"
#include "maths.h"
#include "matrix4.h"
#include "obb.h"
#include "vector2d.h"
#include "vector3d.h"
#include "vector4d.h"

// Sound-related files
#include "Playlist.h"
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
#include "log.h"
#include "memoryManager.h"

// Physics
#include "world2d.h"
#include "physicsRenderable2D.h"
#include "PhysicsRenderer2D.h"

namespace DeltaEngine {

	inline int init()
	{
		if (GLenum err = glewInit() != GLEW_OK)
		{
			DELTAENGINE_ERROR("", glewGetErrorString(err));

			return DELTAENGINE_NOT_INITIALIZED;
		}

		/*
		if(GLEW_VERSION_1_1) DELTAENGINE_INFO("Version 1.1 supported!");
		if(GLEW_VERSION_1_2) DELTAENGINE_INFO("Version 1.2 supported!");
		if(GLEW_VERSION_1_3) DELTAENGINE_INFO("Version 1.3 supported!");
		if(GLEW_VERSION_1_4) DELTAENGINE_INFO("Version 1.4 supported!");
		if(GLEW_VERSION_1_5) DELTAENGINE_INFO("Version 1.5 supported!");
		if(GLEW_VERSION_2_0) DELTAENGINE_INFO("Version 2.0 supported!");
		if(GLEW_VERSION_2_1) DELTAENGINE_INFO("Version 2.1 supported!");
		if(GLEW_VERSION_3_0) DELTAENGINE_INFO("Version 3.0 supported!");
		if(GLEW_VERSION_3_1) DELTAENGINE_INFO("Version 3.1 supported!");
		if(GLEW_VERSION_3_2) DELTAENGINE_INFO("Version 3.2 supported!");
		if(GLEW_VERSION_3_3) DELTAENGINE_INFO("Version 3.3 supported!");
		if(GLEW_VERSION_4_0) DELTAENGINE_INFO("Version 4.0 supported!");
		if(GLEW_VERSION_4_1) DELTAENGINE_INFO("Version 4.1 supported!");
		if(GLEW_VERSION_4_2) DELTAENGINE_INFO("Version 4.2 supported!");
		if(GLEW_VERSION_4_3) DELTAENGINE_INFO("Version 4.3 supported!");
		if(GLEW_VERSION_4_4) DELTAENGINE_INFO("Version 4.4 supported!");
		if(GLEW_VERSION_4_5) DELTAENGINE_INFO("Version 4.5 supported!");
		*/

		//if (!GLEW_VERSION_3_3) DELTAENGINE_ERROR("Version 3.3 is not supported! Shaders won't work! :(");

		Platform::PlatformSetConsoleColor(0x02);

		std::cout << "          [+]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[+] " << std::endl;
		std::cout << "           " << (char)179 << "  ____       _ _        _____             _             " << (char)179 << std::endl;
		std::cout << "           " << (char)179 << " |  _ \\  ___| | |_ __ _| ____|_ __   __ _(_)_ __   ___  " << (char)179 << std::endl;
		std::cout << "           " << (char)179 << " | | | |/ _ \\ | __/ _` |  _| | '_ \\ / _` | | '_ \\ / _ \\ " << (char)179 << std::endl;
		std::cout << "           " << (char)179 << " | |_| |  __/ | || (_| | |___| | | | (_| | | | | |  __/ " << (char)179 << std::endl;
		std::cout << "           " << (char)179 << " |____/ \\___|_|\\__\\__,_|_____|_| |_|\\__, |_|_| |_|\\___| " << (char)179 << std::endl;
		std::cout << "           " << (char)179 << "                     ___   _   ___  |___/               " << (char)179 << std::endl;
		std::cout << "           " << (char)179 << "           __   __  / _ \\ / | / _ \\  __ _               " << (char)179 << std::endl;
		std::cout << "           " << (char)179 << "           \\ \\ / / | | | || || | | |/ _` |              " << (char)179 << std::endl;
		std::cout << "           " << (char)179 << "            \\ V /  | |_| || || |_| | (_| |              " << (char)179 << std::endl;
		std::cout << "           " << (char)179 << "             \\_/    \\___(_)_(_)___/ \\__,_|              " << (char)179 << std::endl;
		std::cout << "           " << (char)179 << "                                                        " << (char)179 << std::endl;
		std::cout << "          [+]~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[+] " << std::endl << std::endl;

		DELTAENGINE_TRACE("OpenGL:\n\n");
		DELTAENGINE_TRACE("Version : ", glGetString(GL_VERSION));
		DELTAENGINE_TRACE("Vendor  : ", glGetString(GL_VENDOR));
		DELTAENGINE_TRACE("Renderer: ", glGetString(GL_RENDERER));
		DELTAENGINE_TRACE("Shaders : GLSL Shading Language v", glGetString(GL_SHADING_LANGUAGE_VERSION), "\n\n");

		_DELTAENGINE_TRACE("DeltaEngine ", DELTAENGINE_VERSION_S, " ", DELTAENGINE_PHASE_S, " (");
		Utils::printBuildTime();
		DELTAENGINE_TRACE(")\n");

		return DELTAENGINE_VERSION;
	}

	class Game
	{
	protected:
		Game() : fps(0), ups(0) { }

		Graphics::Window* window;
		Utils::Timer* timer;
		Types::uint32 fps, ups;
		float tickrate = 1.0f;

		// Runs once upon initialization
		virtual void init() = 0;
		// Runs once per second
		virtual void tick() {}
		// Runs 60 times per second
		virtual void update() {}
		// Runs as fast as possible (unless vsync is enabled)
		virtual void render() = 0;

		void run()
		{
			timer = NEW Utils::Timer();
			float seconds = 0.0f;
			float updateTimer = 0.0f;
			float renderTimer = 0.0f;
			const float updateTick = 1.0f / 60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;

			while (!window->isClosed())
			{
				window->clear();

				if (timer->getElapsedTime() - updateTimer >= updateTick)
				{
					//TODO: Window->updateInput(); (Events)
					//window->updateInput();
					update();
					updates++;
					updateTimer += updateTick;
				}

				if (timer->getElapsedTime() - renderTimer >= window->getVSyncTime())
				{
					render();
					frames++;
					window->update();

					renderTimer += window->getVSyncTime();
				}

				if (timer->getElapsedTime() - seconds >= tickrate)
				{
					seconds += (timer->getElapsedTime() - seconds);
					fps = frames;
					ups = updates;
					frames = 0;
					updates = 0;
					tick();
				}
			}
		}

		virtual ~Game()
		{
			delete timer;
			delete window;

			Memory::MemoryManager::end();
		}

		Graphics::Window* createWindow(std::string name, int width, int height)
		{
			this->window = NEW Graphics::Window(name, width, height);
			return window;
		}

		const unsigned int getFPS() const { return fps; }
		const unsigned int getUPS() const { return ups; }
		const float getTickRate() const { return tickrate; }

		void setTickRate(float seconds) { tickrate = seconds; }

	public:
		void start()
		{
			init();
			run();
		}
	};

}
