#include "GameObject.h"

GameObject::GameObject(TileMap* tilemap):map(tilemap) {};

void GameObject::render() {
	if (sprite != nullptr)
		sprite->render();
}

void GameObject::onCollision(GameObject* other) {

}

void GameObject::setPosition(const glm::vec2& pos) {
	position = pos;
	if (sprite != nullptr)
		sprite->setPosition(position);
}

glm::vec2 GameObject::getPosition() const {
	return position;
}

void GameObject::setTileMap(TileMap* tileMap) {
	map = tileMap;
}

TileMap* GameObject::getTileMap() const {
	return map;
}
