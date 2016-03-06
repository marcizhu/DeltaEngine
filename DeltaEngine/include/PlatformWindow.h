#include <GLEW\glew.h>

#include "log.h"

namespace DeltaEngine {
	namespace Internal {

#if defined(_WIN32) && defined(DELTAENGINE_BUILD)
#	ifdef _WINDOWS_
#		undef _WINDOWS_
#	endif
#include <Windows.h>
#include <Windowsx.h>
#include <GLEW\wglew.h>

		EXTERN_C IMAGE_DOS_HEADER __ImageBase;

		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		//extern void MouseButtonCallback(InputManager* inputManager, int button, int x, int y);

		static HINSTANCE hInstance;
		static HDC hDc;
		HWND hWnd;

		static PIXELFORMATDESCRIPTOR get_pixel_format()
		{
			PIXELFORMATDESCRIPTOR result = { };
			result.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			result.nVersion = 1;
			result.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			result.iPixelType = PFD_TYPE_RGBA;
			result.cColorBits = 32;
			result.cDepthBits = 24;
			result.cStencilBits = 8;
			result.cAuxBuffers = 0;
			result.iLayerType = PFD_MAIN_PLANE;

			return result;
		}

		static __forceinline bool PlatformCreateWindow(Graphics::Window* win, int width, int height, const char* title)
		{
			hInstance = (HINSTANCE)&__ImageBase;

			WNDCLASS winClass = {};
			winClass.hInstance = hInstance; // GetModuleHandle(0);
			winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			winClass.lpfnWndProc = (WNDPROC)WndProc;
			winClass.lpszClassName = "DeltaEngine Win32 Window";
			winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

			if (!RegisterClassA(&winClass))
			{
				DELTAENGINE_ERROR("Could not register Win32 class!");
				return false;
			}

			RECT size = { 0, 0, width, height };
			AdjustWindowRectEx(&size, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, false, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

			hWnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
				winClass.lpszClassName, title,
				WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
				GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2,
				GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2,
				size.right - size.left, size.bottom - size.top, NULL, NULL, hInstance, NULL);

			if (!hWnd)
			{
				DELTAENGINE_ERROR("Could not create window!");
				return false;
			}

			win->registerWindowClass(hWnd, win);

			hDc = GetDC(hWnd);
			PIXELFORMATDESCRIPTOR pfd = get_pixel_format();
			int pixelFormat = ChoosePixelFormat(hDc, &pfd);

			if (pixelFormat)
			{
				if (!SetPixelFormat(hDc, pixelFormat, &pfd))
				{
					DELTAENGINE_ERROR("Failed setting pixel format!");
					return false;
				}
			}
			else
			{
				DELTAENGINE_ERROR("Failed choosing pixel format!");
				return false;
			}

			HGLRC hrc = wglCreateContext(hDc);

			if (hrc)
			{
				if (!wglMakeCurrent(hDc, hrc))
				{
					DELTAENGINE_ERROR("Failed setting OpenGL context!");
					return false;
				}
			}
			else
			{
				DELTAENGINE_ERROR("Failed creating OpenGL context!");
				return false;
			}

			ShowWindow(hWnd, SW_SHOW);
			SetFocus(hWnd);

			return true;
		}

		static __forceinline void PlatformWindowUpdate(Graphics::Window* win)
		{
			MSG message;
			while (PeekMessage(&message, hWnd, NULL, NULL, PM_REMOVE) > 0)
			{
				if (message.message == WM_QUIT)
				{
					win->close();
					return;
				}

				TranslateMessage(&message);
				DispatchMessage(&message);
			}

			//InputManager->PlatformUpdate();
			SwapBuffers(hDc);
		}

		// Win32 Window event handler
		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			LRESULT result = NULL;

			Graphics::Window* window = Graphics::Window::getWindowClass(hWnd);
			if (window == nullptr) return DefWindowProc(hWnd, message, wParam, lParam);

			//InputManager* inputManager = window->GetInputManager();

			switch (message)
			{
			case WM_ACTIVATE:
				if (!HIWORD(wParam)) // Is minimized
				{
					/* active */
				} else {
					/* inactive */
				}

				return 0;
				break;

			case WM_SYSCOMMAND:
				switch (wParam)
				{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;

				// TODO: Add 'SC_MINIMIZE', 'SC_MAXIMIZE' and 'SC_RESTORE'
				}
				result = DefWindowProc(hWnd, message, wParam, lParam);
				break;

			case WM_SETFOCUS:
				window->focusCallback(window, true); break;

			case WM_KILLFOCUS:
				window->focusCallback(window, false); break;

			case WM_CLOSE:
			case WM_DESTROY:
				PostQuitMessage(0); break;

			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
				window->keyCallback(window, lParam, wParam, message); break;

			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
				//MouseButtonCallback(inputManager, message, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				break;

			case WM_SIZE:
				window->resizeCallback(window, LOWORD(lParam), HIWORD(lParam)); break;

			default:
				result = DefWindowProc(hWnd, message, wParam, lParam); break;
			}

			return result;
		}
#else
#	ifdef DELTAENGINE_BUILD
#		error This platform is not supported!
#	endif
#endif

	}
}