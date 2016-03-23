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
#include "log.h"
#include "memoryManager.h"

// Platform files
//#include "PlatformUtils.h"

namespace DeltaEngine {

	inline int init()
	{
		if (glewInit() != GLEW_OK) return DELTAENGINE_NOT_INITIALIZED;

		Internal::PlatformSetConsoleColor(0x02);

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

		_DELTAENGINE_WARN("OpenGL:", "\n\n");
		_DELTAENGINE_WARN("Version : ", glGetString(GL_VERSION), '\n');
		_DELTAENGINE_WARN("Vendor  : ", glGetString(GL_VENDOR), '\n');
		_DELTAENGINE_WARN("Renderer: ", glGetString(GL_RENDERER), "\n\n");

		return DELTAENGINE_VERSION;
	}

	class Game
	{
	protected:
		Game() : fps(0), ups(0) { }

		Graphics::Window* window;
		Utils::Timer* timer;
		Types::uint32 fps, ups;

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
			float _timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
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
				else
				{
					DELTAENGINE_INFO("Free time!");
				}

				render();
				frames++;
				window->update();

				if (timer->getElapsedTime() - _timer >= 1.0f)
				{
					_timer += (timer->getElapsedTime() - _timer);
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

			//Memory::MemoryManager::end();
		}

		Graphics::Window* createWindow(std::string name, int width, int height)
		{
			this->window = NEW Graphics::Window(name, width, height);
			return window;
		}

		const unsigned int getFPS() const { return fps; }
		const unsigned int getUPS() const { return ups; }

	public:
		void start()
		{
			init();
			run();
		}
	};

}
