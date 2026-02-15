//
// Created by flint on 2/12/2026.
//

#include "GameSession.h"

#include "Button.h"

GameSession::GameSession(sf::RenderWindow& window, sf::Font& font, const SessionMode mode)
    : m_window(window),
      m_oras(mode == SessionMode::SANDBOX ? "Oras Sandbox" : "Challenge",
            mode == SessionMode::SANDBOX ? 1000000.0 : 0,
            0),
      m_editPage(window, font, m_oras),
      m_projectPage(window, font, m_oras, m_editPage), m_introTitle(font), m_introBody(font) {
    if (mode == SessionMode::CHALLENGE) {
        ChallengeManager::getInstance();

        m_oras.incarca_preset_challenge();
        m_editPage.generateChallengeVisuals();
        m_editPage.setChallengeMode(true);

        m_introTitle.setString(ChallengeManager::getTitle());
        m_introBody.setString(ChallengeManager::getDescription());
    } else {
        m_oras.reset();
        m_oras.set_nume("Orasul Tau");

        m_introTitle.setString("BINE AI VENIT, PRIMARE!");
        m_introBody.setString(
            "Acesta este orasul tau. Construieste-l cum doresti.\n\n"
            "REGULI:\n"
            "- Castigi daca mentii fericirea > 80% timp de 6 luni.\n"
            "- Pierzi daca fericirea scade la 0% sau trec 48 de luni.\n\n"
            "Succes!"
        );
    }

    m_introBg.setSize({800, 500});
    m_introBg.setOrigin({400, 250});
    m_introBg.setPosition({640, 360});
    m_introBg.setFillColor(sf::Color(20, 20, 30, 250));
    m_introBg.setOutlineThickness(2);
    m_introBg.setOutlineColor(sf::Color::Cyan);

    m_introTitle.setFont(font);
    m_introTitle.setCharacterSize(30);
    m_introTitle.setFillColor(sf::Color::Yellow);
    m_introTitle.setPosition({640, 160});

    const auto bounds = m_introTitle.getLocalBounds();
    m_introTitle.setOrigin({
        bounds.position.x + bounds.size.x / 2.0f,
        bounds.position.y + bounds.size.y / 2.0f
    });
    m_introTitle.setPosition({640.f, 160.f});

    m_introBody.setFont(font);
    m_introBody.setCharacterSize(20);
    m_introBody.setPosition({300, 220});

    m_btnIntroOk = std::make_unique<ui::Button>(
        sf::Vector2f{640, 550}, sf::Vector2f{150, 50}, "AM INTELES", font, sf::Color(0, 150, 0)
    );
    m_btnIntroOk->setCallback([this]() { m_state = InternalState::EDITING; });
}

void GameSession::run() {
    sf::Clock clock;

    while (m_window.isOpen() && m_isRunning) {

        const float dt = clock.restart().asSeconds();

        while (const std::optional event = m_window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {
                m_window.close();
                return;
            }

            const sf::Event& actualEvent = *event;

            if (m_state == InternalState::INTRO) {
                m_btnIntroOk->handleEvent(actualEvent, m_window);
            }
            else if (m_state == InternalState::PROJECT_MENU) {
                m_projectPage.handleEvent(actualEvent, m_window);

                if (m_projectPage.shouldClose()) {
                    m_state = InternalState::EDITING;
                    m_projectPage.resetCloseFlag();
                    m_editPage.resetFinishState();
                }

                if (m_projectPage.hasRequestedStart()) {
                     m_editPage.startProjectSession(m_projectPage.getRequestedCategory(), m_projectPage.getRequestedAction());
                     m_state = InternalState::EDITING;
                     m_projectPage.resetRequest();
                }
            }
            else if (m_state == InternalState::EDITING) {
                m_editPage.handleEvent(actualEvent, m_window);

                if (m_editPage.isFinished()) {
                    m_state = InternalState::PROJECT_MENU;
                }
            }
        }

        if (m_state == InternalState::PROJECT_MENU) {
             m_projectPage.update(dt);
             if (m_projectPage.shouldClose()) {
                 m_state = InternalState::EDITING;
                 m_projectPage.resetCloseFlag();
                 m_editPage.resetFinishState();
             }
        }
        else if (m_state == InternalState::EDITING) {
            m_editPage.update(dt, m_window);
        }

        m_window.clear(sf::Color(20, 20, 30));

        if (m_state == InternalState::INTRO) {
            m_editPage.draw(m_window);

            sf::RectangleShape overlay(sf::Vector2f(m_window.getSize()));
            overlay.setFillColor(sf::Color(0,0,0,200));
            m_window.draw(overlay);

            m_window.draw(m_introBg);
            m_window.draw(m_introTitle);
            m_window.draw(m_introBody);
            m_btnIntroOk->draw(m_window);
        }
        else if (m_state == InternalState::PROJECT_MENU) {
            m_editPage.draw(m_window);
            sf::RectangleShape overlay(sf::Vector2f(m_window.getSize()));
            overlay.setFillColor(sf::Color(0,0,0,200));
            m_window.draw(overlay);
            m_projectPage.draw(m_window);
        }
        else {
            m_editPage.draw(m_window);
        }

        m_window.display();
    }
}
