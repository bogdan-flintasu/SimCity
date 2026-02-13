//
// Created by flint on 2/12/2026.
//

#ifndef OOP_GAMESESSION_H
#define OOP_GAMESESSION_H

#pragma once
#include <SFML/Graphics.hpp>
#include "../Headers/Oras.h"
#include "Pages/EditPage.h"
#include "Pages/ProjectPage.h"
#include "../Headers/ChallangeManager.h"

enum class SessionMode { CHALLENGE, SANDBOX };

class GameSession {
private:
    sf::RenderWindow& m_window;
    sf::Font& m_font;
    Oras m_oras;
    EditMode m_editPage;
    ProjectMode m_projectPage;

    bool m_isRunning = true;
    bool m_showIntroPopup = true;

    sf::RectangleShape m_introBg;
    sf::Text m_introTitle;
    sf::Text m_introBody;
    std::unique_ptr<ui::Button> m_btnIntroOk;
    std::unique_ptr<ChallengeManager> m_challengeManager;
    enum class InternalState { INTRO, EDITING, PROJECT_MENU };
    InternalState m_state = InternalState::INTRO;

public:
    GameSession(sf::RenderWindow& window, sf::Font& font, SessionMode mode);
    void run();
};

#endif //OOP_GAMESESSION_H