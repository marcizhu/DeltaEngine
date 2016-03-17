#pragma once

#include <GLEW\glew.h>
#include <string>

#include <DeltaEngine.h>

using namespace DeltaEngine;

class Sandbox : public DeltaEngine::Game
{
public:
	Sandbox(int argc, char* argv[]);
	~Sandbox();

private:
	Graphics::Shader* shader;
	Graphics::Shader* uiShader;

	Graphics::Label* fpsLabel;
	Graphics::Label* debugLabel;
	Graphics::Label* memoryLabel;

	Graphics::Layer2D* mainLayer;
	Graphics::Layer2D* ui;

	void init() override;
	void update() override;
	void render() override;
	void tick() override;
};