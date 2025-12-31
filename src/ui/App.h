#ifndef UI_APP_H
#define UI_APP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Button.h"
#include "TextInput.h"

class App {
public:
    App();
    void run();

private:
    enum class PlaceType { NONE, STRADA, CASA, BLOC, ADMIN, SERVICII, EDUCATIE, VERDE };
    enum class Mode { NONE, CREATE_ZONE };

    struct BuildingViz {
        PlaceType type{PlaceType::NONE};
        sf::FloatRect rect{};
    };

    struct ZonaVizuala {
        std::string nume;
        sf::FloatRect rect;                 // world coords
        std::vector<BuildingViz> buildings; // includes STRADA cells too
    };

    sf::RenderWindow window;
    sf::Font font;

    static constexpr float PANEL_W = 360.f;

    sf::View uiView;
    sf::View worldView;

    Mode mode{Mode::NONE};
    PlaceType placeMode{PlaceType::NONE};

    // UI
    TextInput inputZonaNume;
    Button btnCreateZone;
    Button btnCancelMode;

    sf::Text title;
    sf::Text help;
    sf::Text status;
    sf::Text hoveredZoneLabel;
    sf::Text modeLabel;

    Button btnPlaceStrada;
    Button btnPlaceCasa;
    Button btnPlaceBloc;
    Button btnPlaceAdmin;
    Button btnPlaceServicii;
    Button btnPlaceEducatie;
    Button btnPlaceVerde;

    // world
    sf::RectangleShape mapBg;

    // zones
    std::vector<ZonaVizuala> zone;
    int hoveredZone{-1};
    int zoneCounter{0};

    // zone creation drag
    bool dragging{false};
    sf::Vector2f dragStart{};
    sf::RectangleShape previewRect;

    // hover border
    sf::RectangleShape hoverBorder;

    // road painting
    bool paintingRoad{false};
    sf::Vector2i lastRoadCell{-9999, -9999};

    // helpers
    void loadFontOrThrow();
    void setStatus(const std::string& msg);

    sf::FloatRect worldBounds() const;
    bool mouseInWorld(sf::Vector2f mousePixel) const;
    sf::Vector2f mouseWorld(sf::Vector2i mousePixel) const;

    static sf::FloatRect rectFromPoints(sf::Vector2f a, sf::Vector2f b);
    static bool inside(const sf::FloatRect& container, const sf::FloatRect& r);
    static bool intersectsAny(const ZonaVizuala& z, const sf::FloatRect& r);
    static sf::FloatRect snapRect(sf::Vector2f center, float w, float h, float tile);
    static sf::Color colorFor(PlaceType t);

    void updateHover(sf::Vector2f mWorld);

    void startCreateZone();
    void cancelMode();

    void beginDrag(sf::Vector2f mWorld);
    void updateDrag(sf::Vector2f mWorld);
    void endDrag(sf::Vector2f mWorld);
};

#endif
