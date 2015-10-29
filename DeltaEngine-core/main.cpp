//main.cpp: For testing purposes only
//

#include <Windows.h>
#include <stdio.h>
#include <string>

#include "window.h"
#include <FreeGLUT\freeglut.h> //Remove extra configurations! (additional lib dirs, additional dependencies)

using namespace DeltaEngine;
using namespace std;

void handler(Graphics::Window* window, int err)
{
	//You can also use: window->getErrorString(window->getError).c_str();
	printf("Error %i: %s\n", err, window->getErrorString(err).c_str()); 
}

int main(int argc, char *argv[])
{
	Graphics::Window win(string("DeltaEngine Test Program!"), 960, 540, &handler);
	
	win.clearToColor(0.0f, 0.2f, 0.7f, 1.0f);

	printf("OK!");
	while (!win.closed())
	{
		win.clear();
		glColor3f(1.0f, 1.0f, 1.0f);
		glRectf(-0.75f, 0.75f, 0.75f, -0.75f);
		win.update();
	}

	return 0;
}