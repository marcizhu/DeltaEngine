//main.cpp: For testing purposes only
//

#define DELTAENGINE_DEBUG

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include <GLEW\glew.h>

#include "window.h"
#include "maths.h"
#include "utils.h"
#include "Matrix4.h"
#include "vector2d.h"
#include "shader.h"
//#include "sound.h"
//#include "soundManager.h"
#include "debug.h"

#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"

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
	
#ifdef TEST_AUDIO
	Audio::SoundManager::init();
	Audio::SoundManager::add(new Audio::Sound("Music", Utils::getCurrentPath()  "\\music.ogg"));
	Audio::SoundManager::get("Music")->loop();
#endif

	GLfloat vertices[] =
	{
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0
	};

	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GLfloat colorsA[] =
	{
		1, 1.0, 0, 1,
		1, 0.6, 0, 1,
		1, 0.3, 0, 1,
		1, 0.0, 0, 1
	};

	GLfloat colorsB[] =
	{
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1,
		0.2f, 0.3f, 0.8f, 1
	};

	Graphics::VertexArray sprite1, sprite2;
	Graphics::IndexBuffer ibo(indices, 6);

	sprite1.addBuffer(new Graphics::Buffer(vertices, 4 * 3, 3), 0);
	sprite1.addBuffer(new Graphics::Buffer(colorsA, 4 * 4, 4), 1);

	sprite2.addBuffer(new Graphics::Buffer(vertices, 4 * 3, 3), 0);
	sprite2.addBuffer(new Graphics::Buffer(colorsB, 4 * 4, 4), 1);

	Maths::Matrix4 ortho = Maths::Matrix4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Graphics::Shader shader(Utils::getCurrentPath() + "\\basic.vert", Utils::getCurrentPath() + "\\basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);

	win.setVSync(true);
	printf("OK!\n");
	while (!win.closed())
	{
		win.clear();

		double x, y;
		win.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Maths::Vector2D((float)(x * 16.0f / win.getWidth()), (float)(y * 9.0f / win.getHeight())));
		
		sprite1.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", Maths::Matrix4::translate(Maths::Vector3D(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite1.unbind();

		sprite2.bind();
		ibo.bind();
		shader.setUniformMat4("ml_matrix", Maths::Matrix4::translate(Maths::Vector3D(0, 0, 0)));
		glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite2.unbind();

		win.update();
		Debug::Debug::checkErrors();

#ifdef TEST_AUDIO
		Audio::SoundManager::update();
#endif
	}

#ifdef TEST_AUDIO
	Audio::SoundManager::clean();
#endif
	return 0;
}