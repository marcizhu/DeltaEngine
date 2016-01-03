//main.cpp: For testing purposes only
//
#if 1
#define BATCH_RENDERER

#include <stdio.h>
#include <string>

#include <GLEW\glew.h>

#include "layer2d.h"
#include "matrix4.h"
#include "window.h"
#include "shader.h"
#include "utils.h"
#include "timer.h"
#include "texture.h"
#include "textureManager.h"

#ifdef _DEBUG
	#include "debug.h"
#endif

#ifdef BATCH_RENDERER
	#include "batchRenderable2d.h"
	#include "batchRenderer2d.h"
#else
	#include "simpleRenderable2d.h"
	#include "simpleRenderer2d.h"
#endif


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

	if (init(argc, argv) == DELTAENGINE_NOT_INITIALIZED) return -1;

	win.installMouse();
	win.installKeyboard();
	win.clearToColor(0.2, 0.3, 0.8, 1.0);

	Maths::Matrix4 pr_matrix = Maths::Matrix4::orthographic(0.0f, 16.0f, 9.0f, 0.0f, -1.0f, 1.0f);

	Graphics::Shader* shader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\basic.vert", Utils::getCurrentPath() + "\\basic.frag");

#ifdef BATCH_RENDERER
	Graphics::TextureManager texManager;
	texManager.add(new Graphics::Texture("Mario", "mario.png", GL_NEAREST));
	texManager.add(new Graphics::Texture("Pipe", "test.png", GL_NEAREST));

	Graphics::Layer2D mainLayer(new Graphics::BatchRenderer2D(), shader, pr_matrix);
	mainLayer.add(new Graphics::BatchRenderable2D(0.0f, 0.0f, 1, 1, texManager.get("Mario")));
	mainLayer.add(new Graphics::BatchRenderable2D(2.0f, 0.0f, 1, 1, texManager.get("Pipe")));
	mainLayer.add(new Graphics::BatchRenderable2D(5.0f, 0.0f, 1, 1, texManager.get("Pipe")));

	GLint texIDs[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	shader->enable();
	shader->setUniform1iv("textures", texIDs, 10);
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

	Utils::Timer myTimer;

	while (!win.closed())
	{
		win.clear();
		i++;
		c++;

		win.getMousePosition(x, y);
		shader->setUniform2f("light_pos", (float)(x * 16.0f / win.getWidth()) - mainLayer.getCameraPositionX(), (float)(9.0 - y * 9.0f / win.getHeight()) - mainLayer.getCameraPositionY());

		//mainLayer.setCameraPosition(-(c / 60), 0);
		mainLayer.render();

		if (win.isKeyPressed(256)) break;

		if (win.isKeyPressed(262)) mainLayer[0]->move( 0.1f,  0.0f); // Right arrow
		if (win.isKeyPressed(263)) mainLayer[0]->move(-0.1f,  0.0f); // Left arrow
		if (win.isKeyPressed(264)) mainLayer[0]->move( 0.0f, -0.1f); // Down arrow
		if (win.isKeyPressed(265)) mainLayer[0]->move( 0.0f,  0.1f); // Up arrow

		if (myTimer.getElapsedTime() >= 1)
		{
			if (i != last) printf("FPS: %i\n", i);
			myTimer.restart();
			last = i;
			i = 0;
		}

		win.update();
#ifdef _DEBUG
		Debug::checkErrors();
#endif
	}

	return 0;
}
#endif 
