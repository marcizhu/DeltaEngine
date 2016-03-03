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

		void Window::keyCallback(Window* window, int flags, int key, unsigned int message)
 		{
 			bool pressed = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;
 			bool repeat = (flags >> 30) & 1;

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

			window->keys[key] = modifier | (repeat << 1) | pressed;
 			/*if (pressed)
 				inputManager->m_KeyModifiers |= modifier;
 			else
 				inputManager->m_KeyModifiers &= ~(modifier);*/

 			/*if (pressed)
 				inputManager->m_EventCallback(KeyPressedEvent(key, repeat, inputManager->m_KeyModifiers));
 			else
 				inputManager->m_EventCallback(KeyReleasedEvent(key));*/
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