#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "UIManager.h"
#include "Menu.h"
#include "Level1.h"

Game::Game()
{
	bPlay = true;
}

Game& Game::instance()
{
	static Game G;
	return G;
}

void Game::init()
{
	bPlay = true;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	mousePos = glm::ivec2(0, 0);
	
	UIManager::instance().init();
	AudioManager::instance().init();

	scene = std::make_unique<Scenes::Menu>();
	scene->init();
}

bool Game::update(int deltaTime)
{
	scene->update(deltaTime);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene->render();
}

void Game::shutdown()
{
	UIManager::instance().shutdown();
	AudioManager::instance().shutdown();
}

void Game::keyPressed(int key)
{
	if(key == GLFW_KEY_ESCAPE)
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::mouseMove(int x, int y) {
	mousePos = glm::ivec2(x, y);
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

glm::ivec2 Game::getMousePos() const {
	return mousePos;
}

