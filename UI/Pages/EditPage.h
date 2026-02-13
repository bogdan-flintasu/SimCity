#ifndef OOP_EDITPAGE_H
#define OOP_EDITPAGE_H

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <functional>

#include "../Headers/Oras.h"
#include "../UI/SideMenu.h"
#include "../Form.h"
#include "../UI/Button.h"

enum class DraftActionType {
    BUILD,
    DEMOLARE
};

struct VisualEntity {
    sf::RectangleShape shape;
    std::string nume;
    std::string tip;
    std::string parentZone;
    std::string detalii;
    double costInitial;
    ui::ToolType originalTool;
    Proiecte tipProiect;
    int id = 0;
};

struct VisualZone {
    sf::RectangleShape shape;
    std::string nume;
};

struct DraftAction {
    DraftActionType type;
    std::string categorie;
    sf::FloatRect rect;
    double cost;
    std::string nume;
    int durata;
    std::function<void()> commitAction;
};

class EditMode {
public:
    EditMode(const sf::RenderWindow& window, sf::Font& font, Oras& oras);

    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update(float dt, const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;

    bool isFinished() const { return m_isFinished; }

    const std::vector<VisualZone>& getZones() const { return m_visualZones; }
    const std::vector<VisualEntity>& getEntities() const { return m_visualEntities; }

    void startProjectSession(const std::string& category, Amanunte actiune);
    bool isProjectFinished() const { return !m_isProjectMode; }
    void resetFinishState() { m_isFinished = false; }
    void generateChallengeVisuals();
    void setChallengeMode(const bool active) { m_isChallengeActive = active; }

    bool checkGameStatus();

private:
    sf::Font& m_font;
    Oras& m_oras;

    bool m_isChallengeActive = false;

    bool m_showGameEndModal = false;
    sf::RectangleShape m_gameEndBg;
    sf::Text m_gameEndTitle;
    sf::Text m_gameEndMsg;

    std::unique_ptr<ui::Button> m_btnRestart;
    std::unique_ptr<ui::Button> m_btnExit;

    void resetGame();

    bool m_isProjectMode = false;
    std::string m_projectCategory;
    Amanunte m_projectAction;
    std::vector<DraftAction> m_draftActions;

    bool m_showSummary = false;
    sf::RectangleShape m_summaryBg;
    sf::Text m_summaryText;
    std::shared_ptr<ui::Button> m_btnConfirmSummary;
    std::shared_ptr<ui::Button> m_btnCancelSummary;

    void updateSummaryText();
    void finalizeProject();

    ui::SideMenu m_sideMenu;
    ui::Form m_form;

    std::vector<VisualZone> m_visualZones;
    std::vector<VisualEntity> m_visualEntities;

    sf::View m_worldView;
    sf::View m_uiView;
    sf::VertexArray m_gridLines;
    sf::RectangleShape m_ghost;

    bool m_isPanning = false;
    sf::Vector2i m_lastMousePos;

    bool m_isDragging = false;
    sf::Vector2f m_dragStart;
    sf::RectangleShape m_selectionRect;

    double m_calculatedRoadLength = 0;
    sf::Vector2f m_roadFinalSize;
    sf::Vector2f m_roadFinalPos;

    sf::Vector2f m_pendingPos;
    ui::ToolType m_pendingType;

    sf::Text m_infoText;
    sf::RectangleShape m_inspectorPanel;
    sf::Text m_inspectorTitle;
    sf::Text m_inspectorContent;
    VisualEntity* m_selectedEntity = nullptr;

    bool m_showConfirmModal = false;
    bool m_isFinished = false;
    sf::RectangleShape m_modalBg;
    sf::Text m_modalText;
    std::unique_ptr<ui::Button> m_btnYes;
    std::unique_ptr<ui::Button> m_btnNo;



    void initGrid();
    void initUI();
    void processFormInput();
};

#endif //OOP_EDITPAGE_H