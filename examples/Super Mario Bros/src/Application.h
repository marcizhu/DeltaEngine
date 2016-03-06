#pragma once

#include <GLEW\glew.h>
#include <string>

#include <DeltaEngine.h>

using namespace DeltaEngine;

class Application : public DeltaEngine::Game
{
public:
	Application(int argc, char* argv[]);
	~Application();

private:
	Graphics::Shader* shader;
	//Graphics::Shader* uiShader;

	Graphics::Layer2D* mainLayer;
	//Graphics::Layer2D* ui;

	void init() override;
	void update() override;
	void render() override;
	void tick() override;
};