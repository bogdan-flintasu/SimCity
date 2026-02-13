#include "Form.h"

namespace ui {
    Form::Form(const sf::Font& font) : m_font(font) {
        m_background.setFillColor(sf::Color(40, 40, 40));
        m_background.setOutlineThickness(2.f);
        m_background.setOutlineColor(sf::Color::White);
    }

    void Form::configure(const std::vector<std::string>& fieldNames) {
        m_fields.clear();
        m_activeIndex = 0;

        float totalHeight = 60.f + static_cast<float>(fieldNames.size()) * 45.f;
        m_background.setSize({400.f, totalHeight});
        m_background.setPosition({440.f, 360.f - totalHeight / 2.f});

        float startY = m_background.getPosition().y + 30.f;

        m_fields.reserve(fieldNames.size());

        for (size_t i = 0; i < fieldNames.size(); ++i) {
            m_fields.emplace_back(m_font, fieldNames[i]);
            const float offset = static_cast<float>(i) * 45.f;
            FormField& f = m_fields.back();
            f.label.setPosition({460.f, startY + offset});
            f.input.setPosition({600.f, startY + offset});
        }
    }

    void Form::show() {
        m_active = true;
        m_confirmed = false;
    }

    void Form::hide() {
        m_active = false;
    }

    std::vector<std::string> Form::getValues() const {
        std::vector<std::string> vals;
        vals.reserve(m_fields.size());
        for(const auto& f : m_fields) {
            vals.push_back(f.value);
        }
        return vals;
    }

    void Form::handleEvent(const sf::Event& event) {
        if (!m_active) return;

        if (const auto* k = event.getIf<sf::Event::KeyPressed>()) {
            if (k->code == sf::Keyboard::Key::Tab) {
                if (!m_fields.empty()) {
                    m_activeIndex = (m_activeIndex + 1) % m_fields.size();
                }
                return;
            }
        }

        if (const auto* textEvent = event.getIf<sf::Event::TextEntered>()) {

            if (textEvent->unicode == 13) {
                if (m_activeIndex < m_fields.size() - 1) {
                    m_activeIndex++;
                }
                else {
                    m_confirmed = true;
                    m_active = false;
                }
            }
            else if (textEvent->unicode == 8) {
                if (!m_fields.empty() && !m_fields[m_activeIndex].value.empty()) {
                    m_fields[m_activeIndex].value.pop_back();
                }
            }
            else if (textEvent->unicode >= 32 && textEvent->unicode < 128) {
                if (!m_fields.empty()) {
                    m_fields[m_activeIndex].value += static_cast<char>(textEvent->unicode);
                }
            }

            for (size_t i = 0; i < m_fields.size(); ++i) {
                std::string display = m_fields[i].value;
                if (i == m_activeIndex) display += "_";
                m_fields[i].input.setString(display);
            }
        }
    }

    void Form::draw(sf::RenderWindow& window) const {
        if (!m_active) return;

        window.draw(m_background);

        for (size_t i = 0; i < m_fields.size(); ++i) {
            window.draw(m_fields[i].label);

            sf::Text tempInput = m_fields[i].input;
            if (i == m_activeIndex) {
                tempInput.setFillColor(sf::Color::Yellow);
            } else {
                tempInput.setFillColor(sf::Color::White);
            }
            window.draw(tempInput);
        }
    }

    void Form::fillInputs(const std::vector<std::string>& values) {
        for (size_t i = 0; i < m_fields.size() && i < values.size(); ++i) {

            m_fields[i].value = values[i];
            m_fields[i].input.setString(values[i]);
        }
    }
}