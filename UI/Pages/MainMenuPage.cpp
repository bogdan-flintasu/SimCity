//
// Created by flint on 2/12/2026.
//

#include "MainMenuPage.h"

MainMenuPage::MainMenuPage(const sf::RenderWindow& window, sf::Font& font)
    : m_title(font), m_subtitle(font)
{
    const sf::Vector2u size = window.getSize();
    float cx = static_cast<float>(size.x) / 2.f;
    const float cy = static_cast<float>(size.y) / 2.f;

    m_background.setSize({static_cast<float>(size.x), static_cast<float>(size.y)});
    m_background.setFillColor(sf::Color(20, 20, 30));

    m_title.setFont(font);
    m_title.setString("SIMCITY");
    m_title.setCharacterSize(60);
    m_title.setFillColor(sf::Color::White);
    m_title.setStyle(sf::Text::Bold);

    const auto bTitle = m_title.getLocalBounds();
    m_title.setOrigin({
        bTitle.position.x + bTitle.size.x / 2.f,
        bTitle.position.y + bTitle.size.y / 2.f
    });
    m_title.setPosition({cx, cy - 200.f});

    m_subtitle.setFont(font);
    m_subtitle.setString("Fii primarul viselor tale");
    m_subtitle.setCharacterSize(24);
    m_subtitle.setFillColor(sf::Color(200, 200, 200));
    m_subtitle.setStyle(sf::Text::Italic);

    const auto bSub = m_subtitle.getLocalBounds();
    m_subtitle.setOrigin({
        bSub.position.x + bSub.size.x / 2.f,
        bSub.position.y + bSub.size.y / 2.f
    });
    m_subtitle.setPosition({cx, cy - 140.f});

    m_btnChallenge = std::make_unique<ui::Button>(
        sf::Vector2f{cx - 200.f - 150.f, cy - 40.f},
        sf::Vector2f{300.f, 80.f},
        "PROVOCARE\n(Oras Prestabilit)", font, sf::Color(200, 50, 50)
    );
    m_btnChallenge->setCallback([this]() { m_selectedAction = MenuAction::START_CHALLENGE; });

    m_btnSandbox = std::make_unique<ui::Button>(
        sf::Vector2f{cx + 200.f - 150.f, cy - 40.f},
        sf::Vector2f{300.f, 80.f},
        "SANDBOX\n(De la zero)", font, sf::Color(50, 150, 50)
    );
    m_btnSandbox->setCallback([this]() { m_selectedAction = MenuAction::START_SANDBOX; });

    m_btnExit = std::make_unique<ui::Button>(
        sf::Vector2f{cx - 100.f, cy + 150.f},
        sf::Vector2f{200.f, 50.f},
        "IESIRE", font, sf::Color(100, 100, 100)
    );
    m_btnExit->setCallback([this]() { m_selectedAction = MenuAction::EXIT; });
}

void MainMenuPage::handleEvent(const sf::Event& event, const sf::RenderWindow& window) const {
    m_btnChallenge->handleEvent(event, window);
    m_btnSandbox->handleEvent(event, window);
    m_btnExit->handleEvent(event, window);
}

void MainMenuPage::draw(sf::RenderWindow& window) const {
    window.setView(window.getDefaultView());
    window.draw(m_background);
    window.draw(m_title);
    window.draw(m_subtitle);
    m_btnChallenge->draw(window);
    m_btnSandbox->draw(window);
    m_btnExit->draw(window);
}
