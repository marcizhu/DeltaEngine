//main.cpp: For testing purposes only
//

#define DELTAENGINE_DEBUG

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include <GLEW\glew.h>
#include <FreeGLUT\freeglut.h> //Remove extra configurations! (additional lib dirs, additional dependencies)

#include "window.h"
#include "maths.h"
#include "utils.h"
#include "Matrix4.h"
#include "vector2d.h"
#include "shader.h"

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
	//win.clearToColor(0.0, 0.2, 0.7, 1.0);
	win.installMouse();
	doMyJobForTesting();

	Maths::Matrix4 ortho = Maths::Matrix4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Graphics::Shader shader(Utils::getCurrentPath() + "\\basic.vert", Utils::getCurrentPath() + "\\basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", Maths::Matrix4::translate(Maths::Vector3D(4, 3, 0)));

	shader.setUniform2f("light_pos", Maths::Vector2D(4.0f, 1.5f));
	shader.setUniform4f("colour", Maths::Vector4D(0.2f, 0.3f, 0.8f, 1.0f));

	printf("OK!\n");
	win.setVSync(true);
	while (!win.closed())
	{
		win.clear();
		//MINE!
		/*glColor3f(0.7f, 0.7f, 1.0f);
		glRectf(-0.75f, 0.75f, 0.75f, -0.75f);*/

		double x, y;
		win.getMousePosition(x, y);
		shader.setUniform2f("light_pos", Maths::Vector2D((float)(x * 16.0f / 960.0f), (float)(9.0f - y * 9.0f / 540.0f)));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		win.update();
	}
	return 0;
}