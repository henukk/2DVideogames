#include <iostream>
#include "Credits.h"
#include "Config.h"
#include "Game.h"
#include "UIManager.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Menu.h"

namespace Scenes {
    Credits::~Credits() {
        delete backgroundSprite;
    }

    void Credits::init() {
        Scene::init();

        initShaders();
        loadBackground();
        projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGTH), 0.f);

        AudioManager::instance().playSound(MUSIC_CREDITS);
    }

    void Credits::update(int deltaTime) {
        if (backgroundSprite) backgroundSprite->update(deltaTime);

        if (Game::instance().getKeyPressed(GLFW_KEY_ESCAPE)) {
            Game::instance().loadNewScene(std::make_unique<Menu>());
        }
    }

    void Credits::render() {
        glm::mat4 modelview(1.0f);

        textureProgram.use();
        textureProgram.setUniformMatrix4f("projection", projection);
        textureProgram.setUniform4f("color", 1.f, 1.f, 1.f, 1.f);
        textureProgram.setUniformMatrix4f("modelview", modelview);
        textureProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

        if (backgroundSprite) backgroundSprite->render();

        glm::vec3 titleColor(0.f, 0.19f, 0.78f);
        glm::vec3 textColor(0.71f, 0.8f, 1.f);

        UIManager::instance().renderText(
            "AUTHOR: ",
            glm::ivec2(5, 3) * TILE_SIZE,
            titleColor,
            2 * TILE_SIZE
        );
        UIManager::instance().renderText(
            "HECTOR N'C'",
            glm::ivec2(8, 4) * TILE_SIZE + glm::ivec2(0, TILE_SIZE/2),
            textColor,
            TILE_SIZE
        );

        UIManager::instance().renderText(
            "ART: ",
            glm::ivec2(5, 6) * TILE_SIZE,
            titleColor,
            2 * TILE_SIZE
        );
        UIManager::instance().renderText(
            "HECTOR N'C'",
            glm::ivec2(8, 7) * TILE_SIZE + glm::ivec2(0, TILE_SIZE / 2),
            textColor,
            TILE_SIZE
        );

        UIManager::instance().renderText(
            "AUDIO: ",
            glm::ivec2(5, 9) * TILE_SIZE,
            titleColor,
            2 * TILE_SIZE
        );
        UIManager::instance().renderText(
            "HECTOR N'C'",
            glm::ivec2(8, 10) * TILE_SIZE + glm::ivec2(0, TILE_SIZE / 2),
            textColor,
            TILE_SIZE
        );


        UIManager::instance().renderText(
            "ESC: RETURN MENU",
            glm::ivec2(SCREEN_WIDTH - (8 * TILE_SIZE), SCREEN_HEIGTH - TILE_SIZE) - glm::ivec2(TILE_SIZE, 0) / 2,
            textColor,
            TILE_SIZE
        );
    }

    void Credits::initShaders() {
        Shader vShader, fShader;

        vShader.initFromFile(VERTEX_SHADER, FILE_VERTEX_SHADER_TEXTURE);
        if (!vShader.isCompiled())
            std::cerr << "Vertex Shader Error:\n" << vShader.log() << "\n";

        fShader.initFromFile(FRAGMENT_SHADER, FILE_FRAGMENT_SHADER_TEXTURE);
        if (!fShader.isCompiled())
            std::cerr << "Fragment Shader Error:\n" << fShader.log() << "\n";

        textureProgram.init();
        textureProgram.addShader(vShader);
        textureProgram.addShader(fShader);
        textureProgram.link();
        if (!textureProgram.isLinked())
            std::cerr << "Shader Linking Error:\n" << textureProgram.log() << "\n";

        textureProgram.bindFragmentOutput("outColor");

        vShader.free();
        fShader.free();

        vShader.initFromFile(VERTEX_SHADER, FILE_VERTEX_SHADER_TEXT);
        if (!vShader.isCompiled())
            std::cerr << "Vertex Shader Error:\n" << vShader.log() << "\n";

        fShader.initFromFile(FRAGMENT_SHADER, FILE_FRAGMENT_SHADER_TEXT);
        if (!fShader.isCompiled())
            std::cerr << "Fragment Shader Error:\n" << fShader.log() << "\n";

        textProgram.init();
        textProgram.addShader(vShader);
        textProgram.addShader(fShader);
        textProgram.link();
        if (!textProgram.isLinked())
            std::cerr << "Shader Linking Error:\n" << textProgram.log() << "\n";

        textProgram.bindFragmentOutput("outColor");

        vShader.free();
        fShader.free();
    }

    void Credits::loadBackground() {
        if (BACKGROUND_CREDITS != nullptr) {
            if (!background.loadFromFile(BACKGROUND_CREDITS, TEXTURE_PIXEL_FORMAT_RGB)) {
                std::cerr << "Error loading background image\n";
                return;
            }

            backgroundSprite = Sprite::createSprite(
                glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGTH),
                glm::vec2(1.f, 1.f),
                &background,
                &textureProgram
            );

            if (backgroundSprite != nullptr)
                backgroundSprite->setPosition(glm::vec2(0.f));
        }
    }
}