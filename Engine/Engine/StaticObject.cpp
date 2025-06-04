#include "StaticObject.h"
#include "TileMap.h"
#include "Config.h"

StaticObject::StaticObject(TileMap* tilemap) : GameObject(tilemap) {
    collidable = true;
}

void StaticObject::init(const glm::ivec2& tileMapPos, const glm::ivec2& sizeInTiles, ShaderProgram& shaderProgram) {
    tileMapTilePos = tileMapPos;
    position = glm::vec2(tileMapPos * TILE_SIZE);
    size = glm::vec2(sizeInTiles);  // Tamaño en tiles

    if (map)
        map->registerObject(this, tileMapPos, sizeInTiles);
}


glm::ivec2 StaticObject::getTileMapTilePos() {
    return tileMapTilePos;
}
