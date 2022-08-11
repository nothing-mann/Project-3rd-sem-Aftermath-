#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"


class GameState :
    public State
{
private:
    sf::View view;
    sf::Vector2i viewGridPosition;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    PauseMenu* pmenu;

    sf::Shader core_shader;

    Player* player;
    PlayerGUI* playerGUI;

    TileMap* tileMap;

    //Functions
    void initDeferredRender();
    void initView();
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initShaders();
    void initPlayers();
    void initPlayerGUI();
    void initTileMap();
public:

    GameState(StateData* state_data);
    virtual ~GameState();

    //Functions
    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updatePauseMenuButtons();
    void updateTileMap(const float& dt);
    void update(const float& dt); // was a pure virtual function of State
    void render(sf::RenderTarget* target = nullptr); // was a pure virtual function of State
};

#endif