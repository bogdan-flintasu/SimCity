#include "ProjectPage.h"
#include <iomanip>
#include <sstream>
#include <iostream>

ProjectMode::ProjectMode(const sf::RenderWindow& window, sf::Font& font, Oras& oras, EditMode& editMode)
    : m_editMode(editMode),
      m_font(font),
      m_oras(oras),
      m_statsText(font) {
    initUI(window);
}

void ProjectMode::initUI(const sf::RenderWindow& window) {
    const sf::Vector2u winSize = window.getSize();
    float centerX = static_cast<float>(winSize.x) / 2.f;
    float centerY = static_cast<float>(winSize.y) / 2.f;

    m_dashboardBg.setSize({500.f, 600.f});
    m_dashboardBg.setOrigin({250.f, 300.f});
    m_dashboardBg.setPosition({centerX, centerY});
    m_dashboardBg.setFillColor(sf::Color(25, 25, 40, 250));
    m_dashboardBg.setOutlineThickness(2.f);
    m_dashboardBg.setOutlineColor(sf::Color(0, 200, 255));

    m_statsText.setCharacterSize(24);
    m_statsText.setFillColor(sf::Color::White);
    m_statsText.setLineSpacing(1.5f);
    updateStatsText();

    m_progressBarContainer.setSize({400.f, 10.f});
    m_progressBarContainer.setOrigin({200.f, 5.f});
    m_progressBarContainer.setPosition({centerX, centerY - 140.f});
    m_progressBarContainer.setFillColor(sf::Color(50, 50, 50));
    m_progressBarContainer.setOutlineThickness(1.f);
    m_progressBarContainer.setOutlineColor(sf::Color::White);

    m_progressBarFill.setSize({0.f, 10.f});
    m_progressBarFill.setPosition({centerX - 200.f, centerY - 145.f});
    m_progressBarFill.setFillColor(sf::Color(0, 255, 0));

    m_buttons.clear();

    m_btnActionToggle = std::make_shared<ui::Button>(
        sf::Vector2f{centerX - 150.f, centerY - 80.f},
        sf::Vector2f{300.f, 40.f},
        "", m_font, sf::Color::White
    );

    m_btnActionToggle->setCallback([this](){
        if(m_isSimulating) return;

        if (m_selectedAction == Amanunte::DE_LA_ZERO) m_selectedAction = Amanunte::DEMOLARE;
        else m_selectedAction = Amanunte::DE_LA_ZERO;

        updateActionButton();
    });

    updateActionButton();

    auto createBtn = [&](const std::string& txt, const float offsetY, const std::string& cat) {
        const auto btn = std::make_shared<ui::Button>(
            sf::Vector2f{centerX - 150.f, centerY + offsetY},
            sf::Vector2f{300.f, 50.f},
            txt, m_font, sf::Color(0, 100, 200)
        );
        btn->setCallback([this, cat](){
            if(!m_isSimulating) {
                m_requestedCategory = cat;
                m_hasRequest = true;
            }
        });
        m_buttons.push_back(btn);
    };

    createBtn("PROIECT INFRASTRUCTURA", 20.f, "Infrastructura");
    createBtn("PROIECT REZIDENTIAL", 90.f, "Rezidential");
    createBtn("PROIECT PUBLIC", 160.f, "Public");

    m_btnSimulate = std::make_shared<ui::Button>(
        sf::Vector2f{centerX - 120.f, centerY - 200.f},
        sf::Vector2f{240.f, 50.f},
        "SIMULARE LUNA", m_font, sf::Color(220, 150, 0)
    );

    m_btnSimulate->setCallback([this](){
        if (!m_isSimulating) {
            m_isSimulating = true;
            m_simulationProgress = 0.0f;
            m_progressBarFill.setSize({0.f, 10.f});
            std::cout << "Incepere simulare luna...\n";
        }
    });
}

void ProjectMode::updateActionButton() const {
    std::string txt;
    sf::Color col;

    switch(m_selectedAction) {
        case Amanunte::DE_LA_ZERO:
            txt = "MOD: CONSTRUCTIE NOUA";
            col = sf::Color(0, 150, 0);
            break;
        case Amanunte::DEMOLARE:
            txt = "MOD: DEMOLARE";
            col = sf::Color(200, 50, 50);
            break;
    }

    m_btnActionToggle->setText(txt);
    m_btnActionToggle->setBackgroundColor(col);
}

void ProjectMode::updateStatsText() {
    std::stringstream ss;

    ss << "Buget: " << std::fixed << std::setprecision(2) << m_oras.get_buget() << " RON\n";

    const double fericireRaw = m_oras.get_fericire();
    int fericireAfisata = static_cast<int>(fericireRaw * 100);
    int luniExcelenta = m_oras.get_luni_excelenta();

    if (fericireAfisata > 100) fericireAfisata = 100;
    if (fericireAfisata < 0) fericireAfisata = 0;

    ss << "Fericire: " << fericireAfisata << "%";

    ss << "Luni de excelenta: " << luniExcelenta << " / 6";

    m_statsText.setString(ss.str());

    if (fericireAfisata < 40) m_statsText.setFillColor(sf::Color(255, 100, 100));
    else if (fericireAfisata > 80) m_statsText.setFillColor(sf::Color::Green);
    else m_statsText.setFillColor(sf::Color::White);

    const sf::FloatRect bounds = m_statsText.getLocalBounds();
    m_statsText.setOrigin({
        bounds.position.x + bounds.size.x / 2.0f,
        bounds.position.y + bounds.size.y / 2.0f
    });

    m_statsText.setPosition({
        m_dashboardBg.getPosition().x,
        m_dashboardBg.getPosition().y - 260.f
    });
}

void ProjectMode::update(const float dt) {
    if (m_isSimulating) {
        m_simulationProgress += dt * m_simulationSpeed;

        float currentWidth = 400.f * std::min(m_simulationProgress, 1.0f);
        m_progressBarFill.setSize({currentWidth, 10.f});

        if (m_simulationProgress >= 1.0f) {
            m_isSimulating = false;
            m_oras.simulare_luna();
            bool isGameOver = m_editMode.checkGameStatus();
            updateStatsText();
            if (isGameOver) {
                m_shouldClose = true;
            }
            std::cout << "Luna simulata cu succes.\n";
        }
    } else {
        updateStatsText();
    }
}

void ProjectMode::handleEvent(const sf::Event& event, const sf::RenderWindow& window) const {
    if (m_isSimulating) return;

    if(m_btnActionToggle) m_btnActionToggle->handleEvent(event, window);
    for(auto& btn : m_buttons) btn->handleEvent(event, window);
    m_btnSimulate->handleEvent(event, window);
}

void ProjectMode::draw(sf::RenderWindow& window) const {
    window.draw(m_dashboardBg);
    window.draw(m_statsText);

    if (m_isSimulating) {
        window.draw(m_progressBarContainer);
        window.draw(m_progressBarFill);
    } else if(m_btnActionToggle)
            m_btnActionToggle->draw(window);

    for(auto& btn : m_buttons) btn->draw(window);
    m_btnSimulate->draw(window);
}