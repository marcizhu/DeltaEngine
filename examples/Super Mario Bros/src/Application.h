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

	Physics::World2D* world;
	Graphics::Layer2D* mainLayer;

	bool jumping = false;
	bool left = false;
	bool right = false;

	void init() override;
	void update(float deltaTime) override;
	void render() override;
	void tick() override;
};