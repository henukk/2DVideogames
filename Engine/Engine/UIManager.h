#ifndef _UI_MANAGER_INCLUDE
#define _UI_MANAGER_INCLUDE

#include <vector>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include <ft2build.h>
#include FT_FREETYPE_H

struct FloatingText {
    std::string text;
    glm::vec2 position;
    glm::vec2 velocity;
    float lifetime;
    float elapsed;
};

struct Character {
    unsigned int textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

class UIManager {
public:
    static UIManager& instance();

    void init();
    void shutdown();

    void update(int deltaTime);
    void render();

    void createFloatingPoints(const std::string& text, const glm::vec2& position, float duration = 1000.0f);
    void createPoints(int amount, const glm::vec2& position, float duration = 1000.0f);

private:
    UIManager();
    ~UIManager();

    UIManager(const UIManager&) = delete;
    UIManager& operator=(const UIManager&) = delete;

    void loadFont(const std::string& fontPath, unsigned int fontSize);
    void drawText(const std::string& text, glm::vec2 pos);

private:
    std::vector<FloatingText> floatingTexts;
    std::map<char, Character> characters;
    FT_Library ft;
    FT_Face face;
    ShaderProgram textShader;
    unsigned int VAO, VBO;
};

#endif // _UI_MANAGER_INCLUDE
