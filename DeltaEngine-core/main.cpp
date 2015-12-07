//main.cpp: For testing purposes only
//

//#define DELTAENGINE_DEBUG

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

#include <GLEW\glew.h>

#include "window.h"
#include "utils.h"
#include "matrix4.h"
#include "vector2d.h"
#include "shader.h"
#include "debug.h"
#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"

#include "timer.h"
#include "renderable2d.h"
#include "simpleRenderer2d.h"

#include "camera.h"
#include "joystick.h"

using namespace DeltaEngine;
using namespace std;

void handler(Graphics::Window* window, int err)
{
	printf("Error %i: %s\n", err, window->getErrorString(err).c_str());
}

int main(int argc, char *argv[])
{
#ifndef _DEBUG
	FreeConsole();
#endif

	Graphics::Window win(string("DeltaEngine Sandbox"), 960, 540, &handler);

	if(init(argc, argv) == DELTAENGINE_NOT_INITIALIZED) return -1;

	win.installMouse();
	win.installKeyboard();

	Graphics::Camera camera(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Graphics::Shader shader(Utils::getCurrentPath() + "\\basic.vert", Utils::getCurrentPath() + "\\basic.frag");
	shader.enable();
	
	vector<Maths::Vector2D> positions;
	positions.push_back(Maths::Vector2D(0, 0));
	positions.push_back(Maths::Vector2D(5, 0));

	Graphics::Renderable2D sprite(positions, 0, Maths::Vector2D(1, 1), Types::Color(255, 0, 0, 255), shader);
	Graphics::Renderable2D sprite2(Maths::Vector2D(0.5, 8.0), 2, Maths::Vector2D(1, 1), Types::Color(0, 255, 0, 255), shader);
	Graphics::Renderable2D sprite3(Maths::Vector2D(1.0, 1.0), 2, Maths::Vector2D(1, 1), Types::Color(0, 0, 255, 255), shader);
	Graphics::SimpleRenderer2D renderer;

	win.setVSync(true);

	Types::ushort16 i = 0, last = 0;
	float x, y;

	Debug::dump(&camera, sizeof(camera));

	Timer::Timer myTimer;

	while (!win.closed())
	{
		win.clear();
		i++;

		win.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Maths::Vector2D((float)(x * 16.0f / win.getWidth()) + camera.getX(), (float)(y * 9.0f / win.getHeight()) + camera.getY()));
		
		shader.setUniformMat4("pr_matrix", camera.getMatrix4());

		renderer.submit(&sprite);
		renderer.submit(&sprite2);
		renderer.submit(&sprite3);
		renderer.sort(); //This function drops down the FPS counter from ~950 to ~750 on my computer, so you know...
		renderer.flush();

		if (win.isKeyPressed(65) && i == 1) Debug::dump(&camera, sizeof(camera));

		if (win.isKeyPressed(256)) break;

		if (win.isKeyPressed(262)) sprite2.move( 0.1f,  0.0f); // Right arrow
		if (win.isKeyPressed(263)) sprite2.move(-0.1f,  0.0f); // Left arrow
		if (win.isKeyPressed(264)) sprite2.move( 0.0f,  0.1f); // Down arrow
		if (win.isKeyPressed(265)) sprite2.move( 0.0f, -0.1f); // Up arrow
		
		if (myTimer.getElapsedTime() >= 1)
		{
			if(i != last) printf("FPS: %i\n", i);
			myTimer.restart();
			last = i;
			i = 0;
		}

		camera.track(sprite2, 7.5f, 4.0f);
		win.update();
		Debug::checkErrors();
	}

	return 0;
}