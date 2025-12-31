#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
private:
    sf::RectangleShape rect;
    sf::Text text;
    std::string textString;
    bool enabled{true};

    void recenterText();

public:
    Button() = default;

    Button(const sf::Font& f,
           std::string label,
           sf::Vector2f pos,
           sf::Vector2f size);

    bool hit(sf::Vector2f mouse) const;

    void setEnabled(bool e);
    bool isEnabled() const;

    void setPosition(sf::Vector2f pos);
    void setSize(sf::Vector2f size);
    void setText(std::string s);

    void draw(sf::RenderTarget& target) const;
};

#endif
