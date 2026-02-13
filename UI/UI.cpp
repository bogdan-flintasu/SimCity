#include "UI.h"


namespace ui {
    void UIManager::addButton(sf::Vector2f position, sf::Vector2f size, const std::string& text, const sf::Font& font, const std::function<void()> &callback, sf::Color color) {
        m_buttons.push_back(std::make_unique<Button>(position, size, text, font, color));
        m_buttons.back()->setCallback(callback);
    }

    void UIManager::handleEvents(const sf::Event& event, const sf::RenderWindow& window) const {
        for (const auto& btn : m_buttons) {
            if (btn->handleEvent(event, window)) return;
        }
    }

    void UIManager::draw(sf::RenderWindow& window) const {
        for (const auto& btn : m_buttons) {
            btn->draw(window);
        }
    }
}