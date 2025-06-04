#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"
#include "Game.h"
#include "Config.h"
#include "UnbreakableBlock.h"
#include "BreakableBlock.h"


using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, program);
	
	return map;
}


TileMap::TileMap(const string &levelFile, ShaderProgram &program)
{
	shaderProgram = &program;
	loadLevel(levelFile);
}

TileMap::~TileMap()
{
	delete[] map;
}

void TileMap::update(int deltaTime) {

	staticObjects.remove_if([this](const std::unique_ptr<StaticObject>& obj) {
		if (obj->isMarkedForDestruction()) {
			removeObject(obj.get(), obj.get()->getTileMapTilePos(), obj.get()->getSize());
			return true;
		}
		return false;
		});

	for (auto& obj : staticObjects)
		obj->update(deltaTime);

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

void TileMap::free()
{
	dynamicObjects.clear();
	staticObjects.clear();

	delete[] map;
	map = nullptr;
}

bool TileMap::loadLevel(const string &levelFile)
{
	map = new GameObject * [SCREEN_X * SCREEN_Y];

	for (int i = 0; i < SCREEN_X * SCREEN_Y; ++i) {
		map[i] = nullptr;
	}

	auto block = std::make_unique<UnbreakableBlock>(
		this,
		UnbreakableBlock::Color::Blue,
		UnbreakableBlock::Length::X3,
		UnbreakableBlock::Type::Vertical
	);
	block->init(glm::vec2(5, SCREEN_Y - 4), *shaderProgram);
	staticObjects.push_back(std::move(block));

	auto block2 = std::make_unique<BreakableBlock>(
		this,
		BreakableBlock::Color::Red,
		BreakableBlock::Length::X4,
		BreakableBlock::Type::Horizontal
	);
	block2->init(glm::vec2(6, SCREEN_Y - 5), *shaderProgram);
	staticObjects.push_back(std::move(block2));

	return true;
}

void TileMap::registerObject(GameObject* obj, const glm::ivec2& tilePos, const glm::ivec2& size) {
	for (int y = 0; y < size.y; ++y) {
		for (int x = 0; x < size.x; ++x) {
			int mapX = tilePos.x + x;
			int mapY = tilePos.y + y;
			if (mapX >= 0 && mapX < SCREEN_X && mapY >= 0 && mapY < SCREEN_Y)
				map[mapY * SCREEN_X + mapX] = obj;
		}
	}
}

void TileMap::removeObject(GameObject* obj, const glm::ivec2& tilePos, const glm::ivec2& size) {
	for (int y = 0; y < size.y; ++y) {
		for (int x = 0; x < size.x; ++x) {
			int mapX = tilePos.x + x;
			int mapY = tilePos.y + y;
			if (mapX >= 0 && mapX < SCREEN_X && mapY >= 0 && mapY < SCREEN_Y) {
				int index = mapY * SCREEN_X + mapX;
				if (map[index] == obj)
					map[index] = nullptr;
			}
		}
	}
}




bool TileMap::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x = pos.x / TILE_SIZE;
	int y0 = pos.y / TILE_SIZE;
	int y1 = (pos.y + size.y - 1) / TILE_SIZE;

	if (x <= LEFT_MARGIN) return true;

	for (int y = y0; y <= y1; ++y)
	{
		int index = y * SCREEN_X + x;
		if (map[index] != nullptr && map[index]->isCollidable())
			return true;
	}
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x = (pos.x + size.x - 1) / TILE_SIZE;
	int y0 = pos.y / TILE_SIZE;
	int y1 = (pos.y + size.y - 1) / TILE_SIZE;

	if (x >= RIGHT_MARGIN) return true;

	for (int y = y0; y <= y1; ++y)
	{
		int index = y * SCREEN_X + x;
		if (map[index] != nullptr && map[index]->isCollidable())
			return true;
	}
	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0 = pos.x / TILE_SIZE;
	int x1 = (pos.x + size.x - 1) / TILE_SIZE;
	int y = (pos.y + size.y - 1) / TILE_SIZE;

	if (y >= DOWN_MARGIN) {
		*posY = DOWN_MARGIN * TILE_SIZE - size.y;
		return true;
	}

	for (int x = x0; x <= x1; ++x)
	{
		int index = y * SCREEN_X + x;
		if (map[index] != nullptr && map[index]->isCollidable())
		{
			if (*posY - TILE_SIZE * y + size.y <= 4)
			{
				*posY = TILE_SIZE * y - size.y;
				return true;
			}
		}
	}
	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0 = pos.x / TILE_SIZE;
	int x1 = (pos.x + size.x - 1) / TILE_SIZE;
	int y = pos.y / TILE_SIZE;

	if (y <= TOP_MARGIN) return true;

	for (int x = x0; x <= x1; ++x)
	{
		int index = y * SCREEN_X + x;
		if (map[index] != nullptr && map[index]->isCollidable())
		{
			if (*posY - TILE_SIZE * y <= 4)
			{
				*posY = TILE_SIZE * (y + 1);
				return true;
			}
		}
	}
	return false;
}



