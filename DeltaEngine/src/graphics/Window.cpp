#include <string>
#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include "window.h"
#include "errors.h"

namespace DeltaEngine {
	namespace Graphics {

		//Creates a window without an error handler
		Window::Window(std::string& title, int width, int height, bool fullscreen)
		{
			this->errorIndex = 0;
			this->errorHandler = nullptr;

			this->title = title;
			this->height = height;
			this->width = width;

			if (!init(fullscreen)) return; //At this point we must have something in 'errorIndex'
		}

		//Creates a window with an error handler
		Window::Window(std::string& title, int width, int height, void(*handler)(Window*, int), bool fullscreen)
		{
			this->errorIndex = 0;
			this->errorHandler = handler;

			this->title = title;
			this->height = height;
			this->width = width;

			if (!init(fullscreen)) return; //At this point we must have something in 'errorIndex'
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

		std::string Window::getErrorString(int error) const
		{
			unsigned int err = abs(error);
			switch (err)
			{
			case ERR_GLFW_INIT:
				return std::string("ERR_GLFW_INIT"); break;

			case ERR_GLEW_INIT:
				return std::string("ERR_GLEW_INIT"); break;

			case ERR_GLFW_CREATE_WINDOW:
				return std::string("ERR_GLFW_CREATE_WINDOW"); break;
			}

			return std::string("ERR_UNKNOWN_ERROR");
		}

		//initializes everything
		bool Window::init(bool fullscreen)
		{
			if (!glfwInit())
			{
				setError(ERR_GLFW_INIT);
				return false;
			}
			
			if (fullscreen)
			{
				const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
				glfwWindowHint(GLFW_RED_BITS, mode->redBits);
				glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
				glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
				glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

				window = glfwCreateWindow(mode->width, mode->height, this->title.c_str(), glfwGetPrimaryMonitor(), NULL);
				this->height = mode->height;
				this->width = mode->width;
			} 
			else
			{
				window = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
			}

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

		void Window::clearToColor(float r, float g, float b, float alpha) const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(r, g, b, alpha);
		}

		//window resize event handler
		inline void Window::windowResize(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);

			Window* win = (Window*)glfwGetWindowUserPointer(window);
			glfwGetFramebufferSize(window, &win->width, &win->height);
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
			if (win->textMode)
			{
				//TODO: Add tab and return keys!
				if (key == 257) win->textInput.push('\n');
				if (key == 258) win->textInput.push('\t');
				return;
			}
			win->keys[key] = (action != GLFW_RELEASE);
		}

		//mouse move handler
		void Window::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mousePosX = (float)xpos;
			win->mousePosY = (float)ypos;
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
			win->scrollX += (float)xoffset;
			win->scrollY += (float)yoffset;
		}

		void Window::grabMouse(bool grab)
		{
			this->mouseGrabbed = grab;
			glfwSetInputMode(window, GLFW_CURSOR, grab ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		}

		void Window::installKeyboard() const
		{
			memset((void*)keys, 0, sizeof(keys));

			glfwSetKeyCallback(this->window, keyCallback);
			glfwSetCharModsCallback(this->window, textInputModsCallback);
		}

		void Window::installMouse() const
		{
			memset((void*)mouseButtons, 0, sizeof(mouseButtons));

			glfwSetCursorPosCallback(this->window, mouseMoveCallback);
			glfwSetMouseButtonCallback(this->window, mouseButtonCallback);
			glfwSetScrollCallback(this->window, mouseScrollCallback);
		}
	}
}