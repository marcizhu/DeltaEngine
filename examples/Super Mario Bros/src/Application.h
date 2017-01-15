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

	Physics::World2D* world;

	void init() override;
	void update(float deltaTime) override;
	void render() override;
	void tick() override;
};