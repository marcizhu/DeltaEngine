#include <Windows.h>

#include "Sandbox.h"

Sandbox::Sandbox(int argc, char* argv[]) : Game()
{
	this->createWindow("DeltaEngine Sandbox", 960, 540);
	int init = DeltaEngine::init(argc, argv);
	DELTAENGINE_ASSERT(init != DELTAENGINE_NOT_INITIALIZED, "DELTAENGINE NOT INITIALIZED!");
}

Sandbox::~Sandbox()
{
	delete mainLayer;
	delete ui;

	Graphics::FontManager::clean();
	Graphics::TextureManager::clean();
}

void Sandbox::init()
{
	SetConsoleTitle(TEXT("DeltaEngine Debug Output"));

	Maths::Matrix4 pr_matrix = Maths::Matrix4::orthographic(0.0f, 16.0f, 9.0f, 0.0f, -1.0f, 1.0f);

	shader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\basic.shader");
	uiShader = Graphics::Shader::loadFromFile(Utils::getCurrentPath() + "\\basic.shader");

	Graphics::TextureManager::add(NEW Graphics::Texture("Mario", "mario.png", GL_NEAREST));

	mainLayer = NEW Graphics::Layer2D(NEW Graphics::BatchRenderer2D(), shader, pr_matrix);
	mainLayer->add(NEW Graphics::BatchRenderable2D(1.0f, 1.0f, 1, 1, Graphics::TextureManager::get("Mario")));
	mainLayer->add(NEW Graphics::Line(4.0f, 1.0f, 12.0f, 1.0f, 16.0f / 960.0f * 30, 0x3FFFFFFF));

	for (int y = 0; y < 20; y++)
	{
		if (y == 0)
			mainLayer->add(NEW Graphics::Line(0.0f, y, 20.0f, y, 16.0f / 960.0f, 0xFF0000FF));
		else
			mainLayer->add(NEW Graphics::Line(0.0f, y, 20.0f, y, 16.0f / 960.0f, 0x3FFFFFFF));
	}

	for (int x = 0; x < 20; x++)
	{
		if (x == 0)
			mainLayer->add(NEW Graphics::Line(x, 0.0f, x, 20.0f, 16.0f / 960.0f, 0xFF0000FF));
		else
			mainLayer->add(NEW Graphics::Line(x, 0.0f, x, 20.0f, 16.0f / 960.0f, 0x3FFFFFFF));
	}

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

	window->setVSync(true);
}

void Sandbox::update()
{
	Graphics::FontManager::get("OpenSans")->setScale(window->getHeight() / 9.0f, window->getWidth() / 16.0f);
	Graphics::FontManager::get("Consolas")->setScale(window->getHeight() / 9.0f, window->getWidth() / 16.0f);

	if (window->isKeyPressed(KB_KEY_ESCAPE)) window->close();

	if (window->isKeyPressed(KB_KEY_RIGHT)) mainLayer->getRenderables()[0]->move( 0.1f,  0.0f); // Right arrow
	if (window->isKeyPressed(KB_KEY_LEFT)) mainLayer->getRenderables()[0]->move(-0.1f,  0.0f); // Left arrow
	if (window->isKeyPressed(KB_KEY_DOWN)) mainLayer->getRenderables()[0]->move( 0.0f, -0.1f); // Down arrow
	if (window->isKeyPressed(KB_KEY_UP)) mainLayer->getRenderables()[0]->move( 0.0f,  0.1f); // Up arrow
}

void Sandbox::render()
{
	//TODO: Individual rotation (for physics)
	/*Maths::Matrix4 m = Maths::Matrix4::identity();
	m.rotate(-30, 0, 0, 1);
	shader->enable();
	shader->setUniformMat4("ml_matrix", m);
	shader->disable();

	uiShader->enable();
	uiShader->setUniformMat4("ml_matrix", m);
	uiShader->disable();*/

	mainLayer->render();
	ui->render();

#ifdef _DEBUG
	Debug::checkErrors();
#endif
}

void Sandbox::tick()
{
	fpsLabel->setText(string("FPS: " + std::to_string(getFPS())));

	float mb = (float)Internal::MemoryInfo::getCurrentMemory() / (1024);
	memoryLabel->setText(string("Allocated memory: " + Utils::precision_to_string(mb, 3) + " Kb"));

	//DELTAENGINE_INFO("Total memory: ", Internal::MemoryInfo::getCurrentMemory());
}