#include <cmath>
#include "Player.h"
#include "Game.h"
#include "Config.h"
#include "TileMap.h"

Player::Player(TileMap* tileMap) : DynamicObject(tileMap), bJumping(false), jumpAngle(0), startY(0) {
    collidable = true;
}

void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram) {
    position = glm::vec2(tileMapPos * TILE_SIZE);
    size = glm::vec2(PLAYER_WIDTH, PLAYER_HEIGTH);

    spritesheet.loadFromFile("images/bub.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(PLAYER_WIDTH, PLAYER_HEIGTH), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(4);

    sprite->setAnimationSpeed(STAND_LEFT, 8);
    sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));

    sprite->setAnimationSpeed(STAND_RIGHT, 8);
    sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));

    sprite->setAnimationSpeed(MOVE_LEFT, 8);
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
    sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.5f));

    sprite->setAnimationSpeed(MOVE_RIGHT, 8);
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.25f));
    sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.5f));

    sprite->changeAnimation(STAND_RIGHT);
    sprite->setPosition(position);
}

void Player::update(int deltaTime) {
    sprite->update(deltaTime);

    glm::ivec2 iPos = glm::ivec2(position);

    if (Game::instance().getKey(GLFW_KEY_LEFT)) {
        if (sprite->animation() != MOVE_LEFT)
            sprite->changeAnimation(MOVE_LEFT);
        position.x -= 2;
        if (map->collisionMoveLeft(iPos, glm::ivec2(PLAYER_WIDTH, PLAYER_HEIGTH))) {
            position.x += 2;
            sprite->changeAnimation(STAND_LEFT);
        }
    }
    else if (Game::instance().getKey(GLFW_KEY_RIGHT)) {
        if (sprite->animation() != MOVE_RIGHT)
            sprite->changeAnimation(MOVE_RIGHT);
        position.x += 2;
        if (map->collisionMoveRight(iPos, glm::ivec2(PLAYER_WIDTH, PLAYER_HEIGTH))) {
            position.x -= 2;
            sprite->changeAnimation(STAND_RIGHT);
        }
    }
    else {
        if (sprite->animation() == MOVE_LEFT)
            sprite->changeAnimation(STAND_LEFT);
        else if (sprite->animation() == MOVE_RIGHT)
            sprite->changeAnimation(STAND_RIGHT);
    }

    if (bJumping) {
        jumpAngle += JUMP_ANGLE_STEP;
        if (jumpAngle >= 180) {
            bJumping = false;
            position.y = float(startY);
        }
        else {
            position.y = float(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
            if (jumpAngle > 90) {
                int newY;
                if (map->collisionMoveDown(glm::ivec2(position), glm::ivec2(PLAYER_WIDTH, PLAYER_HEIGTH), &newY)) {
                    position.y = float(newY);
                    bJumping = false;
                }
            }
        }
    }
    else {
        position.y += FALL_STEP;
        int newY;
        if (map->collisionMoveDown(glm::ivec2(position), glm::ivec2(PLAYER_WIDTH, PLAYER_HEIGTH), &newY)) {
            position.y = float(newY);
            if (Game::instance().getKey(GLFW_KEY_UP)) {
                bJumping = true;
                jumpAngle = 0;
                startY = int(position.y);
            }
        }
    }

    sprite->setPosition(position);
}
