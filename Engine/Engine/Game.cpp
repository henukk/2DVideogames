#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
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
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	
	AudioManager::instance().init();

	scene = std::make_unique<Level1>();
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
	AudioManager::instance().shutdown();
}

void Game::keyPressed(int key)
{
	if(key == GLFW_KEY_ESCAPE) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::mouseMove(int x, int y)
{
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



