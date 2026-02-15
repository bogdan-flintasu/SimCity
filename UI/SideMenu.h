#pragma once
#include <SFML/Graphics.hpp>
#include "UI.h"

namespace ui {
    enum class ToolType {
        NONE, ZONING, DELETE, FINALIZE,
        STRADA, SPATIU_VERDE,
        CASA, BLOC,
        FABRICA, SPATIU_COMERCIAL,
        CLADIRE_ADMINISTRATIVA, CLADIRE_SERVICII, CLADIRE_ECONOMIE,
        CLADIRE_EDUCATIE
    };

    class SideMenu {
    public:
        explicit SideMenu(const sf::Font& font);

        void update(float dt);
        void handleEvent(const sf::Event& event, const sf::RenderWindow& window) const;
        void draw(sf::RenderWindow& window) const;

        void toggle() { m_isOpen = !m_isOpen; }
        void resetSelection() { m_activeTool = ToolType::NONE; }
        ToolType getActiveTool() const { return m_activeTool; }

    private:
        sf::RectangleShape m_background;
        ui::UIManager m_buttons;
        ToolType m_activeTool = ToolType::NONE;
        sf::Text m_infoText;
        bool m_isOpen;
        float m_currentX;
    };
}