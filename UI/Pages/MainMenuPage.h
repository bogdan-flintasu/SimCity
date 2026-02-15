//
// Created by flint on 2/12/2026.
//

#ifndef OOP_MAINMENUPAGE_H
#define OOP_MAINMENUPAGE_H

#pragma once
#include <SFML/Graphics.hpp>
#include "../Button.h"
#include <memory>

enum class MenuAction {
    NONE,
    START_CHALLENGE,
    START_SANDBOX,
    EXIT
};

class MainMenuPage {
private:
    sf::RectangleShape m_background;
    sf::Text m_title;
    sf::Text m_subtitle;

    std::unique_ptr<ui::Button> m_btnChallenge;
    std::unique_ptr<ui::Button> m_btnSandbox;
    std::unique_ptr<ui::Button> m_btnExit;

    MenuAction m_selectedAction = MenuAction::NONE;

public:
    MainMenuPage(const sf::RenderWindow& window, sf::Font& font);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window) const;
    void draw(sf::RenderWindow& window) const;

    MenuAction getAction() const { return m_selectedAction; }
    void resetAction() { m_selectedAction = MenuAction::NONE; }
};

#endif //OOP_MAINMENUPAGE_H