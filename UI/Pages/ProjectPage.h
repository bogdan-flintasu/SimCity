#ifndef OOP_PROJECTPAGE_H
#define OOP_PROJECTPAGE_H

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include "EditPage.h"
#include "../../Headers/Oras.h"
#include "../Button.h"

class ProjectMode {
public:
    ProjectMode(const sf::RenderWindow& window, sf::Font& font, Oras& oras, EditMode& editMode);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) const;

    void update(float dt);

    void draw(sf::RenderWindow& window) const;

    bool hasRequestedStart() const { return m_hasRequest; }
    std::string getRequestedCategory() const { return m_requestedCategory; }
    Amanunte getRequestedAction() const { return m_selectedAction; }
    bool shouldClose() const { return m_shouldClose; }
    void resetCloseFlag() { m_shouldClose = false; }

    void resetRequest() {
        m_hasRequest = false;
        m_requestedCategory.clear();
    }

    bool m_shouldClose = false;

private:
    EditMode& m_editMode;
    Amanunte m_selectedAction = Amanunte::DE_LA_ZERO;
    std::shared_ptr<ui::Button> m_btnActionToggle;
    void updateActionButton() const;

    sf::Font& m_font;
    Oras& m_oras;

    sf::RectangleShape m_dashboardBg;
    std::vector<std::shared_ptr<ui::Button>> m_buttons;
    std::shared_ptr<ui::Button> m_btnSimulate;

    sf::Text m_statsText;

    sf::RectangleShape m_progressBarContainer;
    sf::RectangleShape m_progressBarFill;
    bool m_isSimulating = false;
    float m_simulationProgress = 0.0f;
    float m_simulationSpeed = 0.5f;

    bool m_hasRequest = false;
    std::string m_requestedCategory;

    void initUI(const sf::RenderWindow& window);
    void updateStatsText();
};

#endif //OOP_PROJECTPAGE_H