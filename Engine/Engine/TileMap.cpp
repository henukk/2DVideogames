#include "TileMap.h"
#include "Game.h"
#include "Config.h"
#include "UnbreakableBlock.h"
#include "BreakableBlock.h"
#include <iostream>

using namespace std;

TileMap* TileMap::createTileMap(const LevelData& data, ShaderProgram& program)
{
	return new TileMap(data, program);
}

TileMap::TileMap(const LevelData& data, ShaderProgram& program)
	: shaderProgram(&program),
	staticObjectTree(glm::vec2(0.0f), glm::vec2(GAME_WIDTH, GAME_WIDTH))
{
	loadLevel(data);
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
		glm::vec2(GAME_WIDTH, GAME_WIDTH)
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

bool TileMap::loadLevel(const LevelData& data) {
	for (const auto& tile : data.getTiles()) {
		if (tile.type == TileEntry::TileType::Unbreakable) {
			auto block = std::make_unique<UnbreakableBlock>(
				this,
				static_cast<UnbreakableBlock::Color>(static_cast<int>(tile.color)),
				static_cast<UnbreakableBlock::Length>(static_cast<int>(tile.length)),
				static_cast<UnbreakableBlock::Type>(static_cast<int>(tile.orientation))
			);
			block->init(tile.position, *shaderProgram);
			staticObjectTree.insert(block.get());
			staticObjects.push_back(std::move(block));
		}
		else if (tile.type == TileEntry::TileType::Breakable) {
			auto block = std::make_unique<BreakableBlock>(
				this,
				static_cast<BreakableBlock::Color>(static_cast<int>(tile.color)),
				static_cast<BreakableBlock::Length>(static_cast<int>(tile.length)),
				static_cast<BreakableBlock::Type>(static_cast<int>(tile.orientation))
			);
			block->init(tile.position, *shaderProgram);
			staticObjectTree.insert(block.get());
			staticObjects.push_back(std::move(block));
		}
	}
	return true;
}

bool TileMap::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size, int* posX) const {
	if ((pos.x) <= LEFT_MARGIN * TILE_SIZE) {
		*posX = LEFT_MARGIN * TILE_SIZE;
		return true;
	}

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
	if ((pos.x + size.x - 1) >= RIGHT_MARGIN * TILE_SIZE) {
		*posX = RIGHT_MARGIN * TILE_SIZE - size.x;
		return true;
	}

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
