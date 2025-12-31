#include "Button.h"

#include <utility>

Button::Button(const sf::Font& f,
               std::string label,
               const sf::Vector2f pos,
               const sf::Vector2f size)
    : textString(std::move(label)) {

    rect.setPosition(pos);
    rect.setSize(size);

    rect.setFillColor(sf::Color(45, 45, 52));
    rect.setOutlineColor(sf::Color(80, 80, 92));
    rect.setOutlineThickness(2.f);

    text.setFont(f);
    text.setString(textString);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color(230, 230, 235));

    recenterText();
}

void Button::recenterText() {
    const auto r = rect.getGlobalBounds();
    auto b = text.getLocalBounds();

    text.setOrigin(b.left + b.width * 0.5f, b.top + b.height * 0.5f);
    text.setPosition(r.left + r.width * 0.5f, r.top + r.height * 0.5f);
}

void Button::setPosition(const sf::Vector2f pos) {
    rect.setPosition(pos);
    recenterText();
}

void Button::setSize(const sf::Vector2f size) {
    rect.setSize(size);
    recenterText();
}

void Button::setText(std::string s) {
    textString = std::move(s);
    text.setString(textString);
    recenterText();
}

bool Button::hit(const sf::Vector2f mouse) const {
    return rect.getGlobalBounds().contains(mouse);
}

void Button::setEnabled(const bool e) {
    enabled = e;
    if (enabled) {
        rect.setFillColor(sf::Color(45, 45, 52));
        rect.setOutlineColor(sf::Color(80, 80, 92));
        text.setFillColor(sf::Color(230, 230, 235));
    } else {
        rect.setFillColor(sf::Color(30, 30, 34));
        rect.setOutlineColor(sf::Color(55, 55, 62));
        text.setFillColor(sf::Color(140, 140, 150));
    }
}

bool Button::isEnabled() const {
    return enabled;
}

void Button::draw(sf::RenderTarget& target) const {
    target.draw(rect);
    target.draw(text);
}
