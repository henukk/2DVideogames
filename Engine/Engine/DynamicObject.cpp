#include "DynamicObject.h"
#include "TileMap.h"

DynamicObject::DynamicObject(TileMap* tilemap) : GameObject(tilemap) {
    // Generalmente, los objetos din�micos son colisionables por defecto
    collidable = true;
}

void DynamicObject::move(const glm::vec2& delta) {
    setPosition(position + delta);
}

void DynamicObject::checkCollisions() {
    // M�todo vac�o por ahora. Se sobreescribe o se implementa l�gica espec�fica en subclases (ej: Player, Ball)
}
