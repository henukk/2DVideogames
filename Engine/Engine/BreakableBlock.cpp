#include "BreakableBlock.h"
#include "Config.h"

Texture BreakableBlock::spritesheet;

BreakableBlock::BreakableBlock(TileMap* tilemap, Color color, Length length, Type type)
    : StaticObject(tilemap), color(color), length(length), type(type) {
}

void BreakableBlock::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
    int sizeX = 1, sizeY = 1;

    switch (length) {
    case Length::X1: sizeX = 1; break;
    case Length::X2: sizeX = 2; break;
    case Length::X3: sizeX = 3; break;
    case Length::X4: sizeX = 4; break;
    }

    if (type == Type::Vertical && length != Length::X1)
        std::swap(sizeX, sizeY);

    size = glm::vec2(sizeX, sizeY);

    StaticObject::init(tileMapPos, glm::ivec2(sizeX, sizeY), shaderProgram);

    if (!spritesheet.isLoaded()) {
        spritesheet.loadFromFile(SPRITES_IMAGE, TEXTURE_PIXEL_FORMAT_RGBA);
    }

    int row = getSpriteRow(color, length, type);

    float texX = 0.f;
    float texY = float(row) / float(SPRITE_SIZE);

    sprite = Sprite::createSprite(
        glm::ivec2(sizeX, sizeY) * TILE_SIZE,
        glm::vec2(float(sizeX) / SPRITE_SIZE, float(sizeY) / SPRITE_SIZE),
        &spritesheet, &shaderProgram
    );
    sprite->setTexCoordDispl(glm::vec2(texX, texY));
    sprite->setPosition(position);

    collidable = true;
    interactable = false;
}



int BreakableBlock::getSpriteRow(BreakableBlock::Color color, BreakableBlock::Length length, BreakableBlock::Type type) {
    int base = 0;
    switch (color) {
    case BreakableBlock::Color::Blue: base = 0; break;
    case BreakableBlock::Color::Red: base = 11; break;
    case BreakableBlock::Color::Yellow: base = 22; break;
    }

    if (length == BreakableBlock::Length::X1)
        return base;

    if (type == BreakableBlock::Type::Vertical) {
        if (length == BreakableBlock::Length::X3) return base + 1;
        if (length == BreakableBlock::Length::X4) return base + 4;
    }
    else {
        if (length == BreakableBlock::Length::X2) return base + 8;
        if (length == BreakableBlock::Length::X3) return base + 9;
        if (length == BreakableBlock::Length::X4) return base + 10;
    }

    return base;
}

void BreakableBlock::update(int deltaTime) {
    if (sprite != nullptr) sprite->update(deltaTime);
}

void BreakableBlock::onCollision(GameObject* other) {
    // comportamiento por defecto (nada)
}
