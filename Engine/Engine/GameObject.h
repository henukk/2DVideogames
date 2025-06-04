#ifndef _GAME_OBJECT_INCLUDE
#define _GAME_OBJECT_INCLUDE

#include "Sprite.h"

class TileMap;

class GameObject {
public:
    GameObject(TileMap* tilemap);
    virtual ~GameObject();

    virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) = 0;
    virtual void update(int deltaTime) = 0;
    virtual void render();
    virtual void onCollision(GameObject* other);

    virtual void setPosition(const glm::vec2& pos);
    virtual glm::vec2 getPosition() const;
    virtual glm::vec2 getSize() const;

    TileMap* getTileMap() const;

    virtual bool isCollidable() const { return collidable; }
    virtual bool isInteractable() const { return interactable; }

    bool isMarkedForDestruction() const;
    void markForDestruction();

protected:
    glm::vec2 position;
    glm::vec2 size;
    TileMap* map;
    Sprite* sprite = nullptr;
    Texture spritesheet;

    bool collidable = false;
    bool interactable = false;
    bool toBeDestroyed = false;
};

#endif // _GAME_OBJECT_INCLUDE
