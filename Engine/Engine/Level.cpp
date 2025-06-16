#include "Level.h"
#include "Game.h"
#include "Config.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void Level::init() {
    Scene::init();
}

Level::~Level() {
    delete map;
    delete player;
    delete backgroundSprite;
}

void Level::update(int deltaTime) {
    currentTime += deltaTime;
    if (backgroundSprite)
        backgroundSprite->update(deltaTime);
    if (map)
        map->update(deltaTime);
    if (player)
        player->update(deltaTime);

    UIManager::instance().update(deltaTime);
}

void Level::render() {
    glm::mat4 modelview(1.0f);

    texProgram.use();
    texProgram.setUniformMatrix4f("projection", projection);
    texProgram.setUniform4f("color", 1.f, 1.f, 1.f, 1.f);
    texProgram.setUniformMatrix4f("modelview", modelview);
    texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

    if (backgroundSprite) backgroundSprite->render();
    if (map) map->render();
    if (player) player->render();

    UIManager::instance().render();
}

void Level::initShaders() {
    Shader vShader, fShader;

    vShader.initFromFile(VERTEX_SHADER, FILE_VERTEX_SHADER_TEXTURE);
    if (!vShader.isCompiled())
        std::cerr << "Vertex Shader Error:\n" << vShader.log() << "\n";

    fShader.initFromFile(FRAGMENT_SHADER, FILE_FRAGMENT_SHADER_TEXTURE);
    if (!fShader.isCompiled())
        std::cerr << "Fragment Shader Error:\n" << fShader.log() << "\n";

    texProgram.init();
    texProgram.addShader(vShader);
    texProgram.addShader(fShader);
    texProgram.link();
    if (!texProgram.isLinked())
        std::cerr << "Shader Linking Error:\n" << texProgram.log() << "\n";

    texProgram.bindFragmentOutput("outColor");

    vShader.free();
    fShader.free();
}

void Level::loadBackground() {
    if (BACKGROUND != nullptr) {
        if (!spritesheet.loadFromFile(BACKGROUND, TEXTURE_PIXEL_FORMAT_RGB))
            std::cerr << "Error loading background image\n";

        backgroundSprite = Sprite::createSprite(
            glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT),
            glm::vec2(1, 1),
            &spritesheet,
            &texProgram
        );
        backgroundSprite->setPosition(glm::vec2(0.f));
    }
}
