#include "UIManager.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Config.h"

UIManager::UIManager() : VAO(0), VBO(0) {}

UIManager::~UIManager() {}

UIManager& UIManager::instance() {
    static UIManager uiManager;
    return uiManager;
}

void UIManager::init() {
    floatingTexts.clear();

    if (FT_Init_FreeType(&ft)) {
        std::cerr << "Failed to init FreeType" << std::endl;
        return;
    }

    loadFont("fonts/arial.ttf", 24);

    Shader vShader, fShader;
    vShader.initFromFile(VERTEX_SHADER, "shaders/text.vert");
    fShader.initFromFile(FRAGMENT_SHADER, "shaders/text.frag");

    textShader.init();
    textShader.addShader(vShader);
    textShader.addShader(fShader);
    textShader.link();
    textShader.bindFragmentOutput("outColor");

    vShader.free();
    fShader.free();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void UIManager::shutdown() {
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void UIManager::loadFont(const std::string& fontPath, unsigned int fontSize) {
    if (FT_New_Face(ft, fontPath.c_str(), 0, &face)) {
        std::cerr << "Failed to load font: " << fontPath << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    characters.clear();
    for (unsigned char c = 0; c < 128; ++c) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) continue;

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        characters[c] = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
        };
    }
}

void UIManager::update(int deltaTime) {
    float dt = float(deltaTime);
    for (auto& ft : floatingTexts) {
        ft.elapsed += dt;
        ft.position += ft.velocity * (dt / 1000.0f);
    }

    floatingTexts.erase(
        std::remove_if(floatingTexts.begin(), floatingTexts.end(), [](const FloatingText& ft) {
            return ft.elapsed >= ft.lifetime;
            }),
        floatingTexts.end()
    );
}

void UIManager::render() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    textShader.use();
    glm::mat4 projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
    textShader.setUniformMatrix4f("projection", projection);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    for (const auto& ft : floatingTexts) {
        drawText(ft.text, ft.position);
    }

    glBindVertexArray(0);
    glDisable(GL_BLEND);
}

void UIManager::drawText(const std::string& text, glm::vec2 pos) {
    float scale = 1.0f;
    for (char c : text) {
        Character ch = characters[c];

        float xpos = pos.x + ch.bearing.x * scale;
        float ypos = pos.y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos,     ypos,       0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos,     ypos + h,   0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 0.0f },
            { xpos + w, ypos + h,   1.0f, 1.0f }
        };

        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        pos.x += (ch.advance >> 6) * scale;
    }
}

void UIManager::createFloatingPoints(const std::string& text, const glm::vec2& position, float duration) {
    FloatingText ft;
    ft.text = text;
    ft.position = position;
    ft.velocity = glm::vec2(0.0f, -30.0f);
    ft.lifetime = duration;
    ft.elapsed = 0.0f;
    floatingTexts.push_back(ft);
}

void UIManager::createPoints(int amount, const glm::vec2& position, float duration) {
    createFloatingPoints("+" + std::to_string(amount), position, duration);
}
