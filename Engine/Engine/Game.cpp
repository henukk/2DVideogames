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
	std::fill(std::begin(keys), std::end(keys), false);
	std::fill(std::begin(pressedQuerries), std::end(pressedQuerries), false);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	mousePos = glm::ivec2(0, 0);
	
	UIManager::instance().init();
	AudioManager::instance().init();

	scene = std::make_unique<Scenes::Menu>();
	scene->init();
}

void Game::exitGame() {
	bPlay = false;
}

void Game::loadNewScene(std::unique_ptr<Scene> newScene) {
	std::fill(std::begin(keys), std::end(keys), false);
	std::fill(std::begin(pressedQuerries), std::end(pressedQuerries), false);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//UIManager::instance().init();

	AudioManager::instance().shutdown();
	AudioManager::instance().init();


	scene = std::move(newScene);
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
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
	pressedQuerries[key] = false;
}

void Game::mouseMove(int x, int y) {
	mousePos = glm::ivec2(x, y);
}

void Game::mousePress(int button) {
	if (button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST)
		mouseKeys[button] = true;
}

void Game::mouseRelease(int button) {
	if (button >= 0 && button <= GLFW_MOUSE_BUTTON_LAST) {
		mouseKeys[button] = false;
		mousePressedQuerries[button] = false;
	}
}

bool Game::getKey(int key) const {
	return keys[key];
}

bool Game::getKeyPressed(int key) {
	if (keys[key] && !pressedQuerries[key]) {
		pressedQuerries[key] = true;
		return true;
	}
	return false;
}

bool Game::getMouse(int key) const {
	return mouseKeys[key];
}

bool Game::getMousePressed(int key) {
	if (mouseKeys[key] && !mousePressedQuerries[key]) {
		mousePressedQuerries[key] = true;
		return true;
	}
	return false;
}

glm::ivec2 Game::getMousePos() const {
	return mousePos;
}

