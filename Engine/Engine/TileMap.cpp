#include "TileMap.h"
#include "Game.h"
#include "Config.h"
#include "UnbreakableBlock.h"
#include "BreakableBlock.h"
#include <iostream>

using namespace std;

TileMap* TileMap::createTileMap(const string& levelFile, ShaderProgram& program)
{
	return new TileMap(levelFile, program);
}

TileMap::TileMap(const string& levelFile, ShaderProgram& program)
	: shaderProgram(&program),
	staticObjectTree(glm::vec2(0.0f), glm::vec2(SCREEN_X* TILE_SIZE, SCREEN_Y* TILE_SIZE))
{
	loadLevel(levelFile);
}

TileMap::~TileMap() {}

void TileMap::update(int deltaTime) {
	staticObjects.remove_if([this](const std::unique_ptr<StaticObject>& obj) {
		return obj->isMarkedForDestruction();
		});

	for (auto& obj : staticObjects)
		obj->update(deltaTime);

	staticObjectTree = stdExtension::Quadtree<GameObject*, float>(
		glm::vec2(0.0f),
		glm::vec2(SCREEN_X * TILE_SIZE, SCREEN_Y * TILE_SIZE)
	);

	for (const auto& obj : staticObjects) {
		staticObjectTree.insert(obj.get());
	}

	dynamicObjects.remove_if([](const std::unique_ptr<DynamicObject>& obj) {
		return obj->isMarkedForDestruction();
		});

	for (auto& obj : dynamicObjects)
		obj->update(deltaTime);
}


void TileMap::render() const {
	for (auto& obj : staticObjects)
		obj->render();

	for (auto& obj : dynamicObjects)
		obj->render();
}

void TileMap::free() {
	dynamicObjects.clear();
	staticObjects.clear();
}

bool TileMap::loadLevel(const string& levelFile) {
	auto block = std::make_unique<UnbreakableBlock>(
		this,
		UnbreakableBlock::Color::Blue,
		UnbreakableBlock::Length::X3,
		UnbreakableBlock::Type::Vertical
	);
	block->init(glm::vec2(5, SCREEN_Y - 4), *shaderProgram);
	staticObjectTree.insert(block.get());
	staticObjects.push_back(std::move(block));

	auto block2 = std::make_unique<BreakableBlock>(
		this,
		BreakableBlock::Color::Red,
		BreakableBlock::Length::X4,
		BreakableBlock::Type::Horizontal
	);
	block2->init(glm::vec2(1, SCREEN_Y - 5), *shaderProgram);
	staticObjectTree.insert(block2.get());
	staticObjects.push_back(std::move(block2));

	return true;
}

bool TileMap::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size, int* posX) const {
	auto results = staticObjectTree.query(glm::vec2(pos), glm::vec2(size));
	for (auto obj : results) {
		if (obj && obj->isCollidable()) {
			int rightEdge = static_cast<int>(obj->getPosition().x + obj->getSize().x);
			*posX = rightEdge;
			return true;
		}
	}
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size, int* posX) const {
	auto results = staticObjectTree.query(glm::vec2(pos), glm::vec2(size));
	for (auto obj : results) {
		if (obj && obj->isCollidable()) {
			int leftEdge = static_cast<int>(obj->getPosition().x);
			*posX = leftEdge - size.x;
			return true;
		}
	}
	return false;
}


bool TileMap::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const {
	if((pos.y + size.y - 1) >= DOWN_MARGIN * TILE_SIZE) {
		*posY = DOWN_MARGIN * TILE_SIZE - size.y;
		return true;
	}

	auto results = staticObjectTree.query(glm::vec2(pos), glm::vec2(size));
	for (auto obj : results) {
		if (obj && obj->isCollidable()) {
			*posY = static_cast<int>(obj->getPosition().y - size.y);
			return true;
		}
	}
	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const {
	auto results = staticObjectTree.query(glm::vec2(pos), glm::vec2(size));
	for (auto obj : results) {
		if (obj && obj->isCollidable()) {
			*posY = static_cast<int>(obj->getPosition().y + obj->getSize().y);
			return true;
		}
	}
	return false;
}
