#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"
#include "Game.h"
#include "Config.h"
#include "UnbreakableBlock.h"


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
	if(map != NULL)
		delete map;
}


void TileMap::update(int deltaTime) {
	for (auto& e : entities)
		e->update(deltaTime);
}

void TileMap::render() const {
	for (auto& e : entities)
		e->render();
}

void TileMap::free()
{
	for (auto& obj : entities)
		delete obj;
	entities.clear();

	delete[] map;
	map = nullptr;
}

bool TileMap::loadLevel(const string &levelFile)
{
	map = new GameObject * [SCREEN_X * SCREEN_Y];

	for (int i = 0; i < SCREEN_X * SCREEN_Y; ++i) {
		map[i] = nullptr;
	}

	UnbreakableBlock *block = new UnbreakableBlock();
	block->init(glm::vec2(5, SCREEN_Y-5), *shaderProgram);

	map[5 + ((SCREEN_Y - 5) * SCREEN_X)] = block;
	map[5 + ((SCREEN_Y - 4) * SCREEN_X)] = block;
	map[5 + ((SCREEN_Y - 3) * SCREEN_X)] = block;
	map[5 + ((SCREEN_Y - 2) * SCREEN_X)] = block;
	entities.push_back(block);


	return true;
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



