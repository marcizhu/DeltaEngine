#include <string>
#include <GLEW\glew.h>
//#include <unordered_map>

#include "window.h"
#include "PlatformGraphics.h"

namespace DeltaEngine {
	namespace Graphics {

		std::unordered_map<void*, Window*> Window::handles;

		//Creates a window
		Window::Window(std::string& title, int width, int height, bool fullscreen)
			: title(title), height(height), width(width), closed(false), vsync(false), mouseGrabbed(false), vsyncTime(0.0f)
		{
			if (!Platform::PlatformCreateWindow(this, width, height, title.c_str()))
			{
				DELTAENGINE_FATAL("Failed to create base window!");
				return;
			}
			// TODO: Fullscreen windows!

			if (glewInit() != GLEW_OK)
			{
				DELTAENGINE_FATAL("Could not initialize GLEW!");
				return;
			}

			//glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			memset((void*)keys, 0, sizeof(keys));
			memset((void*)mouseButtons, 0, sizeof(mouseButtons));
		}

		void Window::update() const
		{
			Platform::PlatformWindowUpdate(const_cast<Window*>(this));
		}


		void Window::clearToColor(float r, float g, float b, float alpha) const
		{
			glClearColor(r, g, b, alpha);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		//window resize event handler
		void Window::resizeCallback(Window* window, int width, int height)
		{
			window->width = width;
			window->height = height;
			glViewport(0, 0, width, height);
		}

		// TODO: Implement this!
		void Window::grabMouse(bool grab)
		{
			this->mouseGrabbed = grab;
			//glfwSetInputMode(window, GLFW_CURSOR, grab ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		}

		void Window::focusCallback(Window* window, bool focused)
		{
			if (!focused)
			{
				//window->inputManager->ClearKeys();
				//window->inputManager->ClearMouseButtons();
			}
		}

		void Window::keyCallback(Window* window, int flags, int key, unsigned int message)
 		{
 			bool pressed = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;
			bool repeat = window->keys[key] & 1;

 			Types::byte modifier = 0;
 			switch (key)
 			{
 			case KB_KEY_CONTROL:
 				modifier = KB_MODIFIER_LEFT_CONTROL;
 				break;

 			case KB_KEY_ALT:
 				modifier = KB_MODIFIER_LEFT_ALT;
 				break;

 			case KB_KEY_SHIFT:
 				modifier = KB_MODIFIER_LEFT_SHIFT;
 				break;
 			}

			modifier &= 0xFC;

			window->keys[key] = (repeat << 1) | pressed;

			//TODO: Check this!
 			if (pressed)
				window->keys[key] |= modifier;
 			else
				window->keys[key] = 0;
		}


		void Window::registerWindowClass(void* handle, Window* window)
		{
			handles[handle] = window;
		}

		Window* Window::getWindowClass(void* handle)
		{
			if (handle == nullptr) return handles.begin()->second;

			return handles[handle];
		}

		void Window::setVSync(int mode, int fps)
		{
			switch (mode)
			{
			case VSYNC_ENABLE:
				Platform::PlatformSwapInterval(1);
				vsyncTime = 0.0f;
				break;

			case VSYNC_DISABLE:
				Platform::PlatformSwapInterval(0);
				vsyncTime = 0.0f;
				break;

			case VSYNC_NON_BLOCKING:
				Platform::PlatformSwapInterval(0);
				vsyncTime = (float)1.0 / fps;
				break;

			default:
				__debugbreak();
				break;
			}
		}
	}
}