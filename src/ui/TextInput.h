#ifndef UI_TEXTINPUT_H
#define UI_TEXTINPUT_H

#include <SFML/Graphics.hpp>
#include <string>

class TextInput {
    sf::RectangleShape box;
    sf::Text text;
    sf::Text placeholder;
    bool active{false};

public:
    TextInput() = default;
    TextInput(const sf::Font& font, sf::Vector2f pos, sf::Vector2f size);

    void setPlaceholder(const std::string& s);
    void setActive(bool a);
    bool hit(sf::Vector2f p) const;

    void setPosition(sf::Vector2f p);

    void handleEvent(const sf::Event& e);

    std::string get() const;
    void clear();

    void draw(sf::RenderTarget& target) const;
};

#endif
