#include <Windows.h>

#include "Sandbox.h"

// UI: https://cdn.designmaz.net/wp-content/uploads/2014/01/clean-ui-kit.jpg

Sandbox::Sandbox() : Game()
{
	this->createWindow("DeltaEngine Sandbox", 960, 540, "mario.ico");
	int init = DeltaEngine::init();
	DELTAENGINE_ASSERT(init != DELTAENGINE_NOT_INITIALIZED, "DELTAENGINE NOT INITIALIZED!");
}

Sandbox::~Sandbox()
{
	delete myWorld;
	delete ui;
	delete myList;

	Graphics::FontManager::clean();
	Graphics::TextureManager::clean();
	//Sound::SoundManager::clean();

	Memory::MemoryManager::end();
}

void Sandbox::init()
{
	SetConsoleTitle(TEXT("DeltaEngine Debug Output"));

	Maths::Matrix4 pr_matrix = Maths::Matrix4::orthographic(0.0f, 16.0f, 9.0f, 0.0f);

	shader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\basic.shader");
	uiShader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\basic.shader");

	/*Sound::SoundManager::init();
	Sound::SoundManager::add(NEW Sound::Sound("Intro", Utils::getCurrentPath() + "\\intro.ogg"));
	Sound::SoundManager::add(NEW Sound::Sound("Intro 2", Utils::getCurrentPath() + "\\intro 2.ogg"));

	_DELTAENGINE_INFO("DeltaEngine: [Sandbox] Loading sounds");

	while(Sound::SoundManager::get("Intro")->isReady() == false)
	{
		_DELTAENGINE_INFO(".");
		Sleep(100);
	}

	_DELTAENGINE_INFO("\n");

	myList = NEW Sound::Playlist;
	myList->add(Sound::SoundManager::get("Intro"));
	myList->add(Sound::SoundManager::get("Intro"));
	myList->add(Sound::SoundManager::get("Intro 2"));

	myList->play();*/

	Graphics::TextureManager::add(NEW Graphics::Texture("Mario", "mario.png", GL_NEAREST));

	myWorld = NEW Physics::World2D(NEW Physics::PhysicsRenderer2D(), shader, pr_matrix, Maths::Vector2D(0.0f, -2.0f)); // 0.010f
	myWorld->add(NEW Physics::PhysicsRenderable2D(8.0f, 8.0f, 1.0f, 1.0f, Graphics::TextureManager::get("Mario"), 1.0f));

	Graphics::FontManager::add(NEW Graphics::Font("OpenSans", "OpenSans-Light.ttf", 24));
	Graphics::FontManager::add(NEW Graphics::Font("Consolas", "consola.ttf", 18));
	memoryLabel = NEW Graphics::Label("", 11.5f, 8.6f, "Consolas", 0xffffcf37);
	fpsLabel = NEW Graphics::Label("FPS: 0", 14.2f, 8.0f, "OpenSans", 0xffffffff);
	debugLabel = NEW Graphics::Label("", 0.2f, 8.6f, "Consolas", 0xff00ffff);

	string version = string((char*)glGetString(GL_VERSION));
	string vendor = string((char*)glGetString(GL_VENDOR));
	string renderer = string((char*)glGetString(GL_RENDERER));

	debugLabel->setText(string("Version : " + version + "\nVendor  : " + vendor + "\nRenderer: " + renderer));

	ui = NEW Graphics::Layer2D(NEW Graphics::BatchRenderer2D(), uiShader, pr_matrix);
	ui->add(debugLabel);
	ui->add(fpsLabel);
	ui->add(memoryLabel);

#ifdef DELTAENGINE_DEBUG
	ui->add(NEW Graphics::Line(0.0f, 0.0f, 20.0f, 0.0f, 16.0f / 960.0f, 0xFF0000FF));
	ui->add(NEW Graphics::Line(0.0f, 0.0f, 0.0f, 20.0f, 16.0f / 960.0f, 0xFF0000FF));

	for (float y = 1.0f; y < 20.0f; y++)
	{
		ui->add(NEW Graphics::Line(0.0f, y, 20.0f, y, 16.0f / 960.0f, 0x3FFFFFFF));
	}

	for (float x = 1.0f; x < 20.0f; x++)
	{
		ui->add(NEW Graphics::Line(x, 0.0f, x, 20.0f, 16.0f / 960.0f, 0x3FFFFFFF));
	}
#endif

	GLint texIDs[] =
	{
		 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
		30, 31
	};

	shader->enable();
	shader->setUniform1iv("textures", texIDs, 32);

	uiShader->enable();
	uiShader->setUniform1iv("textures", texIDs, 32);

	window->setVSync(VSYNC_NON_BLOCKING);
}

void Sandbox::update(float deltaTime)
{
	//Sound::SoundManager::update();

	Graphics::FontManager::setScale(window->getHeight() / 9.0f, window->getWidth() / 16.0f);

	if (window->isKeyPressed(KB_KEY_ESCAPE)) window->close();

	//if (window->isKeyPressed(KB_KEY_RIGHT)) Utils::toPhysicsRenderable((*myWorld)[0])->rotate( 5.0f); // Right arrow
	//if (window->isKeyPressed(KB_KEY_LEFT )) Utils::toPhysicsRenderable((*myWorld)[0])->rotate(-5.0f); // Left arrow
	if (window->isKeyPressed(KB_KEY_DOWN )) (*myWorld)[0]->move( 0.0f, -0.1f); // Down arrow
	if (window->isKeyPressed(KB_KEY_UP   )) (*myWorld)[0]->move( 0.0f,  0.1f); // Up arrow
	if (window->isKeyPressed(KB_KEY_RIGHT)) (*myWorld)[0]->move( 0.1f,  0.0f); // Down arrow
	if (window->isKeyPressed(KB_KEY_LEFT )) (*myWorld)[0]->move(-0.1f,  0.0f); // Up arrow

	//DELTAENGINE_INFO("dt: ", deltaTime);

	myWorld->step(1 / 60.0f, 6, 2);
}

void Sandbox::render()
{
	Physics::PhysicsRenderable2D* obj = Utils::toPhysicsRenderable(myWorld->getRenderable(0));

	/*for (int i = 0; i < 4; i++)
	{
		const int c = Utils::cycle(i, 0, 3, 1);
		ui->submit(NEW Graphics::Line(obj->getOBB().getVertex(i).x, obj->getOBB().getVertex(i).y, obj->getOBB().getVertex(c).x, obj->getOBB().getVertex(c).y, 16.0f / 960.0f, i == 0 ? 0xff0000ff : 0xff00ff00));
	}*/

	myWorld->render();
	ui->render();

#ifdef DELTAENGINE_DEBUG
	Debug::checkErrors();
#endif
}

void Sandbox::tick()
{
	//Maths::OBB2D& obb = Utils::toPhysicsRenderable(myWorld->getRenderable(0))->getOBB();
	//DELTAENGINE_TRACE("OBB center: (", obb.getCenter().x, ", ", obb.getCenter().y, ")");
	//DELTAENGINE_TRACE("OBB center: ", obb.getCenter());
	fpsLabel->setText(string("FPS: " + std::to_string(getFPS())));

	memoryLabel->setText(Memory::MemoryManager::getCurrentMemoryString());
	memoryLabel->setPosition(15.8f - memoryLabel->getSize().x, 8.6f);

	DELTAENGINE_INFO("UPS: ", getUPS());
}