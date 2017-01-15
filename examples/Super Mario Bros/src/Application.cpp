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
	delete mainLayer;
}

void Application::init()
{
	SetConsoleTitle(TEXT("DeltaEngine Debug Output"));

	window->clearToColor(0.5f, 0.5f, 1.0f, 0.0f);

	Maths::Matrix4 pr_matrix = Maths::Matrix4::orthographic(0.0f, 24.0f, 13.5f, 0.0f);

	shader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\res\\shaders\\basic.shader");
	bgShader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\res\\shaders\\basic.shader");

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
	Graphics::TextureManager::add(new Graphics::Texture("Mario", ".\\res\\assets\\mario.png", GL_NEAREST));

	world = new Physics::World2D(shader, pr_matrix, Maths::Vector2D(0.0f, -15.0f));
	mainLayer = new Graphics::Layer2D(new Graphics::BatchRenderer2D(), bgShader, pr_matrix);

	mainLayer->add(new Graphics::BatchRenderable2D(0.0f, 2.0f, 5.0f, 3.0f, Graphics::TextureManager::get("Hill big")));
	mainLayer->add(new Graphics::BatchRenderable2D(9.0f, 10.0f, 3.0f, 2.0f, Graphics::TextureManager::get("Cloud small")));

	// this should be bigger (3-piece bush, not 2)
	mainLayer->add(new Graphics::BatchRenderable2D(12.0f, 2.0f, 3.0f, 1.0f, Graphics::TextureManager::get("Bush big")));
	mainLayer->add(new Graphics::BatchRenderable2D(17.0f, 2.0f, 3.0f, 2.0f, Graphics::TextureManager::get("Hill small")));
	world->add(new Physics::PlayerBody(1.5f, 4.5f, 1.0f, 1.0f, Graphics::TextureManager::get("Mario"), 1.0f));
	world->add(new Physics::StaticBody(17.5f, 5.5f, 1.0f, 1.0f, Graphics::TextureManager::get("Question 1"), 0.0f));
	world->add(new Physics::StaticBody(21.5f, 5.5f, 1.0f, 1.0f, Graphics::TextureManager::get("Bricks"), 0.0f));
	world->add(new Physics::StaticBody(22.5f, 5.5f, 1.0f, 1.0f, Graphics::TextureManager::get("Question 1"), 0.0f));
	world->add(new Physics::DynamicBody(22.5f, 6.5f, 1.0f, 1.0f, Graphics::TextureManager::get("Mushroom"), 1.0f));
	world->add(new Physics::StaticBody(23.5f, 5.5f, 1.0f, 1.0f, Graphics::TextureManager::get("Bricks"), 0.0f));
	world->add(new Physics::StaticBody(23.5f, 9.5f, 1.0f, 1.0f, Graphics::TextureManager::get("Question 1"), 0.0f));
	world->add(new Physics::StaticBody(24.5f, 5.5f, 1.0f, 1.0f, Graphics::TextureManager::get("Question 1"), 0.0f));
	world->add(new Physics::StaticBody(25.5f, 5.5f, 1.0f, 1.0f, Graphics::TextureManager::get("Bricks"), 0.0f));
	world->add(new Physics::StaticBody(30.0f, 3.0f, 2.0f, 2.0f, Graphics::TextureManager::get("Pipe"), 0.0f));

	// (*world)[4]->setLinearVelocity(1.0f, 0.01f);

	for (float i = 0.0f; i < 69.0f; i++)
	{
		mainLayer->add(new Graphics::BatchRenderable2D(i, 0.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Ground")));
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

	bgShader->enable();
	bgShader->setUniform1iv("textures", texIDs, 32);

	window->setVSync(VSYNC_NON_BLOCKING);
}

void Application::update(float deltaTime)
{
	if (window->isKeyPressed(KB_KEY_ESCAPE)) window->close();

	Physics::PlayerBody* player = (Physics::PlayerBody*)(*world)[0];

	if (window->isKeyPressed(KB_KEY_RIGHT))
	{
		if (!right)
		{
			player->setLinearVelocity(5.0f, player->getVelocity().y);
			right = true;
		}
	}
	else if (right == true)
	{
		player->setLinearVelocity(0.0f, player->getVelocity().y);
		right = false;
	}

	if (window->isKeyPressed(KB_KEY_LEFT))
	{
		if (!left)
		{
			player->setLinearVelocity(-5.0f, player->getVelocity().y);
			left = true;
		}
	}
	else if (left == true)
	{
		player->setLinearVelocity(0.0f, player->getVelocity().y);
		left = false;
	}

	if (window->isKeyPressed(KB_KEY_SPACE))
	{
		if (!jumping && player->getVelocity().y < 0.01f && player->getVelocity().y > -0.01f)
		{
			player->applyImpulse(12.0f, Maths::toRadians(90.0f));
			jumping = true;
		}
	}
	else jumping = false;

	if (player->getPosition().x > 12.0f)
	{
		world->setCameraPosition(-(player->getPosition().x - 12), 0.0f);
		mainLayer->setCameraPosition(-(player->getPosition().x - 12), 0.0f);
	}

	if (player->getPosition().y < -0.51f)
	{
		DELTAENGINE_INFO("GAME OVER!");
		while (1);
	}

	world->step(1.0f / 60.0f, 6, 3);
}

void Application::render()
{
	// as fast as possible (unless vsync is enabled)
	mainLayer->render();
	world->render();
}

void Application::tick()
{
	DELTAENGINE_INFO("FPS: ", getFPS(), " (UPS: ", getUPS(), ")");
}