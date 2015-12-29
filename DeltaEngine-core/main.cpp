//main.cpp: For testing purposes only
//
#define BATCH_RENDERER

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
#include "timer.h"

#ifdef BATCH_RENDERER
	#include "batchRenderable2d.h"
	#include "batchRenderer2d.h"
#else
	#include "simpleRenderable2d.h"
	#include "simpleRenderer2d.h"
#endif

#include "layer2d.h"

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

	Maths::Matrix4 pr_matrix = Maths::Matrix4::orthographic(0.0f, 16.0f, 9.0f, 0.0f, -1.0f, 1.0f);

	Graphics::Shader* shader = new Graphics::Shader(Utils::getCurrentPath() + "\\basic.vert", Utils::getCurrentPath() + "\\basic.frag");
	shader->enable();

#ifdef BATCH_RENDERER
	Graphics::Layer2D mainLayer(new Graphics::BatchRenderer2D(), shader, pr_matrix);
	mainLayer.add(new Graphics::BatchRenderable2D(0.0f, 0.0f, 1, 1, Types::Color(255, 0, 0, 255)));
	mainLayer.add(new Graphics::BatchRenderable2D(2.0f, 0.0f, 1, 1, Types::Color(0, 255, 0, 255)));
	mainLayer.add(new Graphics::BatchRenderable2D(1.0f, 1.0f, 1, 1, Types::Color(0, 0, 255, 255)));
#else
	Graphics::Layer2D mainLayer(new Graphics::SimpleRenderer2D(), shader, pr_matrix);
	mainLayer.add(new Graphics::SimpleRenderable2D(0.0f, 0.0f, 1, 1, Types::Color(255, 0, 0, 255), *shader));
	mainLayer.add(new Graphics::SimpleRenderable2D(2.0f, 0.0f, 1, 1, Types::Color(0, 255, 0, 255), *shader));
	mainLayer.add(new Graphics::SimpleRenderable2D(1.0f, 1.0f, 1, 1, Types::Color(0, 0, 255, 255), *shader));
#endif

	win.setVSync(true);

	Types::ushort16 i = 0, last = 0;
	float c = 0;
	float x, y;

	Timer::Timer myTimer;

	while (!win.closed())
	{
		win.clear();
		i++;
		c++;

		win.getMousePosition(x, y);
		shader->setUniform2f("light_pos", (float)(x * 16.0f / win.getWidth()) - mainLayer.getCameraPositionX(), (float)(9.0 - y * 9.0f / win.getHeight()) - mainLayer.getCameraPositionY());

		float t = c / 60;

		mainLayer.setCameraPosition(-t, 0);
		mainLayer.render();

		if (win.isKeyPressed(256)) break;

		if (win.isKeyPressed(262)) mainLayer[0]->move( 0.1f,  0.0f); // Right arrow
		if (win.isKeyPressed(263)) mainLayer[0]->move(-0.1f,  0.0f); // Left arrow
		if (win.isKeyPressed(264)) mainLayer[0]->move( 0.0f, -0.1f); // Down arrow
		if (win.isKeyPressed(265)) mainLayer[0]->move( 0.0f,  0.1f); // Up arrow
		
		if (myTimer.getElapsedTime() >= 1)
		{
			if(i != last) printf("FPS: %i\n", i);
			myTimer.restart();
			last = i;
			i = 0;
		}

		win.update();
		Debug::checkErrors();
	}

	return 0;
}