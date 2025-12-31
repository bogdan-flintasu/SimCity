#include "TextInput.h"

TextInput::TextInput(const sf::Font& font, sf::Vector2f pos, sf::Vector2f size) {
    box.setPosition(pos);
    box.setSize(size);
    box.setFillColor(sf::Color(28, 28, 32));
    box.setOutlineThickness(2.f);
    box.setOutlineColor(sf::Color(80, 80, 90));

    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::White);

    placeholder.setFont(font);
    placeholder.setCharacterSize(18);
    placeholder.setFillColor(sf::Color(160, 160, 170));

    setPosition(pos);
}

void TextInput::setPosition(sf::Vector2f p) {
    box.setPosition(p);
    constexpr float padX = 12.f;
    constexpr float padY = 9.f;
    text.setPosition(p.x + padX, p.y + padY);
    placeholder.setPosition(p.x + padX, p.y + padY);
}

void TextInput::setPlaceholder(const std::string& s) {
    placeholder.setString(s);
}

void TextInput::setActive(bool a) {
    active = a;
    box.setOutlineColor(active ? sf::Color(120, 170, 255) : sf::Color(80, 80, 90));
}

bool TextInput::hit(sf::Vector2f p) const {
    return box.getGlobalBounds().contains(p);
}

void TextInput::handleEvent(const sf::Event& e) {
    if (!active) return;

    if (e.type == sf::Event::TextEntered) {
        const auto u = e.text.unicode;

        if (u == 8) { // backspace
            auto s = text.getString();
            if (!s.isEmpty()) s.erase(s.getSize() - 1, 1);
            text.setString(s);
            return;
        }

        if (u == 13) { // enter
            active = false;
            box.setOutlineColor(sf::Color(80, 80, 90));
            return;
        }

        if (u >= 32 && u < 127) {
            auto s = text.getString();
            if (s.getSize() < 24) {
                s += static_cast<sf::Uint32>(u);
                text.setString(s);
            }
        }
    }
}

std::string TextInput::get() const {
    return text.getString().toAnsiString();
}

void TextInput::clear() {
    text.setString("");
}

void TextInput::draw(sf::RenderTarget& target) const {
    target.draw(box);

    if (text.getString().isEmpty()) target.draw(placeholder);
    else target.draw(text);
}
