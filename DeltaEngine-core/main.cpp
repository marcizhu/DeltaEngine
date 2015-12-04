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
#include "Matrix4.h"
#include "vector2d.h"
#include "shader.h"
#include "debug.h"
#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"

#include "timer.h"
#include "renderable2d.h"
#include "renderer2d.h"

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

	Graphics::Window win(string("DeltaEngine Test Program!"), 960, 540, &handler);

	if(init(argc, argv) == DELTAENGINE_NOT_INITIALIZED) return -1;

	win.installMouse();
	win.installKeyboard();

	Maths::Matrix4 ortho = Maths::Matrix4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Graphics::Shader shader(Utils::getCurrentPath() + "\\basic.vert", Utils::getCurrentPath() + "\\basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	
	vector<Maths::Vector2D> positions;
	positions.push_back(Maths::Vector2D(0, 0));
	positions.push_back(Maths::Vector2D(5, 0));

	Graphics::Renderable2D sprite(positions, 0, Maths::Vector2D(1, 1), Types::Color(255, 0, 0, 255), shader);
	Graphics::Renderable2D sprite2(Maths::Vector2D(0.5, 0.5), 2, Maths::Vector2D(1, 1), Types::Color(0, 255, 0, 255), shader);
	Graphics::Renderable2D sprite3(Maths::Vector2D(1.0, 1.0), 1, Maths::Vector2D(1, 1), Types::Color(0, 0, 255, 255), shader);
	Graphics::Renderer2D renderer;

	win.setVSync(true);

	Timer::Timer myTimer;
	Types::ushort16 i = 0;
	float x, y;
	float px, py;
	px = py = 0;
	while (!win.closed())
	{
		win.clear();
		i++;

		win.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Maths::Vector2D((float)(x * 16.0f / win.getWidth()) + px, (float)(y * 9.0f / win.getHeight()) + py));
		
		ortho = Maths::Matrix4::orthographic(0.0f + px, 16.0f + px, 0.0f + py, 9.0f + py, -1.0f, 1.0f);
		shader.setUniformMat4("pr_matrix", ortho);
		
		renderer.submit(&sprite);
		renderer.submit(&sprite2);
		renderer.submit(&sprite3);
		renderer.sort();
		renderer.flush();

		Debug::Debug::checkErrors();
		if (myTimer.getElapsedTime() >= 1)
		{
			printf("FPS: %i\n", i);
			myTimer.restart();
			i = 0;
		}
		
		if (win.isKeyPressed(256)) break;

		if (win.isKeyPressed(262)) px += 0.1;
		if (win.isKeyPressed(263)) px -= 0.1;
		if (win.isKeyPressed(264)) py += 0.1;
		if (win.isKeyPressed(265)) py -= 0.1;

		win.update();
	}

	return 0;
}