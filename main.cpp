#include "UI/Pages/MainMenuPage.h"
#include "GameSession.h" // Clasa noua

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "SimCity OOP");
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.openFromFile("assets/font.ttf")) {
        throw std::runtime_error("Nu s-a putut incarca fontul!");
    }
    MainMenuPage mainMenu(window, font);

    while (window.isOpen()) {
        // --- SFML 3 EVENT LOOP ---
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Trimitem evenimentul concret catre meniu
            mainMenu.handleEvent(*event, window);
        }
        // -------------------------

        // 2. Verificam ce a ales utilizatorul
        MenuAction action = mainMenu.getAction();

        if (action == MenuAction::START_CHALLENGE) {
            GameSession session(window, font, SessionMode::CHALLENGE);
            session.run();
            mainMenu.resetAction();
        }
        else if (action == MenuAction::START_SANDBOX) {
            GameSession session(window, font, SessionMode::SANDBOX);
            session.run();
            mainMenu.resetAction();
        }
        else if (action == MenuAction::EXIT) {
            window.close();
        }

        window.clear();
        mainMenu.draw(window);
        window.display();
    }
    return 0;
}