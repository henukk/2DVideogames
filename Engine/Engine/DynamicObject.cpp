#include "DynamicObject.h"
#include "TileMap.h"

DynamicObject::DynamicObject(TileMap* tilemap) : GameObject(tilemap) {
    // Generalmente, los objetos dinámicos son colisionables por defecto
    collidable = true;
}

void DynamicObject::move(const glm::vec2& delta) {
    setPosition(position + delta);
}

void DynamicObject::checkCollisions() {
    // Método vacío por ahora. Se sobreescribe o se implementa lógica específica en subclases (ej: Player, Ball)
}
