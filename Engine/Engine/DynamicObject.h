#ifndef _DYNAMIC_OBJECT_INCLUDE
#define _DYNAMIC_OBJECT_INCLUDE

#include "GameObject.h"

class DynamicObject : public GameObject {
public:
    DynamicObject(TileMap* tilemap);
    ~DynamicObject() override = default;

    virtual void move(const glm::vec2& delta);
    virtual void checkCollisions();
};

#endif // _DYNAMIC_OBJECT_INCLUDE
