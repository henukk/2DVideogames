#include <iostream>
#include "Menu.h"
#include "Config.h"

namespace Scenes {
    Menu::~Menu() {
        delete backgroundSprite;
        delete banner;
    }

    void Menu::init() {
        Scene::init();

        initShaders();
        loadBackground();


        /*
        if (!spritesheet.isLoaded()) {
            spritesheet.loadFromFile(SPRITES_IMAGE, TEXTURE_PIXEL_FORMAT_RGBA);
        }
        int row = 0;
        float texX = 0.f;
        float texY = float(row) / float(SPRITE_SIZE);

        banner = Sprite::createSprite(
            glm::ivec2(2, 2) * TILE_SIZE,
            glm::vec2(float(2) / SPRITE_SIZE, float(2) / SPRITE_SIZE),
            &spritesheet, &textureProgram
        );
        banner->setTexCoordDispl(glm::vec2(texX, texY));
        banner->setPosition(position);
        */

        AudioManager::instance().playSound(MUSIC_MENU);
    }

    void Menu::update(int deltaTime) {
        if (backgroundSprite) backgroundSprite->update(deltaTime);
    }

    void Menu::render() {
        if (backgroundSprite) backgroundSprite->render();
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

}