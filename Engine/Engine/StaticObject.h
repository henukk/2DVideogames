#ifndef _STATIC_OBJECT_INCLUDE
#define _STATIC_OBJECT_INCLUDE

#include "GameObject.h"

class StaticObject : public GameObject {
public:
    StaticObject(TileMap* tilemap);
    ~StaticObject() override = default;

    void init(const glm::ivec2& tileMapPos, const glm::ivec2& size, ShaderProgram& shaderProgram);

    glm::ivec2 getTileMapTilePos();
    
private:
    glm::ivec2 tileMapTilePos;

};

#endif // _STATIC_OBJECT_INCLUDE