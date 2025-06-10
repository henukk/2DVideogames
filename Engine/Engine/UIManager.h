#ifndef _UI_MANAGER_INCLUDE
#define _UI_MANAGER_INCLUDE

#include <vector>
#include <string>
#include <glm/glm.hpp>

struct FloatingText {
    std::string text;
    glm::vec2 position;
    glm::vec2 velocity;
    float lifetime;
    float elapsed;
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

private:
    std::vector<FloatingText> floatingTexts;
};

#endif // _UI_MANAGER_INCLUDE
