//main.cpp: For testing purposes only
//
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
#include "batchRenderable2d.h"
#include "batchRenderer2d.h"
#include "sprite.h"
#include "Label.h"
#include "font.h"
#include "fontManager.h"

#ifdef _DEBUG
	#include "debug.h"
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

	win.installKeyboard();

	Maths::Matrix4 pr_matrix = Maths::Matrix4::orthographic(0.0f, 16.0f, 9.0f, 0.0f, -1.0f, 1.0f);

	Graphics::Shader* shader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\basic.vert", Utils::getCurrentPath() + "\\basic.frag");
	Graphics::Shader* bgshader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\basic.vert", Utils::getCurrentPath() + "\\basic.frag");
	Graphics::Shader* uiShader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\basic.vert", Utils::getCurrentPath() + "\\basic.frag");

	Graphics::TextureManager texManager;
	texManager.add(new Graphics::Texture("Background", "map.png", GL_NEAREST));
	texManager.add(new Graphics::Texture("Mario", "mario.png", GL_NEAREST));

	Graphics::Sprite marioSprite;
	marioSprite.add(new Graphics::Texture("Mario1", "mario0.png", GL_NEAREST));
	marioSprite.add(new Graphics::Texture("Mario2", "mario1.png", GL_NEAREST));
	marioSprite.add(new Graphics::Texture("Mario3", "mario2.png", GL_NEAREST));
	marioSprite.add(new Graphics::Texture("Mario4", "mario3.png", GL_NEAREST));

	Graphics::Layer2D mainLayer(new Graphics::BatchRenderer2D(), shader, pr_matrix);
	mainLayer.add(new Graphics::BatchRenderable2D(1.0f, 1.4f, 1, 1, marioSprite));

	Graphics::FontManager::add(new Graphics::Font("OpenSans", "OpenSans-Light.ttf", 24));
	Graphics::FontManager::get("OpenSans")->setScale(win.getHeight() / 9.0f, win.getWidth() / 16.0f);
	Graphics::Label* fpsLabel = new Graphics::Label("FPS: 0", 14.5f, 8.5f, "OpenSans", 0xffffffff);
	
	Graphics::Layer2D ui(new Graphics::BatchRenderer2D(), uiShader, pr_matrix);
	ui.add(fpsLabel);

	Graphics::Layer2D background(new Graphics::BatchRenderer2D(), bgshader, Maths::Matrix4::orthographic(0.0f, 320.0f, 200.0f, 0.0f, -1.0f, 1.0f));
	background.add(new Graphics::BatchRenderable2D(0.0f, 0.0f, 3583.0f, 240.0f, texManager.get("Background")));

	GLint texIDs[] = 
	{ 
		 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
		30, 31 
	};

	shader->enable();
	shader->setUniform1iv("textures", texIDs, 32);

	bgshader->enable();
	bgshader->setUniform1iv("textures", texIDs, 32);

	win.setVSync(true);

	Types::ushort16 i = 0, last = 0;
	float x = 1;

	Utils::Timer myTimer;

	while (!win.closed())
	{
		win.clear();

		float xpos = mainLayer[0]->getPosition().x;
		
		if (xpos > 7.5f)
		{
			mainLayer.setCameraPosition(-(xpos - 7.5f), 0);
			background.setCameraPosition(-((xpos - 7.5f) * 320 / 16), 0); // * 320 / 16 = scale factor
		}

		background.render();
		mainLayer.render();
		ui.render();

		if (win.isKeyPressed(256)) break;

		if (win.isKeyPressed(262)) // Right arrow
		{
			mainLayer[0]->move(0.1f, 0.0f);
			if (i % 3 == 0)
			{
				mainLayer[0]->getSprite().setCurrentTexture(x);
				x++;
				if (x >= 4) x = 1;
			}
		}
		else mainLayer[0]->getSprite().setCurrentTexture(0);
		if (win.isKeyPressed(263)) mainLayer[0]->move(-0.1f,  0.0f); // Left arrow
		if (win.isKeyPressed(264) && mainLayer[0]->getPosition().y >= 1.49f) mainLayer[0]->move( 0.0f, -0.1f); // Down arrow
		if (win.isKeyPressed(265)) mainLayer[0]->move( 0.0f,  0.1f); // Up arrow

		if (myTimer.getElapsedTime() >= 1)
		{
			if (i != last) fpsLabel->setText(std::string("FPS: " + std::to_string(i)));
			myTimer.restart();
			last = i;
			i = 0;
		}

		win.update();
		i++;
#ifdef _DEBUG
		Debug::checkErrors();
#endif
	}

	return 0;
}