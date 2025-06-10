#include "UIManager.h"
#include <iostream>
#include <algorithm>

UIManager::UIManager() {}

UIManager::~UIManager() {}

UIManager& UIManager::instance() {
    static UIManager uiManager;
    return uiManager;
}

void UIManager::init() {
    floatingTexts.clear();
}

void UIManager::shutdown() {
    floatingTexts.clear();
}

void UIManager::update(int deltaTime) {
    float dt = float(deltaTime);

    for (auto& ft : floatingTexts) {
        ft.elapsed += dt;
        ft.position += ft.velocity * (dt / 1000.0f); // Movimiento suave en segundos
    }

    floatingTexts.erase(
        std::remove_if(floatingTexts.begin(), floatingTexts.end(), [](const FloatingText& ft) {
            return ft.elapsed >= ft.lifetime;
            }),
        floatingTexts.end()
    );
}

void UIManager::render() {
    for (const auto& ft : floatingTexts) {
        // Aquí deberías llamar a tu sistema de renderizado de texto (usando FreeType u otro)
        // drawText(ft.text, ft.position);
    }
}

void UIManager::createFloatingPoints(const std::string& text, const glm::vec2& position, float duration) {
    FloatingText ft;
    ft.text = text;
    ft.position = position;
    ft.velocity = glm::vec2(0.0f, -30.0f); // Hacia arriba (30 px/segundo)
    ft.lifetime = duration;
    ft.elapsed = 0.0f;
    floatingTexts.push_back(ft);
}

void UIManager::createPoints(int amount, const glm::vec2& position, float duration) {
    createFloatingPoints("+" + std::to_string(amount), position, duration);
}
