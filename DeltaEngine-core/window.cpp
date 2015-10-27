//#include <GL\freeglut.h>
#include <string> //Not needed, already included in "window.h"
#include <GLFW/glfw3.h>

#include "window.h"
#include "errors.h"

namespace DeltaEngine {
	namespace Graphics {

		//Creates a window without an error handler
		Window::Window(string title, int width, int height)
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
		Window::Window(string title, int width, int height, void(*handler)(int))
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

		void Window::update()
		{
			glfwPollEvents();
			//glfwGetFramebufferSize(this->window, &width, &height);
			glfwSwapBuffers(this->window);
		}

		//Sets an error
		void Window::setError(int error)
		{
			this->errorIndex = error;
			if (errorHandler != nullptr) errorHandler(error);
		}

		//returns the last error
		int Window::getError() const
		{
			return -this->errorIndex;
		}

		//Sets an error handler for window errors
		void Window::setWindowErrorHandler(void(*handler)(int))
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
				glfwTerminate();
				setError(ERR_GLFW_CREATE_WINDOW);
				return false;
			}

			glfwMakeContextCurrent(window);
			//glfwSetWindowSizeCallback(window, windowResize);
			glfwSetFramebufferSizeCallback(window, windowResize);
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

		inline void windowResize(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void Window::grabMouse(bool grab)
		{
			this->mouseGrabbed = grab;
			grab ? glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED) : glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		};
	}
}