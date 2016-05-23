#include <Windows.h>

#include "Application.h"

#define LASER_SPEED 15.0f

Application::Application() : Game()
{
	this->createWindow("[DeltaEngine] ATARI Asteroids", 960, 540);
	int init = DeltaEngine::init();
	DELTAENGINE_ASSERT(init != DELTAENGINE_NOT_INITIALIZED, "DELTAENGINE NOT INITIALIZED!");
}

Application::~Application()
{
	delete world;
	delete playArea;

	Graphics::FontManager::clean();
	Graphics::TextureManager::clean();
	Sound::SoundManager::clean();

	Memory::MemoryManager::end();
}

void Application::init()
{
	SetConsoleTitle(TEXT("DeltaEngine Debug Output"));

	shader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\res\\shaders\\basic.shader");
	bgShader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\res\\shaders\\basic.shader");

	Sound::SoundManager::init();
	Sound::SoundManager::add(NEW Sound::Sound("Laser", Utils::getCurrentPath() + "\\res\\sounds\\laser.ogg"));
	//Sound::SoundManager::add(NEW Sound::Sound("Music", Utils::getCurrentPath() + "\\res\\sounds\\music.ogg"));

	//Sound::SoundManager::get("Music")->loop();
	//Sound::SoundManager::get("Music")->setGain(0.7f);

	Graphics::TextureManager::add(NEW Graphics::Texture("Spaceship", Utils::getCurrentPath() + "\\res\\assets\\spaceship.png", GL_NEAREST));
	Graphics::TextureManager::add(NEW Graphics::Texture("Laser", Utils::getCurrentPath() + "\\res\\assets\\laser.png", GL_NEAREST));
	Graphics::TextureManager::add(NEW Graphics::Texture("Alien", Utils::getCurrentPath() + "\\res\\assets\\alien.png"));
	Graphics::TextureManager::add(NEW Graphics::Texture("Background", Utils::getCurrentPath() + "\\res\\assets\\background.jpg"));
	Graphics::TextureManager::add(NEW Graphics::Texture("Asteroid Big 1", Utils::getCurrentPath() + "\\res\\assets\\asteroid-1.png"));
	Graphics::TextureManager::add(NEW Graphics::Texture("Asteroid Big 2", Utils::getCurrentPath() + "\\res\\assets\\asteroid-2.png"));
	Graphics::TextureManager::add(NEW Graphics::Texture("Asteroid Small 1", Utils::getCurrentPath() + "\\res\\assets\\asteroid-small-1.png"));
	Graphics::TextureManager::add(NEW Graphics::Texture("Asteroid Smaller 1", Utils::getCurrentPath() + "\\res\\assets\\asteroid-smallest-1.png"));

	world = NEW Physics::World2D(NEW Physics::PhysicsRenderer2D(), shader, Maths::Matrix4::orthographic(0.0f, 24.0f, 13.5f, 0.0f, -1.0f, 1.0f), 0.0f);
	world->setLimits(false);
	world->add(NEW Physics::PhysicsRenderable2D(12.0f, 6.75f, 1.0f, 1.0f, Graphics::TextureManager::get("Spaceship"), 1.0f, 5));

	Physics::PhysicsRenderable2D* asteroid1 = (Physics::PhysicsRenderable2D*)world->add(NEW Physics::PhysicsRenderable2D(3.0f, 3.0f, 2.0f, 2.0f, Graphics::TextureManager::get("Asteroid Big 1"), 1.0f, 1));
	Physics::PhysicsRenderable2D* asteroid2 = (Physics::PhysicsRenderable2D*)world->add(NEW Physics::PhysicsRenderable2D(9.0f, 1.0f, 2.0f, 2.0f, Graphics::TextureManager::get("Asteroid Big 2"), 1.0f, 1));
	Physics::PhysicsRenderable2D* asteroid3 = (Physics::PhysicsRenderable2D*)world->add(NEW Physics::PhysicsRenderable2D(16.0f, 11.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Asteroid Small 1"), 1.0f, 1));
	Physics::PhysicsRenderable2D* asteroid4 = (Physics::PhysicsRenderable2D*)world->add(NEW Physics::PhysicsRenderable2D(10.0f, 8.0f, 0.5f, 0.5f, Graphics::TextureManager::get("Asteroid Smaller 1"), 1.0f, 1));

	srand(Utils::getSystemTime().Milliseconds);
	asteroid1->setVelocity((float)2.0f * rand() / RAND_MAX, (float)360.0f * rand() / RAND_MAX);

	background = NEW Graphics::Layer2D(NEW Graphics::BatchRenderer2D(), bgShader, Maths::Matrix4::orthographic(0.0f, 960.0f, 540.0f, 0.0f, -1.0f, 1.0f));
	background->add(NEW Graphics::BatchRenderable2D(-480.0f, -330.0f, 1920.0f, 1200.0f, Graphics::TextureManager::get("Background")));

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

	window->setVSync(VSYNC_ENABLE);

	world->setCameraPosition(0, 0);

	playArea = NEW Maths::AABB(Maths::Vector2D(-1.0f, -1.0f), Maths::Vector2D(25.0f, 14.0f));
}

void Application::update()
{
	if (window->isKeyPressed(KB_KEY_ESCAPE)) window->close();

	Physics::PhysicsRenderable2D* spaceship = Utils::toPhysicsRenderable((*world)[0]);
	Physics::PhysicsRenderable2D* asteroid1 = Utils::toPhysicsRenderable((*world)[1]);

	Sound::SoundManager::update();

	if (window->isKeyPressed(KB_KEY_SPACE))
		spaceship->setAcceleration(9.0f);
	else
		spaceship->setAcceleration(0.0f);

	if (window->isKeyPressed(KB_KEY_RIGHT)) spaceship->rotate(-5.0f);
	if (window->isKeyPressed(KB_KEY_LEFT )) spaceship->rotate( 5.0f);

	if (window->isKeyPressed(KB_KEY_W) && !keyHeld)
	{
		//const float intensity = 0.7f;
		//const float pos = (1.0f - intensity) + ((intensity * (spaceship->getPosition().x) / 12) - 1);
		Sound::SoundManager::get("Laser")->play();
		Sound::SoundManager::get("Laser")->setPosition(Maths::Vector2D(spaceship->getPosition().x / 12.0f - 1.0f, spaceship->getPosition().y / 6.25f - 1.0f), 0.7f);
		//Sound::SoundManager::get("Laser")->setPan(pos);

		Physics::PhysicsRenderable2D* laser = NEW Physics::PhysicsRenderable2D(spaceship->getPosition().x, spaceship->getPosition().y, 0.5f, 0.5f, Graphics::TextureManager::get("Laser"), 1.0f, 1);
		laser->setRotation(spaceship->getRotation());
		laser->setVelocity(LASER_SPEED);
		shots.push_back(laser);
		world->add(laser);
		keyHeld = true;
	}
	else if(!window->isKeyPressed(KB_KEY_W)) keyHeld = false;

	auto& iter = shots.begin();

	while (iter != shots.end())
	{
		if (!playArea->contains((*iter)->getPosition()))
		{
			world->remove(*iter);
			delete (*iter);
			iter = shots.erase(iter);
		}
		else ++iter;
	}

	shots.shrink_to_fit();

	if (spaceship->getPosition().x > 25.0f) spaceship->setPosition(-1.0f, spaceship->getPosition().y);
	if (spaceship->getPosition().x < -1.0f) spaceship->setPosition(25.0f, spaceship->getPosition().y);

	if (spaceship->getPosition().y > 14.0f) spaceship->setPosition(spaceship->getPosition().x, -1.0f);
	if (spaceship->getPosition().y < -1.0f) spaceship->setPosition(spaceship->getPosition().x, 14.0f);

	const float absX = 11.5f - spaceship->getPosition().x;
	const float absY = 6.25f - spaceship->getPosition().y;

	background->setCameraPosition(background->getCameraPositionX() + 0.025f * absX, background->getCameraPositionY() + 0.025f * absY);

	world->update(1.0f / 60.0f);
}

void Application::render()
{
	background->render();
	world->render();
}

void Application::tick()
{
	//DELTAENGINE_INFO("FPS: ", getFPS());
}