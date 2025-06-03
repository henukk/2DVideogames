#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE

#include <string>
#include <memory>
#include <list>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "GameObject.h"

class TileMap
{

private:
	TileMap(const std::string &levelFile, ShaderProgram &program);

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const std::string &levelFile, ShaderProgram &program);

	~TileMap();
	
	void update(int deltaTime);
	void render() const;
	void free();

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const;
	
private:
	bool loadLevel(const std::string &levelFile);

private:
	std::list<std::unique_ptr<GameObject>> entities;
	GameObject** map;

	ShaderProgram* shaderProgram;

};


#endif // _TILE_MAP_INCLUDE


