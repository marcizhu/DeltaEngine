#include <Windows.h>

#include "Application.h"

Application::Application(int argc, char* argv[]) : Game()
{
	this->createWindow("[DeltaEngine] Super Mario Bros", 960, 540);
	int init = DeltaEngine::init(argc, argv);
	DELTAENGINE_ASSERT(init != DELTAENGINE_NOT_INITIALIZED, "DELTAENGINE NOT INITIALIZED!");
}

Application::~Application()
{
	DELETE mainLayer;
}

void Application::init()
{
	SetConsoleTitle(TEXT("DeltaEngine Debug Output"));

	window->clearToColor(0.5f, 0.5f, 1.0f, 0.0f);

	Maths::Matrix4 pr_matrix = Maths::Matrix4::orthographic(0.0f, 24.0f, 13.5f, 0.0f, -1.0f, 1.0f);

	shader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\res\\shaders\\basic.shader");

	Graphics::TextureManager::add(new Graphics::Texture("Cloud big", ".\\res\\assets\\cloud-big.png", GL_NEAREST));
	Graphics::TextureManager::add(new Graphics::Texture("Cloud small", ".\\res\\assets\\cloud-small.png", GL_NEAREST));
	Graphics::TextureManager::add(new Graphics::Texture("Ground", ".\\res\\assets\\ground.png", GL_NEAREST));
	Graphics::TextureManager::add(new Graphics::Texture("Pipe", ".\\res\\assets\\pipe.png", GL_NEAREST));
	Graphics::TextureManager::add(new Graphics::Texture("Hill big", ".\\res\\assets\\hill-big.png", GL_NEAREST));
	Graphics::TextureManager::add(new Graphics::Texture("Hill small", ".\\res\\assets\\hill-small.png", GL_NEAREST));
	Graphics::TextureManager::add(new Graphics::Texture("Bush big", ".\\res\\assets\\bush-big.png", GL_NEAREST));
	Graphics::TextureManager::add(new Graphics::Texture("Question 1", ".\\res\\assets\\question-block-1.png", GL_NEAREST));
	Graphics::TextureManager::add(new Graphics::Texture("Bricks", ".\\res\\assets\\bricks.png", GL_NEAREST));
	Graphics::TextureManager::add(new Graphics::Texture("Mushroom", ".\\res\\assets\\mushroom.png", GL_NEAREST));
	
	mainLayer = new Graphics::Layer2D(new Graphics::BatchRenderer2D(), shader, pr_matrix);

	for (int y = 0; y < 14; y++)
	{
		if (y == 0)
			mainLayer->add(NEW Graphics::Line(0.0f, y, 70.0f, y, 16.0f / 960.0f, 0xFF0000FF));
		else
			mainLayer->add(NEW Graphics::Line(0.0f, y, 70.0f, y, 16.0f / 960.0f, 0x3FFFFFFF));
	}

	for (int x = 0; x < 70; x++)
	{
		if (x == 0)
			mainLayer->add(NEW Graphics::Line(x, 0.0f, x, 14.0f, 16.0f / 960.0f, 0xFF0000FF));
		else
			mainLayer->add(NEW Graphics::Line(x, 0.0f, x, 14.0f, 16.0f / 960.0f, 0x3FFFFFFF));
	}

	mainLayer->add(new Graphics::BatchRenderable2D(0.0f, 2.0f, 5.0f, 3.0f, Graphics::TextureManager::get("Hill big")));

	mainLayer->add(new Graphics::BatchRenderable2D(9.0f, 10.0f, 3.0f, 2.0f, Graphics::TextureManager::get("Cloud small")));

	// this should be bigger (3-piece bush, not 2)
	mainLayer->add(new Graphics::BatchRenderable2D(12.0f, 2.0f, 3.0f, 1.0f, Graphics::TextureManager::get("Bush big")));

	mainLayer->add(new Graphics::BatchRenderable2D(17.0f, 2.0f, 3.0f, 2.0f, Graphics::TextureManager::get("Hill small")));
	
	mainLayer->add(new Graphics::BatchRenderable2D(17.0f, 5.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Question 1")));

	mainLayer->add(new Graphics::BatchRenderable2D(21.0f, 5.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Bricks")));

	mainLayer->add(new Graphics::BatchRenderable2D(22.0f, 5.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Question 1")));

	mainLayer->add(new Graphics::BatchRenderable2D(22.0f, 6.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Mushroom")));

	mainLayer->add(new Graphics::BatchRenderable2D(23.0f, 5.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Bricks")));

	mainLayer->add(new Graphics::BatchRenderable2D(23.0f, 9.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Question 1")));

	mainLayer->add(new Graphics::BatchRenderable2D(24.0f, 5.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Question 1")));

	mainLayer->add(new Graphics::BatchRenderable2D(25.0f, 5.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Bricks")));

	mainLayer->add(new Graphics::BatchRenderable2D(29.0f, 2.0f, 2.0f, 2.0f, Graphics::TextureManager::get("Pipe")));
	
	for (float i = 0.0f; i < 69.0f; i++)
	{
		mainLayer->add(new Graphics::BatchRenderable2D(i, 0.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Ground")));
		mainLayer->add(new Graphics::BatchRenderable2D(i, 1.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Ground")));
	}

	GLint texIDs[] =
	{
		0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
		30, 31
	};

	shader->enable();
	shader->setUniform1iv("textures", texIDs, 32);

	window->setVSync(true);
}

void Application::update()
{
	// 60 times per second
	if (window->isKeyPressed(KB_KEY_ESCAPE)) window->close();

	if (window->isKeyPressed(KB_KEY_RIGHT)) mainLayer->setCameraPosition(mainLayer->getCameraPositionX() - 0.1f, 0.0f);
	if (window->isKeyPressed(KB_KEY_LEFT) && (mainLayer->getCameraPositionX() <= -0.1f)) mainLayer->setCameraPosition(mainLayer->getCameraPositionX() + 0.1f, 0.0f);
}

void Application::render()
{
	// as fast as possible (unless vsync is enabled)
	mainLayer->render();
}

void Application::tick()
{
	DELTAENGINE_INFO("FPS: ", getFPS());
}