#pragma once

#include <GLEW\glew.h>
#include <string>

#include <DeltaEngine.h>

using namespace DeltaEngine;

class Application : public DeltaEngine::Game
{
public:
	Application();
	~Application();

private:
	Graphics::Shader* shader;
	Graphics::Shader* bgShader;

	Graphics::Layer2D* background;
	Graphics::Layer2D* mainLayer;

	std::vector<Graphics::PhysicsRenderable2D*> shots;

	bool keyHeld;

	void init() override;
	void update() override;
	void render() override;
	void tick() override;
};