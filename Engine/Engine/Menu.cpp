#include <iostream>
#include "Menu.h"
#include "Config.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Scenes {
    Menu::~Menu() {
        delete backgroundSprite;
        delete bannerSprite;
    }

    void Menu::init() {
        Scene::init();

        initShaders();
        loadBackground();
        loadLogo();
        projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);

        AudioManager::instance().playSound(MUSIC_MENU);
    }

    void Menu::update(int deltaTime) {
        if (backgroundSprite) backgroundSprite->update(deltaTime);
        if (bannerSprite) bannerSprite->update(deltaTime);
    }

    void Menu::render() {
        glm::mat4 modelview(1.0f);

        textureProgram.use();
        textureProgram.setUniformMatrix4f("projection", projection);
        textureProgram.setUniform4f("color", 1.f, 1.f, 1.f, 1.f);
        textureProgram.setUniformMatrix4f("modelview", modelview);
        textureProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

        if (backgroundSprite) backgroundSprite->render();
        if (bannerSprite) bannerSprite->render();
    }

    void Menu::initShaders() {
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

    void Menu::loadBackground() {
        if (BACKGROUND_MENU != nullptr) {
            if (!background.loadFromFile(BACKGROUND_MENU, TEXTURE_PIXEL_FORMAT_RGB)) {
                std::cerr << "Error loading background image\n";
                return;
            }

            backgroundSprite = Sprite::createSprite(
                glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT),
                glm::vec2(1.f, 1.f),
                &background,
                &textureProgram
            );

            if (backgroundSprite != nullptr)
                backgroundSprite->setPosition(glm::vec2(0.f));
        }
    }

    void Menu::loadLogo() {
        if (MENU_BANNER != nullptr) {
            if (!banner.loadFromFile(MENU_BANNER, TEXTURE_PIXEL_FORMAT_RGBA)) {
                std::cerr << "Error loading banner image\n";
                return;
            }

            bannerSprite = Sprite::createSprite(
                glm::ivec2(SCREEN_WIDTH/2, SCREEN_WIDTH/2 * 0.6119f),
                glm::vec2(1.f, 1.f),
                &banner,
                &textureProgram
            );

            if (bannerSprite != nullptr)
                bannerSprite->setPosition(glm::vec2(SCREEN_WIDTH / 4, TILE_SIZE));
        }
    }
}