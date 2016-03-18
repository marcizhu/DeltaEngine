#pragma once

#include <string>
#include <unordered_map>
#include <queue>

#include "internal.h"
#include "input.h"
#include "vector2d.h"

using namespace std;

namespace DeltaEngine {
	namespace Graphics {

		class Window {

		private:
			string title;

			int width, height;

			queue<unsigned int> textInput;

			bool vsync;
			bool mouseGrabbed;
			bool textMode;
			bool closed;

			unsigned char mouseButtons[MAX_BUTTONS];
			unsigned char keys[MAX_KEYS];

			float mousePosX;
			float mousePosY;
			float scrollX;
			float scrollY;

			static std::unordered_map<void*, Window*> handles;

			//Callbacks:
			/*static void windowResize(GLFWwindow* window, int width, int height);

			static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
			static void textInputModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);

			static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
			static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			static void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);*/

			//TODO: FIX THIS! -> Event handler
		public:
			static void focusCallback(Window* window, bool focused);
			static void resizeCallback(Window* window, int width, int height);
			static void keyCallback(Window* window, int flags, int key, unsigned int message);

		public:
			DELTAENGINE_API Window(string& title, int height, int width, bool fullscreen = false);
			DELTAENGINE_API ~Window() {};

			DELTAENGINE_API inline int getHeight() { return height; }
			DELTAENGINE_API inline int getWidth() { return width; }

			DELTAENGINE_API void update() const;
			DELTAENGINE_API inline bool isClosed() const { return closed; };
			DELTAENGINE_API inline void close() { this->closed = true; };

			//vsync functions
			DELTAENGINE_API inline void setVSync(bool enable);
			DELTAENGINE_API inline bool IsVSync() const { return vsync; }

			DELTAENGINE_API void clear() const { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); };
			DELTAENGINE_API void clearToColor(float r, float g, float b, float alpha) const;

			//Mouse functions
			DELTAENGINE_API inline void getMousePosition(float& x, float& y) const { x = mousePosX; y = mousePosY; };
			DELTAENGINE_API inline void getMouseScroll(double& x, double& y) const { x = scrollX; y = scrollY; };
			DELTAENGINE_API inline Maths::Vector2D getMousePosition() const { return Maths::Vector2D(mousePosX, mousePosY); }
			DELTAENGINE_API inline Maths::Vector2D getMouseScroll() const { return Maths::Vector2D(scrollX, scrollY); }
			DELTAENGINE_API inline void grabMouse(bool grab);
			DELTAENGINE_API inline bool isMouseGrabbed() { return mouseGrabbed; };
			DELTAENGINE_API inline bool isMouseButtonPressed(int button) const { return mouseButtons[button]; };

			//keyboard functions
			DELTAENGINE_API inline bool isKeyPressed(int key) const { return keys[key] & 1; };
			//TODO: INVESTIGATE THIS!
			DELTAENGINE_API inline bool isKeyHeld(int key) const { return (keys[key] >> 1) & 1; };
			DELTAENGINE_API inline void setTextMode(bool enable) { textMode = enable; }
			DELTAENGINE_API inline bool isTextInputAvailable() const { return (!textInput.empty()) && (textMode == true); };
			DELTAENGINE_API unsigned int getTextInput() { unsigned int i = textInput.front(); textInput.pop(); return i; };

			DELTAENGINE_API static void registerWindowClass(void* handle, Window* window);
			DELTAENGINE_API static Window* getWindowClass(void* handle);
		};

	}
}

// HACK: Q&D Solution
#include "PlatformWindow.h"