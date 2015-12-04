#pragma once

#ifndef __DELTAENGINE_WINDOW__
#define __DELTAENGINE_WINDOW__

#include <GLFW\glfw3.h>
#include <string>
#include <queue>

#include "DeltaEngine.h"
#include "vector2d.h"

using namespace std;

namespace DeltaEngine {
	namespace Graphics {

		class Window {

		private:
			string title;
			GLFWwindow* window;

			int width, height;
			int errorIndex;

			queue<unsigned int> textInput;

			bool vsync = false;
			bool mouseGrabbed = false;
			bool textMode = false;

			bool mouseButtons[GLFW_MOUSE_BUTTON_LAST];
			bool keys[GLFW_KEY_LAST];

			float mousePosX;
			float mousePosY;
			Maths::Vector2D scroll;
			
			void(*errorHandler)(class Window*, int);

			bool init(bool fullscreen);
			void setError(int error);

			inline void updateSize() { glfwGetFramebufferSize(this->window, &width, &height); }

			//Callbacks:
			static void windowResize(GLFWwindow* window, int width, int height);
			
			static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void textInputModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);

			static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
			static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
			
		public:
			DELTAENGINE_API Window(string& title, int height, int width, void(*handler)(class Window*, int), bool fullscreen = false);
			DELTAENGINE_API Window(string& title, int height, int width, bool fullscreen = false);
			DELTAENGINE_API ~Window();

			DELTAENGINE_API inline int getHeight() { /*updateSize();*/ return height; }
			DELTAENGINE_API inline int getWidth() { /*updateSize();*/ return width; }

			DELTAENGINE_API void update() const;
			DELTAENGINE_API inline bool closed() const;

			//vsync functions
			DELTAENGINE_API inline void setVSync(bool enable) { enable ? glfwSwapInterval(1) : glfwSwapInterval(0); vsync = enable; }
			DELTAENGINE_API inline bool IsVSync() const { return vsync; }

			//error-related functions
			DELTAENGINE_API int getError() const;
			DELTAENGINE_API string getErrorString(int error) const;
			DELTAENGINE_API inline void setWindowErrorHandler(void(*handler)(class Window*, int));

			DELTAENGINE_API void clear() const;
			DELTAENGINE_API void clearToColor(float r, float g, float b, float alpha) const;

			//Mouse functions
			DELTAENGINE_API inline void getMousePosition(float& x, float& y) const { x = mousePosX; y = mousePosY; };
			DELTAENGINE_API inline void getMouseScroll(double& x, double& y) const { x = scroll.x; y = scroll.y; };
			DELTAENGINE_API inline Maths::Vector2D getMousePosition() const { return Maths::Vector2D(mousePosX, mousePosY); }
			DELTAENGINE_API inline Maths::Vector2D getMouseScroll() const { return scroll; }
			DELTAENGINE_API inline void grabMouse(bool grab);
			DELTAENGINE_API inline bool isMouseGrabbed() { return mouseGrabbed; };
			DELTAENGINE_API inline bool isMouseButtonPressed(int button) const { return mouseButtons[button]; };
			DELTAENGINE_API inline void installMouse() const;
			
			//keyboard functions
			DELTAENGINE_API inline void installKeyboard() const;
			DELTAENGINE_API inline bool isKeyPressed(int key) const { return keys[key]; };
			DELTAENGINE_API inline void setTextMode(bool enable) { textMode = enable; }
			DELTAENGINE_API inline bool isTextInputAvailable() const { return (!textInput.empty()) && (textMode == true); };
			DELTAENGINE_API unsigned int getTextInput() { unsigned int i = textInput.front(); textInput.pop(); return i; };
		};

	}
}

#endif