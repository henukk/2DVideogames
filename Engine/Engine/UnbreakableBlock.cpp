#include "UnbreakableBlock.h"
#include "Config.h"

void UnbreakableBlock::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
	map = nullptr;
	position = glm::vec2(tileMapPos*TILE_SIZE);
	spritesheet.loadFromFile(SPRITES_IMAGE, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(TILE_SIZE, TILE_SIZE*4), glm::vec2(1.f/SPRITE_SIZE, 4.f/SPRITE_SIZE), &spritesheet, &shaderProgram);
	sprite->setPosition(position);

	collidable = true;
	interactable = false;
}

void UnbreakableBlock::update(int deltaTime) {
	if (sprite != nullptr)
		sprite->update(deltaTime);
}

void UnbreakableBlock::onCollision(GameObject* other) {

}
