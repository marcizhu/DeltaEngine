//main.cpp: For testing purposes only
//

#define DELTAENGINE_DEBUG

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <FreeGLUT\freeglut.h> //Remove extra configurations! (additional lib dirs, additional dependencies)

#include <iostream>

#include "window.h"
#include "vector4d.h"

using namespace DeltaEngine;
using namespace std;

void handler(Graphics::Window* window, int err)
{
	printf("Error %i: %s\n", err, window->getErrorString(err).c_str());
}

int main(int argc, char *argv[])
{
	printf("DeltaEngine Version %s %s\n", DELTAENGINE_VERSION, DELTAENGINE_PHASE);
	
	Graphics::Window win(string("DeltaEngine Test Program!"), 960, 540, &handler);

	win.clearToColor(0.0f, 0.2f, 0.7f, 1.0f);

	Maths::Vector4D vector(1, 3, 1, 1);
	Maths::Vector4D other(2, 2, 2, 2);
	vector /= other;

	cout << vector << endl;

	printf("OK!\n");
	win.setVSync(true);
	while (!win.closed())
	{
		win.clear();
		glColor3f(0.7f, 0.7f, 1.0f);
		glRectf(-0.75f, 0.75f, 0.75f, -0.75f);
		win.update();
	}
	return 0;
}