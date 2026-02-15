#include "Button.h"

namespace ui {

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size,
               const std::string& text, const sf::Font& font, sf::Color color)
    : m_text(font),
      m_idleColor(color),
      m_hoverColor(std::min(255, color.r + 30), std::min(255, color.g + 30), std::min(255, color.b + 30)),
      m_activeColor(std::max(0, color.r - 30), std::max(0, color.g - 30), std::max(0, color.b - 30))
{
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_shape.setFillColor(m_idleColor);
    m_shape.setOutlineThickness(1.f);
    m_shape.setOutlineColor(sf::Color::White);

    m_text.setString(text);
    m_text.setCharacterSize(14);
    m_text.setFillColor(sf::Color::White);

    centerText();
}

void Button::centerText() {
    const sf::FloatRect textBounds = m_text.getLocalBounds();
    const sf::Vector2f shapePos = m_shape.getPosition();
    const sf::Vector2f shapeSize = m_shape.getSize();

    m_text.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f
    });

    m_text.setPosition({
        shapePos.x + shapeSize.x / 2.0f,
        shapePos.y + shapeSize.y / 2.0f
    });
}

void Button::setText(const std::string& text) {
    m_text.setString(text);
    centerText();
}

void Button::setBackgroundColor(sf::Color color) {
    m_idleColor = color;
    m_hoverColor = sf::Color(std::min(255, color.r + 30), std::min(255, color.g + 30), std::min(255, color.b + 30));
    m_activeColor = sf::Color(std::max(0, color.r - 30), std::max(0, color.g - 30), std::max(0, color.b - 30));
    if(!m_isPressed && !m_isHovered) m_shape.setFillColor(m_idleColor);
}

void Button::setCallback(std::function<void()> callback) {
    m_callback = std::move(callback);
}

bool Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (const auto* moved = event.getIf<sf::Event::MouseMoved>()) {
        sf::Vector2f mousePos = window.mapPixelToCoords(moved->position);
        bool wasHovered = m_isHovered;
        m_isHovered = m_shape.getGlobalBounds().contains(mousePos);

        if (m_isHovered != wasHovered) {
            if (m_isHovered) m_shape.setFillColor(m_hoverColor);
            else {
                m_shape.setFillColor(m_idleColor);
                m_isPressed = false;
            }
        }
        return m_isHovered;
    }

    if (const auto* pressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (pressed->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(pressed->position);
            if (m_shape.getGlobalBounds().contains(mousePos)) {
                m_isPressed = true;
                m_shape.setFillColor(m_activeColor);
                return true;
            }
        }
    }

    if (const auto* released = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (released->button == sf::Mouse::Button::Left) {
            if (m_isPressed) {
                m_isPressed = false;
                sf::Vector2f mousePos = window.mapPixelToCoords(released->position);
                if (m_shape.getGlobalBounds().contains(mousePos)) {
                    m_shape.setFillColor(m_hoverColor);
                    if (m_callback) m_callback();
                    return true;
                }
                m_shape.setFillColor(m_idleColor);
            }
        }
    }
    return false;
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
    window.draw(m_text);
}

    void ui::Button::setPosition(const sf::Vector2f& pos) {
    m_shape.setPosition(pos);
    const auto textBounds = m_text.getLocalBounds();

    m_text.setOrigin({
        textBounds.position.x + textBounds.size.x / 2.0f,
        textBounds.position.y + textBounds.size.y / 2.0f
    });

    const auto btnBounds = m_shape.getGlobalBounds();

    m_text.setPosition({
        btnBounds.position.x + btnBounds.size.x / 2.0f,
        btnBounds.position.y + btnBounds.size.y / 2.0f
    });
}

}