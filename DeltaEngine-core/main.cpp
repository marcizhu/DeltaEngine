//main.cpp: For testing purposes only
//

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
#include "batchRenderable2d.h"
#include "batchRenderer2d.h"
#include "camera.h"

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

	Graphics::Camera camera(0.0f, 16.0f, 9.0f, 0.0f, -1.0f, 1.0f);

	Graphics::Shader shader(Utils::getCurrentPath() + "\\basic.vert", Utils::getCurrentPath() + "\\basic.frag");
	shader.enable();
	
	//vector<Maths::Vector2D> positions;
	//positions.push_back(Maths::Vector2D(0, 0));
	//positions.push_back(Maths::Vector2D(5, 0));

	// Graphics::Renderable2D sprite(positions, 0, Maths::Vector2D(1, 1), Types::Color(255, 0, 0, 255), shader);
	// Graphics::Renderable2D sprite2(Maths::Vector2D(2.0, 0.0), 2, Maths::Vector2D(1, 1), Types::Color(0, 255, 0, 255), shader);
	// Graphics::Renderable2D sprite3(Maths::Vector2D(1.0, 1.0), 2, Maths::Vector2D(1, 1), Types::Color(0, 0, 255, 255), shader);

	Graphics::BatchRenderable2D sprite(0.0f, 0.0f, 1, 1, Types::Color(255, 0, 255, 255));
	Graphics::BatchRenderer2D renderer;

	Maths::Matrix4 view = Maths::Matrix4::identity();
	//view.translate(-1.0f, 0.0f, 0.0f);

	win.setVSync(true);

	Types::ushort16 i = 0, last = 0;
	float x, y;

	Timer::Timer myTimer;

	while (!win.closed())
	{
		win.clear();
		i++;

		win.getMousePosition(x, y);
		shader.setUniform2f("light_pos", (float)(x * 16.0f / win.getWidth()) - view.elements[12], (float)(9.0 - y * 9.0f / win.getHeight()) - view.elements[13]);

		shader.setUniformMat4("pr_matrix", camera.getMatrix4());
		shader.setUniformMat4("vw_matrix", view);

		renderer.begin();
		renderer.submit(&sprite);
		renderer.end();
		// renderer.submit(&sprite2);
		// renderer.submit(&sprite3);
		renderer.flush();

		if (win.isKeyPressed(65) && i == 1) Debug::dump(&camera, sizeof(camera));

		if (win.isKeyPressed(256)) break;

		if (win.isKeyPressed(262)) sprite.move( 0.1f,  0.0f); // Right arrow
		if (win.isKeyPressed(263)) sprite.move(-0.1f,  0.0f); // Left arrow
		if (win.isKeyPressed(264)) sprite.move( 0.0f, -0.1f); // Down arrow
		if (win.isKeyPressed(265)) sprite.move( 0.0f,  0.1f); // Up arrow
		
		if (myTimer.getElapsedTime() >= 1)
		{
			if(i != last) printf("FPS: %i\n", i);
			myTimer.restart();
			last = i;
			i = 0;
		}

		//camera.track(sprite2, 7.5f, 4.0f);
		win.update();
		Debug::checkErrors();
	}

	return 0;
}