#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

namespace ui {

    class Button {
    public:
        Button(const sf::Vector2f& position, const sf::Vector2f& size,
            const std::string& text,const sf::Font& font, sf::Color color);

        bool handleEvent(const sf::Event& event, const sf::RenderWindow& window);
        void draw(sf::RenderWindow& window) const;

        void setText(const std::string& text);
        void setBackgroundColor(sf::Color color);
        void setPosition(const sf::Vector2f& pos);

        void setCallback(std::function<void()> callback);

    private:
        sf::RectangleShape m_shape;
        sf::Text m_text;
        sf::Color m_idleColor;
        sf::Color m_hoverColor;
        sf::Color m_activeColor;

        std::function<void()> m_callback;

        bool m_isHovered = false;
        bool m_isPressed = false;

        void centerText();
    };

}

#endif //OOP_BUTTON_H