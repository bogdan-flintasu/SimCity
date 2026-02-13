#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace ui {
    struct FormField {
        sf::Text label;
        sf::Text input;
        std::string value;

        FormField(const sf::Font& font, const std::string& labelText)
            : label(font, labelText, 18),
              input(font, "_", 18)
        {
            label.setFillColor(sf::Color(200, 200, 200));
            input.setFillColor(sf::Color::White);
        }
    };

    class Form {
    public:
        explicit Form(const sf::Font& font);

        void configure(const std::vector<std::string>& fieldLabels);

        void show();
        void hide();
        bool isActive() const { return m_active; }
        bool isConfirmed() const { return m_confirmed; }

        void handleEvent(const sf::Event& event);
        void draw(sf::RenderWindow& window) const;
        void fillInputs(const std::vector<std::string>& values);

        std::vector<std::string> getValues() const;

    private:
        const sf::Font& m_font;
        sf::RectangleShape m_background;
        std::vector<FormField> m_fields;

        std::size_t m_activeIndex = 0;

        bool m_active = false;
        bool m_confirmed = false;
    };
}