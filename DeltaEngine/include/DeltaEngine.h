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
#include "log.h"

// Platform files
#include "PlatformConsole.h"
#include "PlatformTime.h"
#include "PlatformLog.h"

namespace DeltaEngine {

	inline int init(int argc, char *argv[])
	{
		//TODO: Check for parameters!

		if (glewInit() != GLEW_OK) return DELTAENGINE_NOT_INITIALIZED;

		_DELTAENGINE_INFO("DeltaEngine Version ", DELTAENGINE_VERSION_S, " ", DELTAENGINE_PHASE_S, "\n\n");

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
			timer = new Utils::Timer();
			float _timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;

			while (!window->closed())
			{
				window->clear();
				if (timer->getElapsedTime() - updateTimer >= updateTick)
				{
					//TODO: Window->updateInput();
					//window->updateInput();
					update();
					updates++;
					updateTimer += updateTick;
				}
				render();
				frames++;
				window->update();
				if (timer->getElapsedTime() - _timer >= 1.0f)
				{
					_timer += 1.0f;
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
		}

		Graphics::Window* createWindow(std::string name, int width, int height)
		{
			this->window = new Graphics::Window(name, width, height);
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
