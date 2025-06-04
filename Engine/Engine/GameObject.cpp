#include <iostream>
#include "GameObject.h"
#include "Config.h"

GameObject::GameObject(TileMap* tilemap) : map(tilemap) {}

GameObject::~GameObject() {
    if (sprite != nullptr)
        delete sprite;
}

void GameObject::render() {
    if (sprite != nullptr)
        sprite->render();
}

void GameObject::onCollision(GameObject* other) {
    // Por defecto, no hace nada
}

void GameObject::setPosition(const glm::vec2& pos) {
    position = pos;
    if (sprite != nullptr)
        sprite->setPosition(position);
}

glm::vec2 GameObject::getPosition() const {
    return position;
}

glm::vec2 GameObject::getSize() const {
    return size;
}

TileMap* GameObject::getTileMap() const {
    return map;
}

bool GameObject::isMarkedForDestruction() const {
    return toBeDestroyed;
}

void GameObject::markForDestruction() {
    toBeDestroyed = true;
}
