//main.cpp: For testing purposes only
//

#include <Windows.h>
#include "window.h"

#include"logger.h"

#include <stdio.h>
#include <string>

using namespace DeltaEngine;
using namespace std;

void handler(int err)
{
	printf("Error: %i\n", err);
}

int main(int argc, char *argv[])
{
	Graphics::Window win(string("DeltaEngine Test Program!"), 960, 540, &handler);
	
	win.clearToColor(0.0f, 0.2f, 0.7f, 1.0f);

	/*win.update();
	Sleep(1000);
	win.grabMouse(true);
	Sleep(5000);
	win.grabMouse(false);*/

	printf("OK!");
	while (!win.closed())
	{
		win.clear();
		win.update();
	}

	return 0;
}