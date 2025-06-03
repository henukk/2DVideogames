#ifndef _GAME_OBJECT_INCLUDE
#define _GAME_OBJECT_INCLUDE

#include "Sprite.h"

class TileMap;

class GameObject {
public:
	virtual ~GameObject() {
		if (sprite != NULL)
			delete sprite;
	}

	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
	virtual void update(int deltaTime) = 0;
	virtual void render();

	virtual void onCollision(GameObject* other);

	virtual void setPosition(const glm::vec2& pos);
	virtual glm::vec2 getPosition() const;

	void setTileMap(TileMap* tileMap);
	TileMap* getTileMap() const;

	virtual bool isCollidable() const { return collidable; }
	virtual bool isInteractable() const { return interactable; }

protected:
	glm::vec2 position;
	TileMap* map;
	Sprite* sprite;
	Texture spritesheet;

	bool collidable = false;
	bool interactable = false;
};

#endif // _GAME_OBJECT_INCLUDE
