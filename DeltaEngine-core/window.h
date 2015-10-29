#pragma once

#ifndef __DELTAENGINE_WINDOW__
#define __DELTAENGINE_WINDOW__

#include <GLFW\glfw3.h>
#include <string>

#ifdef DELTAENGINE_STATIC
#include <FreeGLUT\freeglut.h>
#endif

#include "DeltaEngine.h"

using namespace std;

namespace DeltaEngine {
	namespace Graphics {

		class Window {

		private:
			string title;
			GLFWwindow* window;

			int width, height;
			int errorIndex;

			bool vsync = false;
			bool mouseGrabbed = false;

			void(*errorHandler)(class Window*, int);

			void setError(int error);
			bool init();

			//const void* INSTANCE;

			inline void updateSize() { glfwGetFramebufferSize(this->window, &width, &height); }
			static inline void windowResize(GLFWwindow* window, int width, int height);
			
		public:
			DELTAENGINE_API Window(string title, int height, int width, void(*handler)(class Window*, int));
			DELTAENGINE_API Window(string title, int height, int width);
			DELTAENGINE_API ~Window();

			DELTAENGINE_API inline int getHeight() { updateSize(); return height; }
			DELTAENGINE_API inline int getWidth() { updateSize(); return width; }

			DELTAENGINE_API void update();
			DELTAENGINE_API bool closed() const;

			DELTAENGINE_API inline void setVSync(bool enable) { enable ? glfwSwapInterval(1) : glfwSwapInterval(0); vsync = enable; }
			DELTAENGINE_API inline bool IsVSync() const { return vsync; }

			DELTAENGINE_API int getError() const;
			DELTAENGINE_API string getErrorString(int error) const;
			DELTAENGINE_API void setWindowErrorHandler(void(*handler)(class Window*, int));

			DELTAENGINE_API void clear() const;
			DELTAENGINE_API void clearToColor(float r, float g, float b, float alpha) const;

			DELTAENGINE_API inline void grabMouse(bool grab);
			DELTAENGINE_API inline bool IsMouseGrabbed() { return mouseGrabbed; };
		};
	}
}

#endif