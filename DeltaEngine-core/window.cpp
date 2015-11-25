#include <string>
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include "window.h"
#include "errors.h"

namespace DeltaEngine {
	namespace Graphics {

		//Creates a window without an error handler
		Window::Window(string& title, int width, int height)
		{
			this->errorIndex = 0;
			this->errorHandler = nullptr;

			this->title = title;
			this->height = height;
			this->width = width;

			if (!init())
			{
				glfwTerminate();
				return; //At this point we must have something in 'errorIndex'
			}
		}

		//Creates a window with an error handler
		Window::Window(string& title, int width, int height, void(*handler)(Window*, int))
		{
			this->errorIndex = 0;
			this->errorHandler = handler;

			this->title = title;
			this->height = height;
			this->width = width;

			if (!init()) return; //At this point we must have something in 'errorIndex'
		}

		//Destroys the window
		Window::~Window()
		{
			glfwDestroyWindow(this->window);
			glfwTerminate();
		}

		void Window::update() const
		{
			glfwPollEvents();
			glfwSwapBuffers(this->window);
		}

		//Sets an error
		void Window::setError(int error)
		{
			this->errorIndex = error;
			if (errorHandler != nullptr) errorHandler(this, error);
		}

		//returns the last error
		int Window::getError() const
		{
			return -this->errorIndex;
		}

		string Window::getErrorString(int error) const
		{
			unsigned int err = abs(error);
			switch (err)
			{
			case ERR_GLFW_INIT:
				return string("ERR_GLFW_INIT"); break;

			case ERR_GLEW_INIT:
				return string("ERR_GLEW_INIT"); break;

			case ERR_GLFW_CREATE_WINDOW:
				return string("ERR_GLFW_CREATE_WINDOW"); break;
			}

			return string("ERR_UNKNOWN_ERROR");
		}

		//Sets an error handler for window errors
		void Window::setWindowErrorHandler(void(*handler)(class Window*, int))
		{
			this->errorHandler = handler;
		}

		//initializes everything
		bool Window::init()
		{
			if (!glfwInit())
			{
				setError(ERR_GLFW_INIT);
				return false;
			}
			
			window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
			if (!window)
			{
				setError(ERR_GLFW_CREATE_WINDOW);
				return false;
			}

			glfwMakeContextCurrent(window);
			glfwSetFramebufferSizeCallback(window, windowResize);
			glfwSetWindowUserPointer(this->window, this);

			if (glewInit() != GLEW_OK)
			{
				setError(ERR_GLEW_INIT);
				return false;
			}

			return true;
		}

		//Returns if the window should close
		bool Window::closed() const
		{
			return (glfwWindowShouldClose(this->window) != 0);
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::clearToColor(float r, float g, float b, float alpha) const
		{
			clear();
			glClearColor(r, g, b, alpha);
		}

		//window resize event handler
		inline void Window::windowResize(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		//text mode input handler
		void Window::textInputModsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			if (!win->textMode) return;
			win->textInput.push(codepoint);
		}

		//keypress input handler
		void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if ((key > GLFW_KEY_LAST) || (key == GLFW_KEY_UNKNOWN)) return;

			Window* win = (Window*)glfwGetWindowUserPointer(window);
			if (win->textMode) return;
			win->keys[key] = (action != GLFW_RELEASE);
		}

		//mouse move handler
		void Window::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mousePos.x = xpos;
			win->mousePos.y = ypos;
		}

		//mouse button click handler
		void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mouseButtons[button] = (action != GLFW_RELEASE);
		}

		//mouse scroll handler
		void Window::mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->scroll.x += xoffset;
			win->scroll.y += yoffset;
		}

		void Window::grabMouse(bool grab)
		{
			this->mouseGrabbed = grab;
			grab ? glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED) : glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		void Window::installKeyboard() const
		{
			glfwSetKeyCallback(this->window, keyCallback);
			glfwSetCharModsCallback(this->window, textInputModsCallback);
		}

		void Window::installMouse() const
		{
			glfwSetCursorPosCallback(this->window, mouseMoveCallback);
			glfwSetMouseButtonCallback(this->window, mouseButtonCallback);
			glfwSetScrollCallback(this->window, mouseScrollCallback);
		}
	}
}