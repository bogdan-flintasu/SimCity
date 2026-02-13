#include "SideMenu.h"

namespace ui {
    SideMenu::SideMenu(const sf::Font& font)
        :m_infoText(font),  m_isOpen(true), m_currentX(0.f)
    {
        m_background.setSize({250.f, 1080.f});
        m_background.setFillColor(sf::Color(30, 30, 30, 220));

        m_buttons.addButton({10, 50}, {230, 30}, "Creare Zona", font, [this](){ m_activeTool = ToolType::ZONING; }, sf::Color(0, 255, 255, 50));
        m_buttons.addButton({10, 100}, {230, 30}, "Casa (2x2)", font, [this](){ m_activeTool = ToolType::CASA; }, sf::Color(50, 205, 50));
        m_buttons.addButton({10, 135}, {230, 30}, "Bloc (3x3)", font, [this](){ m_activeTool = ToolType::BLOC; }, sf::Color(65, 105, 225));
        m_buttons.addButton({10, 180}, {230, 30}, "Strada (1x1)", font, [this](){ m_activeTool = ToolType::STRADA; }, sf::Color(60, 60, 60));
        m_buttons.addButton({10, 215}, {230, 30}, "Spatiu Verde (2x2)", font, [this](){ m_activeTool = ToolType::SPATIU_VERDE; }, sf::Color(34, 139, 34));
        m_buttons.addButton({10, 260}, {230, 30}, "Fabrica (4x4)", font, [this](){ m_activeTool = ToolType::FABRICA; }, sf::Color(210, 105, 30));
        m_buttons.addButton({10, 295}, {230, 30}, "Comercial (3x2)", font, [this](){ m_activeTool = ToolType::SPATIU_COMERCIAL; }, sf::Color(255, 215, 0));
        m_buttons.addButton({10, 340}, {230, 30}, "Administrativ (3x3)", font, [this](){ m_activeTool = ToolType::CLADIRE_ADMINISTRATIVA; }, sf::Color(128, 0, 128));
        m_buttons.addButton({10, 375}, {230, 30}, "Servicii (2x2)", font, [this](){ m_activeTool = ToolType::CLADIRE_SERVICII; }, sf::Color(255, 105, 180));
        m_buttons.addButton({10, 410}, {230, 30}, "Educatie (3x3)", font, [this](){ m_activeTool = ToolType::CLADIRE_EDUCATIE; }, sf::Color(255, 140, 0));
        m_buttons.addButton({10, 10}, {230, 30}, "STERGERE", font, [this](){ m_activeTool = ToolType::DELETE; }, sf::Color(180, 0, 0));
        m_buttons.addButton({10, 450}, {230, 40}, ">>> FINALIZARE <<<", font, [this](){ m_activeTool = ToolType::FINALIZE; }, sf::Color(0, 150, 0));

        m_infoText.setFont(font);
        m_infoText.setCharacterSize(14);
        m_infoText.setFillColor(sf::Color(200, 200, 200));

        m_infoText.setString(
            "--- CONTROALE ---\n\n"
            "TAB: Inchide/Deschide Meniu\n"
            "ESC: Anulare / Deselectare\n\n"
            "CLICK STANGA:\n"
            " - Selectare Cladire\n"
            " - Plasare Constructie\n"
            " - Tragere Zona/Strada\n\n"
            "CLICK DREAPTA:\n"
            " - Miscare Camera (Pan)\n"
            " - Anulare Constructie"
        );

        m_infoText.setPosition({15.f, 510.f});
    }

    void SideMenu::update(const float dt) {
        constexpr float menuWidth = 250.f;
        const float targetX = m_isOpen ? 0.f : -menuWidth;
        constexpr float speed = 15.f;
        m_currentX += (targetX - m_currentX) * speed * dt;
        m_background.setPosition({m_currentX, 0.f});
        m_infoText.setPosition({m_currentX + 15.f, 510.f});
    }

    void SideMenu::handleEvent(const sf::Event& event, const sf::RenderWindow& window) const {
        if (m_isOpen) {
             m_buttons.handleEvents(event, window);
        }
    }

    void SideMenu::draw(sf::RenderWindow& window) const {
        window.draw(m_background);
        if (m_currentX > -240.f) {
            m_buttons.draw(window);
            window.draw(m_infoText);
        }
    }
}