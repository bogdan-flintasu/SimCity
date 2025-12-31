#include "App.h"

#include <filesystem>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <string>

static bool tryLoadFont(sf::Font& f, const std::string& path) {
    try {
        if (std::filesystem::exists(path)) return f.loadFromFile(path);
    } catch (...) {}
    return false;
}

void App::loadFontOrThrow() {
    const std::vector<std::string> candidates = {
        "assets/arial.ttf",
        "./assets/arial.ttf",
        "../assets/arial.ttf",
        "../../assets/arial.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf"
    };

    for (const auto& p : candidates) {
        if (tryLoadFont(font, p)) return;
    }
    throw std::runtime_error("Nu pot incarca font. Pune assets/arial.ttf sau foloseste DejaVu in WSL.");
}

sf::Color App::colorFor(PlaceType t) {
    switch (t) {
        case PlaceType::STRADA:   return {230, 230, 235, 210};
        case PlaceType::CASA:     return {70, 120, 255, 210};
        case PlaceType::BLOC:     return {40, 80, 200, 210};
        case PlaceType::ADMIN:    return {60, 200, 120, 210};
        case PlaceType::SERVICII: return {40, 170, 100, 210};
        case PlaceType::EDUCATIE: return {30, 140, 90, 210};
        case PlaceType::VERDE:    return {70, 220, 90, 170};
        default:                  return sf::Color::Transparent;
    }
}

App::App()
    : window(sf::VideoMode(1200, 700), "SimCity Editor - Zone"),
      uiView(sf::FloatRect(0.f, 0.f, 1200.f, 700.f)),
      worldView(sf::FloatRect(PANEL_W, 0.f, 1200.f - PANEL_W, 700.f)),

      inputZonaNume(font, {20.f, 0.f}, {PANEL_W - 40.f, 42.f}),
      btnCreateZone(font, "Creeaza zona (drag)", {20.f, 0.f}, {PANEL_W - 40.f, 42.f}),
      btnCancelMode(font, "Anuleaza", {20.f, 0.f}, {PANEL_W - 40.f, 42.f}),

      btnPlaceStrada(font, "Plaseaza Strada", {20.f, 0.f}, {PANEL_W - 40.f, 38.f}),
      btnPlaceCasa(font, "Plaseaza Casa", {20.f, 0.f}, {PANEL_W - 40.f, 38.f}),
      btnPlaceBloc(font, "Plaseaza Bloc", {20.f, 0.f}, {PANEL_W - 40.f, 38.f}),
      btnPlaceAdmin(font, "Plaseaza Admin", {20.f, 0.f}, {PANEL_W - 40.f, 38.f}),
      btnPlaceServicii(font, "Plaseaza Servicii", {20.f, 0.f}, {PANEL_W - 40.f, 38.f}),
      btnPlaceEducatie(font, "Plaseaza Educatie", {20.f, 0.f}, {PANEL_W - 40.f, 38.f}),
      btnPlaceVerde(font, "Plaseaza Verde", {20.f, 0.f}, {PANEL_W - 40.f, 38.f}) {

    window.setFramerateLimit(60);
    loadFontOrThrow();

    constexpr float padX = 20.f;
    float y = 14.f;

    title.setFont(font);
    title.setCharacterSize(22);
    title.setFillColor(sf::Color::White);
    title.setPosition(padX, y);
    title.setString("Editor Oras - Constructie (de la 0)");
    y += 34.f;

    help.setFont(font);
    help.setCharacterSize(15);
    help.setFillColor(sf::Color(200, 200, 210));
    help.setPosition(padX, y);
    help.setString(
        "Zone: creezi prin drag.\n"
        "Cladiri: alegi tip, apoi click in zona.\n"
        "Strada: tine apasat click si \"pictezi\" pe grid."
    );
    y += 66.f;

    inputZonaNume.setPlaceholder("Nume zona (optional) ...");
    inputZonaNume.setPosition({padX, y});
    y += 52.f;

    btnCreateZone.setPosition({padX, y});
    y += 50.f;

    btnCancelMode.setPosition({padX, y});
    y += 58.f;

    modeLabel.setFont(font);
    modeLabel.setCharacterSize(14);
    modeLabel.setFillColor(sf::Color(170, 170, 180));
    modeLabel.setPosition(padX, y);
    modeLabel.setString("Plasare:");
    y += 26.f;

    btnPlaceStrada.setPosition({padX, y});    y += 44.f;
    btnPlaceCasa.setPosition({padX, y});      y += 44.f;
    btnPlaceBloc.setPosition({padX, y});      y += 44.f;
    btnPlaceAdmin.setPosition({padX, y});     y += 44.f;
    btnPlaceServicii.setPosition({padX, y});  y += 44.f;
    btnPlaceEducatie.setPosition({padX, y});  y += 44.f;
    btnPlaceVerde.setPosition({padX, y});     y += 44.f;

    status.setFont(font);
    status.setCharacterSize(15);
    status.setFillColor(sf::Color(200, 200, 210));
    status.setPosition(padX, 666.f);
    status.setString("Status: Ready");

    hoveredZoneLabel.setFont(font);
    hoveredZoneLabel.setCharacterSize(18);
    hoveredZoneLabel.setFillColor(sf::Color::White);
    hoveredZoneLabel.setPosition(PANEL_W + 20.f, 20.f);
    hoveredZoneLabel.setString("");

    mapBg.setPosition({PANEL_W, 0.f});
    mapBg.setSize({1200.f - PANEL_W, 700.f});
    mapBg.setFillColor(sf::Color(18, 18, 22));

    previewRect.setFillColor(sf::Color(255, 255, 255, 20));
    previewRect.setOutlineColor(sf::Color(255, 255, 255, 120));
    previewRect.setOutlineThickness(2.f);

    hoverBorder.setFillColor(sf::Color::Transparent);
    hoverBorder.setOutlineColor(sf::Color::White);
    hoverBorder.setOutlineThickness(2.f);

    setStatus("Ready");
}

sf::FloatRect App::worldBounds() const {
    return {
        PANEL_W,
        0.f,
        static_cast<float>(window.getSize().x) - PANEL_W,
        static_cast<float>(window.getSize().y)
    };
}

bool App::mouseInWorld(sf::Vector2f mousePixel) const {
    return worldBounds().contains(mousePixel);
}

sf::Vector2f App::mouseWorld(sf::Vector2i mousePixel) const {
    return window.mapPixelToCoords(mousePixel, worldView);
}

void App::setStatus(const std::string& msg) {
    status.setString("Status: " + msg);
}

sf::FloatRect App::rectFromPoints(sf::Vector2f a, sf::Vector2f b) {
    const float left = (a.x < b.x) ? a.x : b.x;
    const float top  = (a.y < b.y) ? a.y : b.y;
    const float w = (a.x < b.x) ? (b.x - a.x) : (a.x - b.x);
    const float h = (a.y < b.y) ? (b.y - a.y) : (a.y - b.y);
    return {left, top, w, h};
}

bool App::inside(const sf::FloatRect& container, const sf::FloatRect& r) {
    return r.left >= container.left
        && r.top >= container.top
        && (r.left + r.width) <= (container.left + container.width)
        && (r.top + r.height) <= (container.top + container.height);
}

bool App::intersectsAny(const ZonaVizuala& z, const sf::FloatRect& r) {
    for (const auto& b : z.buildings) {
        sf::FloatRect inter;
        if (b.rect.intersects(r, inter)) return true;
    }
    return false;
}

sf::FloatRect App::snapRect(sf::Vector2f center, float w, float h, float tile) {
    const auto snap = [&](float v) { return std::round(v / tile) * tile; };
    const float cx = snap(center.x);
    const float cy = snap(center.y);
    return {cx - w * 0.5f, cy - h * 0.5f, w, h};
}

void App::updateHover(sf::Vector2f mWorld) {
    hoveredZone = -1;

    for (int i = static_cast<int>(zone.size()) - 1; i >= 0; --i) {
        if (zone[i].rect.contains(mWorld)) {
            hoveredZone = i;
            break;
        }
    }

    if (hoveredZone != -1) {
        const auto& z = zone[hoveredZone];
        hoverBorder.setPosition({z.rect.left, z.rect.top});
        hoverBorder.setSize({z.rect.width, z.rect.height});
        hoveredZoneLabel.setString("Zona: " + z.nume);
    } else {
        hoveredZoneLabel.setString("");
    }
}

void App::startCreateZone() {
    mode = Mode::CREATE_ZONE;
    placeMode = PlaceType::NONE;
    dragging = false;
    paintingRoad = false;
    setStatus("Mode: CREATE_ZONE (drag pe harta)");
}

void App::cancelMode() {
    mode = Mode::NONE;
    placeMode = PlaceType::NONE;
    dragging = false;
    paintingRoad = false;
    setStatus("Mode: NONE");
}

void App::beginDrag(sf::Vector2f mWorld) {
    dragging = true;
    dragStart = mWorld;
    previewRect.setPosition(mWorld);
    previewRect.setSize({0.f, 0.f});
}

void App::updateDrag(sf::Vector2f mWorld) {
    if (!dragging) return;
    auto r = rectFromPoints(dragStart, mWorld);
    previewRect.setPosition({r.left, r.top});
    previewRect.setSize({r.width, r.height});
}

void App::endDrag(sf::Vector2f mWorld) {
    if (!dragging) return;
    dragging = false;

    auto r = rectFromPoints(dragStart, mWorld);

    if (r.width < 60.f || r.height < 60.f) {
        setStatus("Zona prea mica (minim ~60x60).");
        return;
    }

    std::string name = inputZonaNume.get();
    if (name.empty()) {
        zoneCounter++;
        name = "Zona " + std::to_string(zoneCounter);
    }

    zone.push_back({name, r, {}});
    inputZonaNume.clear();

    setStatus("Creata: " + name);
}

void App::run() {
    constexpr float tile = 25.f;

    const auto zoneAt = [&](sf::Vector2f worldPos) -> int {
        for (int i = static_cast<int>(zone.size()) - 1; i >= 0; --i)
            if (zone[i].rect.contains(worldPos)) return i;
        return -1;
    };

    const auto placeOne = [&](int zi, PlaceType t, sf::Vector2f worldPos) {
        if (zi < 0 || zi >= static_cast<int>(zone.size())) return;

        float w = 50.f, h = 50.f;
        if (t == PlaceType::STRADA) { w = 25.f; h = 25.f; }

        auto r = snapRect(worldPos, w, h, tile);

        const auto& zr = zone[zi].rect;

        if (r.left < zr.left) r.left = zr.left;
        if (r.top < zr.top) r.top = zr.top;
        if (r.left + r.width > zr.left + zr.width) r.left = zr.left + zr.width - r.width;
        if (r.top + r.height > zr.top + zr.height) r.top = zr.top + zr.height - r.height;

        if (!inside(zr, r)) {
            setStatus("Nu incape in zona.");
            return;
        }

        if (intersectsAny(zone[zi], r)) {
            setStatus("Nu poti suprapune peste alta cladire/strada.");
            return;
        }

        zone[zi].buildings.push_back({t, r});
        setStatus("Plasat in " + zone[zi].nume);
    };

    while (window.isOpen()) {
        sf::Event e{};
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) window.close();

            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                const sf::Vector2f mPix(static_cast<float>(e.mouseButton.x), static_cast<float>(e.mouseButton.y));

                if (!mouseInWorld(mPix)) {
                    const bool inputClicked = inputZonaNume.hit(mPix);
                    inputZonaNume.setActive(inputClicked);

                    if (btnCreateZone.hit(mPix)) startCreateZone();
                    else if (btnCancelMode.hit(mPix)) cancelMode();
                    else if (btnPlaceStrada.hit(mPix)) { mode = Mode::NONE; placeMode = PlaceType::STRADA; setStatus("Mode: PLACE Strada (tine click apasat si pictezi)"); }
                    else if (btnPlaceCasa.hit(mPix))   { mode = Mode::NONE; placeMode = PlaceType::CASA; setStatus("Mode: PLACE Casa"); }
                    else if (btnPlaceBloc.hit(mPix))   { mode = Mode::NONE; placeMode = PlaceType::BLOC; setStatus("Mode: PLACE Bloc"); }
                    else if (btnPlaceAdmin.hit(mPix))  { mode = Mode::NONE; placeMode = PlaceType::ADMIN; setStatus("Mode: PLACE Admin"); }
                    else if (btnPlaceServicii.hit(mPix)) { mode = Mode::NONE; placeMode = PlaceType::SERVICII; setStatus("Mode: PLACE Servicii"); }
                    else if (btnPlaceEducatie.hit(mPix)) { mode = Mode::NONE; placeMode = PlaceType::EDUCATIE; setStatus("Mode: PLACE Educatie"); }
                    else if (btnPlaceVerde.hit(mPix)) { mode = Mode::NONE; placeMode = PlaceType::VERDE; setStatus("Mode: PLACE Verde"); }

                } else {
                    inputZonaNume.setActive(false);

                    const sf::Vector2f mW = mouseWorld({e.mouseButton.x, e.mouseButton.y});

                    if (mode == Mode::CREATE_ZONE) {
                        beginDrag(mW);
                    } else if (placeMode != PlaceType::NONE) {
                        const int zi = zoneAt(mW);
                        if (zi == -1) {
                            setStatus("Da click in interiorul unei zone!");
                        } else {
                            if (placeMode == PlaceType::STRADA) {
                                paintingRoad = true;
                                lastRoadCell = {-9999, -9999};
                                placeOne(zi, placeMode, mW);
                            } else {
                                placeOne(zi, placeMode, mW);
                            }
                        }
                    }
                }
            }

            if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left) {
                const sf::Vector2f mPix(static_cast<float>(e.mouseButton.x), static_cast<float>(e.mouseButton.y));
                if (mouseInWorld(mPix)) {
                    const sf::Vector2f mW = mouseWorld({e.mouseButton.x, e.mouseButton.y});
                    if (mode == Mode::CREATE_ZONE && dragging) endDrag(mW);
                }
                paintingRoad = false;
            }

            if (e.type == sf::Event::MouseMoved) {
                const sf::Vector2f mPix(static_cast<float>(e.mouseMove.x), static_cast<float>(e.mouseMove.y));

                if (mouseInWorld(mPix)) {
                    const sf::Vector2f mW = mouseWorld({e.mouseMove.x, e.mouseMove.y});

                    if (mode == Mode::CREATE_ZONE && dragging) updateDrag(mW);

                    if (!dragging) updateHover(mW);

                    if (paintingRoad && placeMode == PlaceType::STRADA) {
                        const int zi = zoneAt(mW);
                        if (zi != -1) {
                            const int cx = static_cast<int>(std::floor(mW.x / tile));
                            const int cy = static_cast<int>(std::floor(mW.y / tile));
                            if (sf::Vector2i{cx, cy} != lastRoadCell) {
                                lastRoadCell = {cx, cy};
                                placeOne(zi, PlaceType::STRADA, mW);
                            }
                        }
                    }

                } else {
                    hoveredZone = -1;
                    hoveredZoneLabel.setString("");
                }
            }

            inputZonaNume.handleEvent(e);
        }

        window.clear(sf::Color(12, 12, 14));

        // world
        window.setView(worldView);
        window.draw(mapBg);

        const auto wb = worldBounds();
        const int cols = static_cast<int>(wb.width / tile);
        const int rows = static_cast<int>(wb.height / tile);

        sf::VertexArray lines(sf::Lines);
        for (int c = 0; c <= cols; ++c) {
            const float x = wb.left + static_cast<float>(c) * tile;
            lines.append(sf::Vertex({x, wb.top}, sf::Color(28, 28, 33)));
            lines.append(sf::Vertex({x, wb.top + wb.height}, sf::Color(28, 28, 33)));
        }
        for (int r = 0; r <= rows; ++r) {
            const float y = wb.top + static_cast<float>(r) * tile;
            lines.append(sf::Vertex({wb.left, y}, sf::Color(28, 28, 33)));
            lines.append(sf::Vertex({wb.left + wb.width, y}, sf::Color(28, 28, 33)));
        }
        window.draw(lines);

        // draw buildings
        for (const auto& z : zone) {
            for (const auto& b : z.buildings) {
                sf::RectangleShape r;
                r.setPosition({b.rect.left, b.rect.top});
                r.setSize({b.rect.width, b.rect.height});
                r.setFillColor(colorFor(b.type));
                r.setOutlineThickness(1.f);
                r.setOutlineColor(sf::Color(255, 255, 255, 70));
                window.draw(r);
            }
        }

        if (mode == Mode::CREATE_ZONE && dragging) window.draw(previewRect);
        if (hoveredZone != -1) window.draw(hoverBorder);

        // ui
        window.setView(uiView);

        window.draw(title);
        window.draw(help);

        inputZonaNume.draw(window);
        btnCreateZone.draw(window);
        btnCancelMode.draw(window);

        window.draw(modeLabel);
        btnPlaceStrada.draw(window);
        btnPlaceCasa.draw(window);
        btnPlaceBloc.draw(window);
        btnPlaceAdmin.draw(window);
        btnPlaceServicii.draw(window);
        btnPlaceEducatie.draw(window);
        btnPlaceVerde.draw(window);

        if (!hoveredZoneLabel.getString().isEmpty()) window.draw(hoveredZoneLabel);

        window.draw(status);

        window.display();
    }
}
