#ifndef OOP_UI_H
#define OOP_UI_H

#include <vector>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Button.h"

namespace ui {

    class UIManager {
    public:
        void addButton(sf::Vector2f position, sf::Vector2f size, const std::string& text, const sf::Font& font, const std::function<void()> &callback, sf::Color color);


        void handleEvents(const sf::Event& event, const sf::RenderWindow& window) const;
        void draw(sf::RenderWindow& window) const;

    private:
        std::vector<std::unique_ptr<Button>> m_buttons;
    };

}

#endif //OOP_UI_H