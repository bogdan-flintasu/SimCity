#include "EditPage.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <utility>

#include "ExceptieOras.h"
#include "../Headers/Proiect.h"
#include "../Headers/Zona.h"
#include "../Headers/Strada.h"
#include "../Headers/Casa.h"
#include "../Headers/SpatiuVerde.h"
#include "../Headers/CladireFactory.h"

constexpr float GRID_SIZE = 40.f;
struct GridSpec { int w{}; int h{}; sf::Color color; };

struct ChallengeSpecs {
    double costFix;
    std::vector<std::string> valoriDefault;
};

const std::map<ui::ToolType, ChallengeSpecs> DATA = {
    {ui::ToolType::STRADA, { 2000.0, { "Strada", "2000", "2", "0", "1" } }},
    {ui::ToolType::CASA, { 5000.0, { "Casa", "5000", "120", "2", "4" } }},
    {ui::ToolType::BLOC, { 15000.0, { "Bloc Nou", "15000", "300", "8", "100" } }},
    {ui::ToolType::FABRICA, { 30000.0, { "Uzina", "30000", "2000", "5000", "100", "0", "50", "10", "200", "0" } }},
    {ui::ToolType::SPATIU_COMERCIAL, { 20000.0, { "Mall", "20000", "1500", "30", "50", "60", "3000", "100", "5", "0" } }},
    {ui::ToolType::SPATIU_VERDE, { 5000.0, { "Parc", "5000", "200", "500", "10", "1000", "0" } }},

};

GridSpec getSpec(const ui::ToolType tip) {
    switch (tip) {
        case ui::ToolType::DELETE:              return {1, 1, sf::Color(255, 0, 0)};
        case ui::ToolType::STRADA:              return {1, 1, sf::Color(60, 60, 60)};
        case ui::ToolType::SPATIU_VERDE:        return {2, 2, sf::Color(34, 139, 34)};
        case ui::ToolType::CASA:                return {2, 2, sf::Color(50, 205, 50)};
        case ui::ToolType::BLOC:                return {3, 3, sf::Color(65, 105, 225)};
        case ui::ToolType::FABRICA:             return {4, 4, sf::Color(210, 105, 30)};
        case ui::ToolType::SPATIU_COMERCIAL:    return {3, 2, sf::Color(255, 215, 0)};
        case ui::ToolType::CLADIRE_ADMINISTRATIVA: return {3, 3, sf::Color(128, 0, 128)};
        case ui::ToolType::CLADIRE_SERVICII:       return {2, 2, sf::Color(255, 105, 180)};
        case ui::ToolType::CLADIRE_EDUCATIE:       return {3, 3, sf::Color(255, 140, 0)};
        default: return {1, 1, sf::Color::White};
    }
}

sf::Vector2f snapToGrid(sf::Vector2f pos) {
    return { std::floor(pos.x / GRID_SIZE) * GRID_SIZE, std::floor(pos.y / GRID_SIZE) * GRID_SIZE };
}

std::string formatDetails(const std::string& label, const std::string& value) { return label + ": " + value + "\n"; }
std::string boolToString(const std::string& val) { return (val == "1") ? "Da" : "Nu"; }

const std::map<ui::ToolType, std::vector<std::string>> BUILDING_RECIPES = {
    {ui::ToolType::ZONING,                 {"Nume Zona"}},
    {ui::ToolType::STRADA,                 {"Nume", "Cost Constr.", "Benzi/Sens", "Sens Unic (0/1)", "Trotuar (0/1)"}},
    {ui::ToolType::SPATIU_VERDE,           {"Nume", "Cost C.", "Cost I.", "Suprafata", "Mentenanta", "Capacitate", "Inchiriat (0/1)"}},
    {ui::ToolType::CASA,                   {"Nume", "Cost Constr.", "Suprafata", "Etaje", "Locatari"}},
    {ui::ToolType::BLOC,                   {"Nume", "Cost Constr.", "Suprafata", "Etaje", "Locatari"}},
    {ui::ToolType::FABRICA,                {"Nume", "Cost C.", "Cost I.", "Productie", "Angajati", "Automatizare", "Poluare", "Risc", "Capacitate", "Inchiriat (0/1)"}},
    {ui::ToolType::SPATIU_COMERCIAL,       {"Nume", "Cost C.", "Cost I.", "Unitati", "Angajati", "Trafic", "Profit", "Locuri Parcare", "Nivel Servicii", "Inchiriat (0/1)"}},
    {ui::ToolType::CLADIRE_ADMINISTRATIVA, {"Nume", "Cost C.", "Cost I.", "Capacitate", "Securitate", "Timp Raspuns", "Coruptie", "Inchiriat (0/1)"}},
    {ui::ToolType::CLADIRE_SERVICII,       {"Nume", "Cost C.", "Cost I.", "Capacitate", "Timp Asteptare", "Stoc", "Inchiriat (0/1)", "Coruptie", "Dotare", "Rata Rezolvare"}},
    {ui::ToolType::CLADIRE_EDUCATIE,       {"Nume", "Cost C.", "Cost I.", "Capacitate", "Nivel (1-8)", "Promovare", "Medie", "Absente", "Rating", "Inchiriat (0/1)"}}
};

EditMode::EditMode(const sf::RenderWindow& window, sf::Font& font, Oras& oras)
    : m_font(font),
      m_oras(oras),
      m_gameEndTitle(font),
      m_gameEndMsg(font),
      m_projectAction(Amanunte::DE_LA_ZERO),
      m_summaryText(font),
      m_sideMenu(font),
      m_form(font),
      m_pendingType(ui::ToolType::NONE),
      m_infoText(font),
      m_inspectorTitle(font),
      m_inspectorContent(font),
      m_modalText(font)
{
    m_isFinished = false;
    m_isProjectMode = false;
    m_worldView = window.getDefaultView();
    m_uiView = window.getDefaultView();
    initGrid();
    initUI();
}

void EditMode::initGrid() {
    m_gridLines.setPrimitiveType(sf::PrimitiveType::Lines);
    for(int i=-50; i<50; ++i) {
        const auto fi = static_cast<float>(i);
        m_gridLines.append({{fi * GRID_SIZE, -2000.f}, sf::Color(50, 50, 50)});
        m_gridLines.append({{fi * GRID_SIZE, 2000.f}, sf::Color(50, 50, 50)});
        m_gridLines.append({{-2000.f, fi * GRID_SIZE}, sf::Color(50, 50, 50)});
        m_gridLines.append({{2000.f, fi * GRID_SIZE}, sf::Color(50, 50, 50)});
    }
    m_ghost.setOutlineThickness(1.f);
    m_ghost.setOutlineColor(sf::Color::White);

    m_selectionRect.setFillColor(sf::Color(0, 255, 255, 50));
    m_selectionRect.setOutlineColor(sf::Color::Cyan);
    m_selectionRect.setOutlineThickness(2.f);
}

void EditMode::initUI() {
    m_gameEndBg.setSize({600.f, 350.f});
    m_gameEndBg.setOrigin({300.f, 175.f});
    m_gameEndBg.setPosition({640.f, 360.f});
    m_gameEndBg.setFillColor(sf::Color(20, 20, 30, 255));
    m_gameEndBg.setOutlineThickness(3.f);
    m_gameEndBg.setOutlineColor(sf::Color::White);

    m_infoText.setFont(m_font);
    m_infoText.setCharacterSize(18);
    m_infoText.setFillColor(sf::Color::White);
    m_infoText.setOutlineColor(sf::Color::Black);
    m_infoText.setOutlineThickness(1.f);

    m_inspectorPanel.setSize({300.f, 720.f});
    m_inspectorPanel.setPosition({1280.f - 300.f, 0.f});
    m_inspectorPanel.setFillColor(sf::Color(40, 40, 40, 230));
    m_inspectorPanel.setOutlineColor(sf::Color::White);
    m_inspectorPanel.setOutlineThickness(-2.f);

    m_inspectorTitle.setFont(m_font);
    m_inspectorTitle.setString("DETALII CLADIRE");
    m_inspectorTitle.setCharacterSize(22);
    m_inspectorTitle.setPosition({1280.f - 280.f, 20.f});
    m_inspectorTitle.setFillColor(sf::Color::Yellow);

    m_inspectorContent.setFont(m_font);
    m_inspectorContent.setCharacterSize(16);
    m_inspectorContent.setPosition({1280.f - 280.f, 60.f});
    m_inspectorContent.setFillColor(sf::Color::White);

    m_modalBg.setSize({400.f, 200.f});
    m_modalBg.setOrigin({200.f, 100.f});
    m_modalBg.setPosition({640.f, 360.f});
    m_modalBg.setFillColor(sf::Color(50, 50, 50, 255));
    m_modalBg.setOutlineThickness(2.f);
    m_modalBg.setOutlineColor(sf::Color::White);

    m_modalText.setFont(m_font);
    m_modalText.setString("Esti sigur ca vrei sa finalizezi orasul?\nNu vei mai putea modifica cladirile.");
    m_modalText.setCharacterSize(18);
    const sf::FloatRect tb = m_modalText.getLocalBounds();
    m_modalText.setOrigin({tb.size.x/2.f, tb.size.y/2.f});
    m_modalText.setPosition({640.f, 320.f});

    m_btnYes = std::make_unique<ui::Button>(sf::Vector2f{550.f, 400.f}, sf::Vector2f{80.f, 40.f}, "DA", m_font, sf::Color(0, 150, 0));
    m_btnYes->setCallback([this](){ m_isFinished = true; });

    m_btnNo = std::make_unique<ui::Button>(sf::Vector2f{650.f, 400.f}, sf::Vector2f{80.f, 40.f}, "NU", m_font, sf::Color(150, 0, 0));
    m_btnNo->setCallback([this](){ m_showConfirmModal = false; });

    m_btnConfirmSummary = std::make_shared<ui::Button>(sf::Vector2f{500.f, 500.f}, sf::Vector2f{120.f, 40.f}, "CONFIRMA", m_font, sf::Color(0, 200, 0));
    m_btnConfirmSummary->setCallback([this](){ finalizeProject(); });

    m_btnCancelSummary = std::make_shared<ui::Button>(sf::Vector2f{660.f, 500.f}, sf::Vector2f{120.f, 40.f}, "ANULEAZA", m_font, sf::Color(200, 0, 0));
    m_btnCancelSummary->setCallback([this](){ m_showSummary = false; });

    m_btnRestart = std::make_unique<ui::Button>(
        sf::Vector2f{540.f, 450.f}, sf::Vector2f{160.f, 50.f},
        "DA / PLAY AGAIN", m_font, sf::Color(0, 150, 0)
    );
    m_btnRestart->setCallback([this] { resetGame(); });

    m_btnExit = std::make_unique<ui::Button>(
        sf::Vector2f{740.f, 450.f}, sf::Vector2f{160.f, 50.f},
        "NU / EXIT", m_font, sf::Color(150, 0, 0)
    );
    m_btnExit->setCallback([] {
        std::exit(0);
    });
}

static bool isToolAllowedForProject(const ui::ToolType tool, const std::string& category, const Amanunte actiune) {
    if (tool == ui::ToolType::NONE || tool == ui::ToolType::FINALIZE || tool == ui::ToolType::ZONING) return true;

    if (actiune == Amanunte::DEMOLARE) {
        return (tool == ui::ToolType::DELETE);
    }

    if (actiune == Amanunte::DE_LA_ZERO) {
        if (tool == ui::ToolType::DELETE) return false;
        if (category == "Infrastructura") return (tool == ui::ToolType::STRADA);
        if (category == "Rezidential") return (tool == ui::ToolType::CASA || tool == ui::ToolType::BLOC);
        if (category == "Public") return (tool != ui::ToolType::STRADA && tool != ui::ToolType::CASA && tool != ui::ToolType::BLOC);
    }

    return true;
}

void EditMode::startProjectSession(const std::string& category, const Amanunte actiune) {
    if (m_oras.get_proiect_implementat()) {
        std::cout << "\nAi implementat deja un proiect luna aceasta!\n";
        std::cout << "Asteapta simularea lunii urmatoare pentru a construi din nou.\n";

        m_isProjectMode = false;
        m_isFinished = true;
        return;
    }
    m_isProjectMode = true;
    m_projectCategory = category;
    m_projectAction = actiune;
    m_draftActions.clear();
    m_showSummary = false;
    m_isFinished = false;

    m_sideMenu.resetSelection();
    m_pendingType = ui::ToolType::NONE;
    m_selectedEntity = nullptr;
    m_showConfirmModal = false;

    m_summaryBg.setSize({600.f, 400.f});
    m_summaryBg.setOrigin({300.f, 200.f});
    m_summaryBg.setFillColor(sf::Color(30, 30, 40, 250));
    m_summaryBg.setOutlineColor(sf::Color::Yellow);
    m_summaryBg.setOutlineThickness(2.f);

    m_summaryText.setFont(m_font);
    m_summaryText.setCharacterSize(20);
    m_summaryText.setFillColor(sf::Color::White);

    std::cout << ">>> EditMode pornit in regim PROIECT: " << category << "\n";
}

void EditMode::processFormInput() {
    m_form.hide();

    std::vector<std::string> inputs = m_form.getValues();
    if (inputs.empty()) {
        m_pendingType = ui::ToolType::NONE;
        return;
    }

    const std::string& nume = inputs[0];

    if (m_pendingType == ui::ToolType::ZONING) {
        VisualZone vz; vz.nume = nume; vz.shape = m_selectionRect;
        vz.shape.setFillColor(sf::Color(0, 0, 200, 40));
        vz.shape.setOutlineColor(sf::Color::Blue);
        m_visualZones.push_back(vz);
        m_oras.adauga_zona(Zona(nume));
        m_pendingType = ui::ToolType::NONE;
        return;
    }

    std::string targetZone;
    sf::Vector2f checkPos = (m_pendingType == ui::ToolType::STRADA) ? m_roadFinalPos : m_pendingPos;
    for(const auto& vz : m_visualZones) {
        if(vz.shape.getGlobalBounds().contains(checkPos)) {
            targetZone = vz.nume;
            break;
        }
    }

    if (targetZone.empty() || !m_oras.cautare_zona(targetZone)) {
        std::cout << "Trebuie sa construiesti intr-o zona existenta!\n";
        m_pendingType = ui::ToolType::NONE;
        return;
    }

    try {
        double costReal = std::stod(inputs[1]);
        double costDePlata = m_isProjectMode ? costReal : 0.0;
        constexpr auto actiuneConstructie = Amanunte::DE_LA_ZERO;

        if (m_oras.get_buget() < costDePlata) {
            throw ExceptieBugetInsuficient(m_oras.get_buget(), costDePlata);
        }

        Proiecte tipBackend;
        std::stringstream ss;

        if (m_pendingType == ui::ToolType::STRADA) {
            tipBackend = Proiecte::STRADA;
            Proiect p(nume, tipBackend, actiuneConstructie, static_cast<int>(costDePlata), 0);

            auto s = CladireFactory::creeaza_strada(inputs, m_calculatedRoadLength);
            m_oras.implementare_proiect_stradal(p, *s, targetZone);

            ss << formatDetails("Benzi", inputs[2])
               << formatDetails("Trotuar", (inputs[4] == "1" ? "Da" : "Nu"));
        }
        else if (m_pendingType == ui::ToolType::CASA || m_pendingType == ui::ToolType::BLOC) {
            tipBackend = Proiecte::REZIDENTIAL;
            Proiect p(nume, tipBackend, actiuneConstructie, static_cast<int>(costDePlata), 0);

            auto rezid = CladireFactory::creeaza_rezidentiala(m_pendingType, inputs);
            m_oras.implementare_proiect_rezidential(p, std::move(rezid), targetZone);

            ss << formatDetails("Etaje", inputs[3])
               << formatDetails("Locatari", inputs[4]);
        }
        else {
            tipBackend = Proiecte::PUBLIC;
            Proiect p(nume, tipBackend, actiuneConstructie, static_cast<int>(costDePlata), 0);

            auto publica = CladireFactory::creeaza_publica(m_pendingType, inputs);
            m_oras.implementare_proiect_public(p, std::move(publica), targetZone);

            ss << formatDetails("Info", "Proiect Public");
        }

        VisualEntity ve;
        if (m_pendingType == ui::ToolType::STRADA) {
            ve.shape.setPosition(m_roadFinalPos);
            ve.shape.setSize(m_roadFinalSize);
        } else {
            auto spec = getSpec(m_pendingType);
            ve.shape.setPosition(m_pendingPos);
            ve.shape.setSize({static_cast<float>(spec.w) * GRID_SIZE, static_cast<float>(spec.h) * GRID_SIZE});
        }

        ve.shape.setFillColor(getSpec(m_pendingType).color);
        ve.nume = nume;
        ve.parentZone = targetZone;
        ve.costInitial = costReal;
        ve.tipProiect = tipBackend;
        ve.detalii = "Zona: " + targetZone + "\n" + ss.str();

        if (Zona* z = m_oras.cautare_zona(targetZone)) {
            if (m_pendingType == ui::ToolType::STRADA) ve.id = z->get_ultimul_id_strada();
            else if (tipBackend == Proiecte::REZIDENTIAL) ve.id = z->get_ultimul_id_rezidentiala();
            else ve.id = z->get_ultimul_id_publica();
        }

        m_visualEntities.push_back(ve);

        if (m_isProjectMode) {
            DraftAction act;
            act.type = DraftActionType::BUILD;
            act.nume = nume;
            act.cost = costReal;
            act.durata = 30;
            act.rect = ve.shape.getGlobalBounds();
            act.commitAction = nullptr;
            m_draftActions.push_back(act);
        }

    } catch (const ExceptieBugetInsuficient& e) {
        std::stringstream errorSs;
        errorSs << "FONDURI INSUFICIENTE!\n"
                << "Cost proiect: " << std::fixed << std::setprecision(0) << e.getCost() << " RON\n"
                << "Iti lipsesc: " << e.getLipsa() << " RON";

        m_modalText.setString(errorSs.str());
        m_showConfirmModal = true;
    } catch (const std::exception& e) {
        std::cout << "Eroare neprevazuta: " << e.what() << "\n";
    }

    m_pendingType = ui::ToolType::NONE;
}

void EditMode::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (m_showGameEndModal) {
        window.setView(m_uiView);
        if (m_btnRestart->handleEvent(event, window)) return;
        if (m_btnExit->handleEvent(event, window)) return;
        return;
    }

    if (m_showSummary) {
        window.setView(m_uiView);
        if (m_btnCancelSummary->handleEvent(event, window)) return;
        if (m_btnConfirmSummary->handleEvent(event, window)) return;
        return;
    }

    if (m_showConfirmModal) {
        window.setView(m_uiView);
        if (m_btnYes->handleEvent(event, window)) return;
        if (m_btnNo->handleEvent(event, window)) return;
        return;
    }

    if (m_form.isActive()) {
        m_form.handleEvent(event);
        if (m_form.isConfirmed()) processFormInput();
        return;
    }

    if (m_sideMenu.getActiveTool() == ui::ToolType::FINALIZE) {
        m_sideMenu.resetSelection();
        if (m_isProjectMode && !m_draftActions.empty()) {
            updateSummaryText();
            m_showSummary = true;
        } else {
            m_showConfirmModal = true;
        }
        return;
    }

    if (const auto* k = event.getIf<sf::Event::KeyPressed>()) {
        if (k->code == sf::Keyboard::Key::Tab) m_sideMenu.toggle();
        if (k->code == sf::Keyboard::Key::Escape) {
            m_sideMenu.resetSelection(); m_isDragging = false; m_ghost.setSize({0, 0}); m_selectedEntity = nullptr; m_pendingType = ui::ToolType::NONE;
        }
    }

    m_sideMenu.handleEvent(event, window);

    const sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    const sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, m_worldView);
    bool mouseOverUI = (pixelPos.x < 250) || (m_selectedEntity != nullptr && pixelPos.x > 1280 - 300);

    if (const auto* mPressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mPressed->button == sf::Mouse::Button::Right) {
             if (m_sideMenu.getActiveTool() != ui::ToolType::NONE) {
                 m_sideMenu.resetSelection(); m_isDragging = false; m_ghost.setSize({0,0}); m_selectedEntity = nullptr; m_pendingType = ui::ToolType::NONE;
             } else { m_isPanning = true; m_lastMousePos = sf::Mouse::getPosition(window); }
        }
        else if (mPressed->button == sf::Mouse::Button::Left) {
            if (mouseOverUI) return;

            const sf::Vector2f snap = snapToGrid(worldPos);
            const ui::ToolType tool = m_sideMenu.getActiveTool();

            if (m_isProjectMode) {
                if (!isToolAllowedForProject(tool, m_projectCategory, m_projectAction)) {
                    m_sideMenu.resetSelection(); m_pendingType = ui::ToolType::NONE; return;
                }
            }

            if (tool == ui::ToolType::DELETE) {
                // 1. Încercăm să ștergem o clădire/entitate
                auto itEntity = std::ranges::find_if(m_visualEntities, [&](const VisualEntity& ve) {
                    return ve.shape.getGlobalBounds().contains(worldPos);
                });

                if (itEntity != m_visualEntities.end()) {
                    int pId = itEntity->id;
                    std::string pNume = itEntity->nume;
                    std::string pZona = itEntity->parentZone;
                    Proiecte pTip = itEntity->tipProiect;
                    double pCostInitial = itEntity->costInitial;
                    sf::FloatRect pRect = itEntity->shape.getGlobalBounds();

                    if (m_isProjectMode) {
                        bool permis = true;
                        if (m_projectCategory == "Infrastructura" && pTip != Proiecte::STRADA) permis = false;
                        if (m_projectCategory == "Rezidential" && pTip != Proiecte::REZIDENTIAL) permis = false;
                        if (m_projectCategory == "Public" && pTip != Proiecte::PUBLIC) permis = false;

                        if (!permis) {
                            std::cout << "Nu poti demola aceasta cladire in proiectul curent!\n";
                            return;
                        }

                        DraftAction act;
                        act.type = DraftActionType::DEMOLARE;
                        act.nume = pNume;
                        act.cost = pCostInitial * 0.25;
                        act.rect = pRect;

                        act.commitAction = [=, this]() {
                            try {
                                Proiect p(pNume, pTip, Amanunte::DEMOLARE, static_cast<int>(pCostInitial), pId);
                                if (pTip == Proiecte::STRADA) {
                                    if (Zona* z = m_oras.cautare_zona(pZona)) {
                                        if (auto* s = z->get_strada_dupa_id(pId))
                                            m_oras.implementare_proiect_stradal(p, *s, pZona);
                                        else throw ExceptieIDInexistent(pId);
                                    }
                                }
                                else if (pTip == Proiecte::REZIDENTIAL)
                                    m_oras.implementare_proiect_rezidential(p, nullptr, pZona);
                                else if (pTip == Proiecte::PUBLIC)
                                    m_oras.implementare_proiect_public(p, nullptr, pZona);
                            } catch (const ExceptieIDInexistent& e) {
                                std::cout << "Eroare ID la commit: " << e.getID() << "\n";
                            }
                        };
                        m_draftActions.push_back(act);
                    } else {
                        Proiect p(pNume, pTip, Amanunte::DEMOLARE, 0, pId);
                        if (pTip == Proiecte::STRADA) {
                            if (Zona* z = m_oras.cautare_zona(pZona)) {
                                if (auto* s = z->get_strada_dupa_id(pId))
                                    m_oras.implementare_proiect_stradal(p, *s, pZona);
                            }
                        }
                        else if (pTip == Proiecte::REZIDENTIAL) m_oras.implementare_proiect_rezidential(p, nullptr, pZona);
                        else if (pTip == Proiecte::PUBLIC) m_oras.implementare_proiect_public(p, nullptr, pZona);
                    }
                    m_visualEntities.erase(itEntity);
                    m_selectedEntity = nullptr;
                }
                else {
                    // 2. DACĂ NU E CLĂDIRE, verificăm dacă e o ZONĂ
                    auto itZone = std::ranges::find_if(m_visualZones, [&](const VisualZone& vz) {
                        return vz.shape.getGlobalBounds().contains(worldPos);
                    });

                    if (itZone != m_visualZones.end()) {
                        std::string numeZona = itZone->nume;
                        try {
                            if (m_oras.sterge_zona(numeZona)) {
                                std::cout << "Zona stearsa: " << numeZona << "\n";
                                m_visualZones.erase(itZone);
                                std::erase_if(m_visualEntities, [&](const VisualEntity& ve) {
                                    return ve.parentZone == numeZona;
                                });
                            }
                        } catch (const ExceptieZonaInexistenta& e) {
                            std::cout << "Eroare: " << e.getNumeZona() << " nu a fost gasita.\n";
                        }
                    }
                }
            }
            else if (tool == ui::ToolType::ZONING || tool == ui::ToolType::STRADA) {
                m_isDragging = true; m_dragStart = snap;
                m_selectionRect.setPosition(m_dragStart); m_selectionRect.setSize({0, 0});
                if (tool == ui::ToolType::STRADA) { m_selectionRect.setFillColor(sf::Color(60, 60, 60, 150)); m_selectionRect.setOutlineColor(sf::Color::White); }
                else { m_selectionRect.setFillColor(sf::Color(0, 255, 255, 50)); m_selectionRect.setOutlineColor(sf::Color::Cyan); }
                m_selectedEntity = nullptr;
            }
            else if (tool != ui::ToolType::NONE) {
                const auto spec = getSpec(tool);
                const sf::FloatRect r(snap, {static_cast<float>(spec.w) * GRID_SIZE, static_cast<float>(spec.h) * GRID_SIZE});
                sf::FloatRect colR = r; colR.position.x += 2.5f; colR.position.y += 2.5f; colR.size.x -= 5.0f; colR.size.y -= 5.0f;
                bool ocupat = false;
                for(const auto& ve : m_visualEntities) if(ve.shape.getGlobalBounds().findIntersection(colR)) ocupat = true;
                bool inZona = false;
                for(const auto& vz : m_visualZones) if(vz.shape.getGlobalBounds().contains(snap)) inZona = true;

                if(!ocupat && inZona) {
                    m_pendingPos = snap;
                    m_pendingType = tool;
                    if(BUILDING_RECIPES.contains(m_pendingType)) {
                        m_form.configure(BUILDING_RECIPES.at(m_pendingType));
                        if (m_isChallengeActive) {
                            if (DATA.contains(m_pendingType)) m_form.fillInputs(DATA.at(m_pendingType).valoriDefault);
                        }
                        m_form.show();
                    }
                }
            }
            else {
                m_selectedEntity = nullptr;
                for (auto& ve : m_visualEntities) {
                    if (ve.shape.getGlobalBounds().contains(worldPos)) {
                        m_selectedEntity = &ve;
                        m_inspectorTitle.setString(ve.nume);
                        m_inspectorContent.setString(ve.detalii);
                        break;
                    }
                }
            }
        }
    }

    if (const auto* mRel = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (mRel->button == sf::Mouse::Button::Right) m_isPanning = false;
        if (mRel->button == sf::Mouse::Button::Left && m_isDragging) {
            m_isDragging = false;
            if (mouseOverUI) return;
            if (const ui::ToolType tool = m_sideMenu.getActiveTool(); tool == ui::ToolType::ZONING) {
                if(std::abs(m_selectionRect.getSize().x) > 10) {
                    m_pendingType = ui::ToolType::ZONING;
                    m_form.configure(BUILDING_RECIPES.at(m_pendingType));
                    m_form.show();
                }
            }
            else if (tool == ui::ToolType::STRADA) {
                if (const sf::Vector2f size = m_selectionRect.getSize(); std::abs(size.x) > 5 || std::abs(size.y) > 5) {
                    m_roadFinalSize = size;
                    m_roadFinalPos = m_selectionRect.getPosition();
                    float pixelLen = std::max(std::abs(size.x), std::abs(size.y));
                    int blocks = static_cast<int>(std::round(pixelLen / GRID_SIZE));
                    m_calculatedRoadLength = blocks * 5.0;
                    m_pendingType = ui::ToolType::STRADA;
                    m_form.configure(BUILDING_RECIPES.at(m_pendingType));
                    m_form.show();
                }
            }
        }
    }

    if (const auto* mMoved = event.getIf<sf::Event::MouseMoved>()) {
        const sf::Vector2i curr = mMoved->position;
        if(m_isPanning) {
            const sf::Vector2f d = window.mapPixelToCoords(m_lastMousePos, m_worldView) - window.mapPixelToCoords(curr, m_worldView);
            m_worldView.move(d); m_lastMousePos = curr;
        }
        if(m_isDragging) {
            const sf::Vector2f currWorld = window.mapPixelToCoords(curr, m_worldView);
            if (m_sideMenu.getActiveTool() == ui::ToolType::ZONING) {
                m_selectionRect.setSize({currWorld.x - m_dragStart.x, currWorld.y - m_dragStart.y});
            } else if (m_sideMenu.getActiveTool() == ui::ToolType::STRADA) {
                float dx = std::abs(currWorld.x - m_dragStart.x);
                float dy = std::abs(currWorld.y - m_dragStart.y);
                if (dx > dy) m_selectionRect.setSize({currWorld.x - m_dragStart.x, GRID_SIZE});
                else m_selectionRect.setSize({GRID_SIZE, currWorld.y - m_dragStart.y});
            }
        }
    }
}

void EditMode::update(float dt, const sf::RenderWindow& window) {
    if (!m_showConfirmModal) {
        m_sideMenu.update(dt);
    }

    const sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    const sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, m_worldView);

    ui::ToolType t = m_sideMenu.getActiveTool();

    if (m_isProjectMode && !isToolAllowedForProject(t, m_projectCategory, m_projectAction)) {
        t = ui::ToolType::NONE;
    }

    bool isBuildingTool = (t != ui::ToolType::NONE && t != ui::ToolType::ZONING && t != ui::ToolType::STRADA && t != ui::ToolType::DELETE && t != ui::ToolType::FINALIZE);
    if(isBuildingTool && !m_form.isActive() && !m_showConfirmModal && !m_showSummary) {
        auto spec = getSpec(t);
        m_ghost.setSize({static_cast<float>(spec.w) * GRID_SIZE, static_cast<float>(spec.h) * GRID_SIZE});
        m_ghost.setPosition(snapToGrid(worldPos));
        sf::FloatRect ghostCol = m_ghost.getGlobalBounds();
        ghostCol.position.x += 2.5f; ghostCol.position.y += 2.5f; ghostCol.size.x -= 5.0f; ghostCol.size.y -= 5.0f;
        bool coll = false;
        for(const auto& v:m_visualEntities) if(v.shape.getGlobalBounds().findIntersection(ghostCol)) coll=true;
        m_ghost.setFillColor(coll ? sf::Color(255,0,0,100) : sf::Color(spec.color.r, spec.color.g, spec.color.b, 150));
    }
    else if (t == ui::ToolType::DELETE && !m_showConfirmModal) {
        m_ghost.setSize({GRID_SIZE, GRID_SIZE}); m_ghost.setPosition(snapToGrid(worldPos)); m_ghost.setFillColor(sf::Color(255, 0, 0, 150));
    } else {
        m_ghost.setSize({0,0});
    }

    std::string hoverInfo;
    if (!m_showConfirmModal) {
        for (const auto& ve : m_visualEntities) { if (ve.shape.getGlobalBounds().contains(worldPos)) { hoverInfo = "CLADIRE: " + ve.nume; break; } }
        if (hoverInfo.empty()) { for (const auto& vz : m_visualZones) { if (vz.shape.getGlobalBounds().contains(worldPos)) { hoverInfo = "ZONA: " + vz.nume; break; } } }
    }
    m_infoText.setString(hoverInfo);
    float offX = (m_selectedEntity != nullptr) ? 320.f : 20.f;
    sf::FloatRect textBounds = m_infoText.getLocalBounds();
    m_infoText.setPosition({1280.f - textBounds.size.x - offX, 720.f - textBounds.size.y - 20.f});
}

void EditMode::finalizeProject() {
    int successCount = 0;
    for (const auto& act : m_draftActions) {
        if (act.type == DraftActionType::DEMOLARE && act.commitAction) {
            try {
                act.commitAction();
                successCount++;
            } catch (const std::exception& e) {
                std::cerr << "Eroare demolare: " << e.what() << "\n";
            }
        } else {
            successCount++;
        }
    }

    m_oras.set_proiect_implementat();
    m_showSummary = false;
    m_draftActions.clear();
    m_sideMenu.resetSelection();
    m_isProjectMode = false;
    m_isFinished = true;
    std::cout << ">>> Proiect Finalizat cu succes! Numar actiuni proiect:" << successCount <<"\n";
}

void EditMode::updateSummaryText() {
    double totalCost = 0;
    int timeDays = 0;

    for(const auto& act : m_draftActions) {
        totalCost += act.cost;
        timeDays += act.durata;
    }

    std::stringstream ss;
    ss << "REZUMAT PROIECT (" << m_projectCategory << ")\n\n";
    ss << "--- STATISTICI MANDAT ---\n";
    ss << "Luna curenta: " << m_oras.get_luna_curenta() << " / 48\n";
    if (m_oras.get_luni_excelenta() > 0) {
        ss << "Streak Fericire (>80%): " << m_oras.get_luni_excelenta() << " / 6 luni\n";
    } else {
        ss << "Streak Fericire: 0 / 6\n";
    }
    ss << "-------------------------\n\n";
    ss << "Actiuni: " << m_draftActions.size() << "\n";
    ss << "Cost Total: " << std::fixed << std::setprecision(2) << totalCost << " RON\n";
    ss << "Timp: " << timeDays << " Zile\n\n";
    ss << "Buget Actual: " << m_oras.get_buget() << "\n";
    ss << "Buget Final:  " << (m_oras.get_buget() - totalCost) << "\n";

    if(m_oras.get_buget() < totalCost) {
        ss << "\n[!] FONDURI INSUFICIENTE!";
        m_summaryText.setFillColor(sf::Color::Red);
    } else {
        m_summaryText.setFillColor(sf::Color::White);
    }

    m_summaryText.setString(ss.str());

    const sf::FloatRect b = m_summaryText.getLocalBounds();
    m_summaryText.setOrigin({b.size.x / 2.f, b.size.y / 2.f});
    m_summaryText.setPosition({640.f, 320.f});
}

void EditMode::draw(sf::RenderWindow& window) const {
    window.setView(m_worldView);
    window.draw(m_gridLines);
    for(const auto& vz:m_visualZones) window.draw(vz.shape);
    if(m_isDragging) window.draw(m_selectionRect);
    for(const auto& ve:m_visualEntities) {
        window.draw(ve.shape);
        if(&ve == m_selectedEntity) {
            sf::RectangleShape outline = ve.shape;
            outline.setFillColor(sf::Color::Transparent);
            outline.setOutlineColor(sf::Color::Yellow);
            outline.setOutlineThickness(3.f);
            window.draw(outline);
        }
    }
    window.draw(m_ghost);

    window.setView(m_uiView);
    m_sideMenu.draw(window);
    m_form.draw(window);
    if (m_selectedEntity != nullptr) {
        window.draw(m_inspectorPanel);
        window.draw(m_inspectorTitle);
        window.draw(m_inspectorContent);
    }
    if (!m_infoText.getString().isEmpty()) window.draw(m_infoText);

    if (m_showConfirmModal) {
        sf::RectangleShape overlay({1280.f, 720.f});
        overlay.setFillColor(sf::Color(0,0,0,150));
        window.draw(overlay);
        window.draw(m_modalBg);
        window.draw(m_modalText);
        m_btnYes->draw(window);
        m_btnNo->draw(window);
    }

    if (m_showSummary) {
        sf::RectangleShape overlay({1280.f, 720.f});
        overlay.setFillColor(sf::Color(0,0,0,200));
        window.draw(overlay);

        sf::RectangleShape bg = m_summaryBg;
        bg.setPosition({640.f, 360.f});
        window.draw(bg);

        window.draw(m_summaryText);

        m_btnConfirmSummary->draw(window);
        m_btnCancelSummary->draw(window);
    }

    if (m_showGameEndModal) {
        sf::RectangleShape overlay({1280.f, 720.f});
        overlay.setFillColor(sf::Color(0,0,0,220));
        window.draw(overlay);

        window.draw(m_gameEndBg);
        window.draw(m_gameEndTitle);
        window.draw(m_gameEndMsg);

        m_btnRestart->draw(window);
        m_btnExit->draw(window);
    }
}

bool EditMode::checkGameStatus() {
    const int stare = m_oras.get_stare_joc();

    if (stare == 0) return false;

    m_showGameEndModal = true;

    std::string titlu;
    std::string mesaj;
    std::string btnYesText = "DA";
    std::string btnNoText = "NU";
    sf::Color outlineCol;

    if (stare == 1) {
        titlu = "VICTORIE!";
        mesaj = "Ai castigat admiratia locuitorilor!\nOrasul te iubeste.\n\nCe doresti sa faci mai departe?";
        btnYesText = "Joaca din nou";
        btnNoText = "Iesi";
        outlineCol = sf::Color::Green;
        m_gameEndTitle.setFillColor(sf::Color::Green);
    }
    else if (stare == -1 && m_oras.get_fericire() <= 0.01) {
        titlu = "AI FOST DEMIS!";
        mesaj = "Cetatenii s-au revoltat (Fericire 0%)!\nVor avea loc alegeri anticipate.\n\nMai candidezi?";
        outlineCol = sf::Color::Red;
        m_gameEndTitle.setFillColor(sf::Color::Red);
    }
    else {
        titlu = "MANDAT TERMINAT";
        mesaj = "Mandatul s-a terminat fara rezultate notabile.\nVor fi din nou alegeri.\n\nMai candidezi?";
        outlineCol = sf::Color::Red;
        m_gameEndTitle.setFillColor(sf::Color(255, 100, 0));
    }

    m_gameEndBg.setOutlineColor(outlineCol);
    m_gameEndTitle.setString(titlu);
    m_gameEndMsg.setString(mesaj);
    m_btnRestart->setText(btnYesText);
    m_btnExit->setText(btnNoText);

    float centerX = 640.f;
    float centerY = 360.f;

    const sf::FloatRect tbTitle = m_gameEndTitle.getLocalBounds();
    m_gameEndTitle.setOrigin({
        tbTitle.position.x + tbTitle.size.x / 2.f,
        tbTitle.position.y + tbTitle.size.y / 2.f
    });
    m_gameEndTitle.setPosition({centerX, centerY - 80.f});

    const sf::FloatRect tbMsg = m_gameEndMsg.getLocalBounds();
    m_gameEndMsg.setOrigin({
        tbMsg.position.x + tbMsg.size.x / 2.f,
        tbMsg.position.y + tbMsg.size.y / 2.f
    });
    m_gameEndMsg.setPosition({centerX, centerY});

    m_btnRestart->setPosition({centerX - 120.f - 80.f, centerY + 100.f - 25.f});
    m_btnExit->setPosition({centerX + 120.f - 80.f, centerY + 100.f - 25.f});

    return true;
}

void EditMode::resetGame() {
    std::cout << ">>> RESETARE JOC <<<\n";

    m_oras.reset();

    m_visualEntities.clear();
    m_visualZones.clear();
    m_draftActions.clear();
    m_showGameEndModal = false;
    m_isProjectMode = false;
    m_pendingType = ui::ToolType::NONE;
    m_worldView.setCenter({0, 0});
}

void EditMode::generateChallengeVisuals() {
    m_visualEntities.clear();
    m_visualZones.clear();

    constexpr float G = 40.f;
    constexpr float offX = 320.f;
    constexpr float offY = 40.f;

    auto createVisualFromBackend = [&](int idRecept, const std::string& nume, const std::string& zonaNume,
                                       Proiecte tip, int gx, int gy, int gw, int gh, sf::Color col, const std::string& extraDet) {

        float pixelX = offX + static_cast<float>(gx) * G;
        float pixelY = offY + static_cast<float>(gy) * G;

        VisualEntity ve;
        ve.id = idRecept;
        ve.nume = nume;
        ve.parentZone = zonaNume;
        ve.tipProiect = tip;
        ve.costInitial = 0;

        ve.shape.setPosition({pixelX, pixelY});
        ve.shape.setSize({static_cast<float>(gw) * G, static_cast<float>(gh) * G});
        ve.shape.setFillColor(col);

        ve.detalii = "ID Backend: " + std::to_string(idRecept) + "\n" + extraDet;

        m_visualEntities.push_back(ve);
    };

    if (Zona* zInd = m_oras.cautare_zona("Zona Industriala")) {
        VisualZone vz; vz.nume = "Zona Industriala";
        vz.shape.setPosition({offX + 16*G, offY}); vz.shape.setSize({14*G, 24*G});
        vz.shape.setFillColor(sf::Color(80,20,20,100)); vz.shape.setOutlineColor(sf::Color::Red); vz.shape.setOutlineThickness(2.f);
        m_visualZones.push_back(vz);

        for (const auto& c : zInd->get_cladiri_publice()) {
            const int id = c->get_ID();

            if (std::string nume = c->get_nume(); nume == "Otelaria Veche")
                createVisualFromBackend(id, nume, "Zona Industriala", Proiecte::PUBLIC, 21, 1, 5, 5, sf::Color(139, 69, 19), "Pierderi Mari");
            else if (nume == "Textila Falimentara")
                createVisualFromBackend(id, nume, "Zona Industriala", Proiecte::PUBLIC, 21, 9, 4, 3, sf::Color(160, 82, 45), "Faliment");
            else if (nume == "Uzina Chimica")
                createVisualFromBackend(id, nume, "Zona Industriala", Proiecte::PUBLIC, 22, 16, 4, 4, sf::Color(100, 0, 100), "Risc Mare");
        }

        for (const auto& s : zInd->get_strazi()) {
            int id = s.get_ID();
            const std::string& nume = s.get_nume();

            if (nume == "Bd. Fumului")
                createVisualFromBackend(id, nume, "Zona Industriala", Proiecte::STRADA, 18, 0, 2, 24, sf::Color(40,40,40), "");
            else if (nume == "Str. Depozitului")
                createVisualFromBackend(id, nume, "Zona Industriala", Proiecte::STRADA, 16, 6, 14, 2, sf::Color(50,50,50), "");
        }
    }

    if (Zona* zRez = m_oras.cautare_zona("Cartierul Speranta")) {
        VisualZone vz; vz.nume = "Cartierul Speranta";
        vz.shape.setPosition({offX, offY + 8*G}); vz.shape.setSize({16*G, 16*G});
        vz.shape.setFillColor(sf::Color(0,100,0,80)); vz.shape.setOutlineColor(sf::Color::Green); vz.shape.setOutlineThickness(2.f);
        m_visualZones.push_back(vz);

        for(const auto& s : zRez->get_strazi()) {
            if (s.get_nume() == "Bd. Tineretului")
                createVisualFromBackend(s.get_ID(), s.get_nume(), "Cartierul Speranta", Proiecte::STRADA, 7, 8, 2, 16, sf::Color(60,60,60), "");
            else if (s.get_nume() == "Aleea Blocului")
                createVisualFromBackend(s.get_ID(), s.get_nume(), "Cartierul Speranta", Proiecte::STRADA, 0, 14, 7, 1, sf::Color(70,70,70), "");
        }

        for(const auto& c : zRez->get_cladiri_rezidentiale()) {
            int id = c->get_ID();
            std::string n = c->get_nume();

            if (n.find("Bloc") != std::string::npos) {
                int val = std::stoi(n.substr(n.find_last_of(' ') + 1));

                int gx = (val <= 2) ? 1 : (val <= 5 ? 10 : 4);
                int gy = (val == 1) ? 9 : (val == 2 ? 16 : (val == 3 ? 9 : (val == 4 ? 13 : (val == 5 ? 17 : 9))));

                createVisualFromBackend(id, n, "Cartierul Speranta", Proiecte::REZIDENTIAL, gx, gy, 3, 3, sf::Color(65, 105, 225), "Bloc Parasit");
            }
            else if (n.find("Casa") != std::string::npos) {
                if (n.find('1') != std::string::npos)
                    createVisualFromBackend(id, n, "Cartierul Speranta", Proiecte::REZIDENTIAL, 4, 16, 2, 2, sf::Color(50, 205, 50), "");
                else if (n.find('2') != std::string::npos)
                    createVisualFromBackend(id, n, "Cartierul Speranta", Proiecte::REZIDENTIAL, 13, 21, 2, 2, sf::Color(50, 205, 50), "");
            }
        }
    }

    if (Zona* zCom = m_oras.cautare_zona("Centrul Vechi")) {
        VisualZone vz; vz.nume = "Centrul Vechi";
        vz.shape.setPosition({offX, offY}); vz.shape.setSize({16*G, 8*G});
        vz.shape.setFillColor(sf::Color(180,180,0,80)); vz.shape.setOutlineColor(sf::Color::Yellow); vz.shape.setOutlineThickness(2.f);
        m_visualZones.push_back(vz);

        for(const auto& s : zCom->get_strazi()) {
            if (s.get_nume() == "Calea Victoriei")
                createVisualFromBackend(s.get_ID(), s.get_nume(), "Centrul Vechi", Proiecte::STRADA, 0, 6, 16, 2, sf::Color(60,60,60), "");
        }

        for(const auto& c : zCom->get_cladiri_publice()) {
            int id = c->get_ID();
            std::string n = c->get_nume();

            if (n == "Mall Parasit")
                createVisualFromBackend(id, n, "Centrul Vechi", Proiecte::PUBLIC, 1, 1, 4, 3, sf::Color(255, 215, 0), "Pierdere");
            else if (n == "Piata Centrala")
                createVisualFromBackend(id, n, "Centrul Vechi", Proiecte::PUBLIC, 10, 2, 3, 2, sf::Color(255, 220, 0), "Profit Mic");
        }
    }

    std::cout << "[UI] Challenge Visuals LINKATE CORECT cu Backend-ul.\n";
}