#pragma once

#include <GLEW\glew.h>
#include <string>

#include <DeltaEngine.h>

using namespace DeltaEngine;

class Sandbox : public DeltaEngine::Game
{
public:
	Sandbox();
	~Sandbox();

private:
	Graphics::Shader* shader;
	Graphics::Shader* uiShader;

	Graphics::Label* fpsLabel;
	Graphics::Label* debugLabel;
	Graphics::Label* memoryLabel;

	Graphics::Layer2D* ui;

	Physics::World2D* myWorld;

	Sound::Playlist* myList;

	void init() override;
	void update(float deltaTime) override;
	void render() override;
	void tick() override;
};