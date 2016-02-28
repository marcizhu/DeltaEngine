#include <string>
#include <GLEW\glew.h>
//#include <unordered_map>

#include "window.h"
//#include "PlatformWindow.h"

namespace DeltaEngine {
	namespace Graphics {

		std::unordered_map<void*, Window*> Window::handles;
		
		//Creates a window
		Window::Window(std::string& title, int width, int height, bool fullscreen)
			: title(title), height(height), width(width)
		{
			if (!Internal::PlatformCreateWindow(this, width, height, title.c_str()))
			{
				DELTAENGINE_FATAL("Failed to create base window!");
				return;
			}
			// TODO: Fullscreen!

			if (glewInit() != GLEW_OK)
			{
				DELTAENGINE_FATAL("Could not initialize GLEW!");
				return;
			}

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		//Destroys the window
		//Window::~Window() { }

		void Window::update() const
		{
			Internal::PlatformWindowUpdate(const_cast<Window*>(this));
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

		void Window::grabMouse(bool grab)
		{
			this->mouseGrabbed = grab;
			//glfwSetInputMode(window, GLFW_CURSOR, grab ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		}

		void Window::installKeyboard() const
		{
			memset((void*)keys, 0, sizeof(keys));
		}

		void Window::installMouse() const
		{
			memset((void*)mouseButtons, 0, sizeof(mouseButtons));
		}
		
		void Window::focusCallback(Window* window, bool focused)
		{
			if (!focused)
			{
				//window->inputManager->ClearKeys();
				//window->inputManager->ClearMouseButtons();
			}
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
	}
}