//main.cpp: For testing purposes only
//

#define DELTAENGINE_DEBUG

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
	Graphics::Window win(string("DeltaEngine Test Program!"), 960, 540, &handler);

	if(init(argc, argv) == DELTAENGINE_NOT_INITIALIZED) return -1;

	win.installMouse();

	Maths::Matrix4 ortho = Maths::Matrix4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Graphics::Shader shader(Utils::getCurrentPath() + "\\basic.vert", Utils::getCurrentPath() + "\\basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	vector<Maths::Vector3D> positions;
	positions.push_back(Maths::Vector3D(0, 0, 0));
	positions.push_back(Maths::Vector3D(5, 0, 0));

	Graphics::Renderable2D sprite(positions, Maths::Vector2D(1, 1), Types::Color(1, 0.5f, 0, 1), shader);
	Graphics::Renderer2D renderer;

	win.setVSync(true);
	printf("OK!\n");
	while (!win.closed())
	{
		win.clear();

		double x, y;
		win.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Maths::Vector2D((float)(x * 16.0f / win.getWidth()), (float)(y * 9.0f / win.getHeight())));
		renderer.submit(&sprite);
		renderer.flush();

		win.update();
		Debug::Debug::checkErrors();
	}

	return 0;
}