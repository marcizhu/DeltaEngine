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
#include "sound.h"
#include "soundManager.h"

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

	Audio::SoundManager::init();
	Audio::SoundManager::add(new Audio::Sound("Music", Utils::getCurrentPath() + "\\music.ogg"));
	Audio::SoundManager::get("Music")->play();
	
	GLfloat vertices[] =
	{
		 0, 0, 0,
		16, 0, 0,
		 0, 9, 0,
		 0, 9, 0,
		16, 9, 0,
		16, 0, 0
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	Maths::Matrix4 ortho = Maths::Matrix4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Graphics::Shader shader(Utils::getCurrentPath() + "\\basic.vert", Utils::getCurrentPath() + "\\basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", Maths::Matrix4::translate(Maths::Vector3D(0, 0, 0)));

	shader.setUniform2f("light_pos", Maths::Vector2D(4.0f, 1.5f));
	shader.setUniform4f("colour", Maths::Vector4D(0.2f, 0.3f, 0.8f, 1.0f));

	win.setVSync(true);
	printf("OK!\n");
	while (!win.closed())
	{
		win.clear();
		//MINE!
		/*glColor3f(0.7f, 0.7f, 1.0f);
		glRectf(-0.75f, 0.75f, 0.75f, -0.75f);*/

		double x, y;
		win.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Maths::Vector2D((float)(x * 16.0f / win.getWidth()), (float)(9.0f - y * 9.0f / win.getHeight())));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		win.update();
		Audio::SoundManager::update();
	}

	Audio::SoundManager::clean();
	return 0;
}