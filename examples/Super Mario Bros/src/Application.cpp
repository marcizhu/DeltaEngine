#include <Windows.h>

#include "Application.h"

Application::Application() : Game()
{
	this->createWindow("[DeltaEngine] Super Mario Bros", 960, 540, "res/assets/mushroom.ico");
	int init = DeltaEngine::init();
	DELTAENGINE_ASSERT(init != DELTAENGINE_NOT_INITIALIZED, "DELTAENGINE NOT INITIALIZED!");
}

Application::~Application()
{
	delete world;
}

void Application::init()
{
	SetConsoleTitle(TEXT("DeltaEngine Debug Output"));

	window->clearToColor(0.5f, 0.5f, 1.0f, 0.0f);

	Maths::Matrix4 pr_matrix = Maths::Matrix4::orthographic(0.0f, 24.0f, 13.5f, 0.0f);

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

	world = new Physics::World2D(shader, pr_matrix, Maths::Vector2D(0.0f, -10.0f));

	world->add(new Physics::DynamicBody(0.0f, 2.0f, 5.0f, 3.0f, Graphics::TextureManager::get("Hill big"), 1.0f));
	world->add(new Physics::DynamicBody(9.0f, 10.0f, 3.0f, 2.0f, Graphics::TextureManager::get("Cloud small"), 1.0f));

	// this should be bigger (3-piece bush, not 2)
	world->add(new Physics::DynamicBody(12.0f, 2.0f, 3.0f, 1.0f, Graphics::TextureManager::get("Bush big"), 1.0f));
	world->add(new Physics::DynamicBody(17.0f, 2.0f, 3.0f, 2.0f, Graphics::TextureManager::get("Hill small"), 1.0f));
	world->add(new Physics::DynamicBody(17.0f, 5.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Question 1"), 1.0f));
	world->add(new Physics::DynamicBody(21.0f, 5.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Bricks"), 1.0f));
	world->add(new Physics::DynamicBody(22.0f, 5.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Question 1"), 1.0f));
	world->add(new Physics::DynamicBody(22.0f, 6.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Mushroom"), 1.0f));
	world->add(new Physics::DynamicBody(23.0f, 5.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Bricks"), 1.0f));
	world->add(new Physics::DynamicBody(23.0f, 9.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Question 1"), 1.0f));
	world->add(new Physics::DynamicBody(24.0f, 5.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Question 1"), 1.0f));
	world->add(new Physics::DynamicBody(25.0f, 5.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Bricks"), 1.0f));
	world->add(new Physics::StaticBody(30.0f, 3.0f, 2.0f, 2.0f, Graphics::TextureManager::get("Pipe"), 1.0f));

	for (float i = 0.0f; i < 69.0f; i++)
	{
		world->add(new Physics::StaticBody(i + 0.5f, 0.5f, 1.0f, 1.0f, Graphics::TextureManager::get("Ground"), 0.0f));
		world->add(new Physics::StaticBody(i + 0.5f, 1.5f, 1.0f, 1.0f, Graphics::TextureManager::get("Ground"), 0.0f));
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

	window->setVSync(VSYNC_NON_BLOCKING);
}

void Application::update(float deltaTime)
{
	// 60 times per second
	if (window->isKeyPressed(KB_KEY_ESCAPE)) window->close();

	if (window->isKeyPressed(KB_KEY_RIGHT)) world->setCameraPosition(world->getCameraPositionX() - 0.1f, 0.0f);

	if (window->isKeyPressed(KB_KEY_LEFT) && (world->getCameraPositionX() <= -0.1f))
		world->setCameraPosition(world->getCameraPositionX() + 0.1f, 0.0f);
	else if(window->isKeyPressed(KB_KEY_LEFT) && (world->getCameraPositionX() > 0.0f))
		world->setCameraPosition(0.0f, 0.0f);

	world->step(1.0f / 60.0f, 6, 3);
}

void Application::render()
{
	// as fast as possible (unless vsync is enabled)
	world->render();
}

void Application::tick()
{
	DELTAENGINE_INFO("FPS: ", getFPS(), " (UPS: ", getUPS(), ")");
}