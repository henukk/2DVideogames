#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE

#include <string>
#include <memory>
#include <list>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include "Quadtree.h"

class TileMap
{
private:
	TileMap(const std::string& levelFile, ShaderProgram& program);

public:
	static TileMap* createTileMap(const std::string& levelFile, ShaderProgram& program);

	~TileMap();

	void update(int deltaTime);
	void render() const;
	void free();

	bool collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size, int* posX) const;
	bool collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size, int* posX) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;

private:
	bool loadLevel(const std::string& levelFile);

private:
	std::list<std::unique_ptr<DynamicObject>> dynamicObjects;
	std::list<std::unique_ptr<StaticObject>> staticObjects;
	stdExtension::Quadtree<GameObject*, float> staticObjectTree;
	ShaderProgram* shaderProgram;
};

#endif // _TILE_MAP_INCLUDE