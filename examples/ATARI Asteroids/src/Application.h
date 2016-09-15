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
	Graphics::Shader* uiShader;

	Graphics::Layer2D* background;
	Graphics::Layer2D* ui;
	Physics::World2D* world;

	Graphics::Label* score;

	std::vector<Physics::PhysicsRenderable2D*> shots;

	Maths::AABB* playArea;

	bool keyHeld;

	void init() override;
	void update() override;
	void render() override;
	void tick() override;
};