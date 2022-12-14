#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"


class Game
{
private:
	
	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	bool fullscreen;

	sf::Clock dtClock;
	float dt; /*dt -- delta time -- keeps track of how long it took
			  for us/our game to do one update calland one render call together.
			  It resets itself after keeping track each time so lasts around some milliseconds.*/ 
	std::stack<State*> states;

	std::map<std::string, int > supportedKeys;

	float gridSize;

	//Initialization
	void initvariables();
	void initGraphicsSettings();
	
	void initwindow();
	void initkeys();
	void initStateData();
	void initstates();
	
public:
	//Constructor/Destructors
	Game();
	virtual ~Game();

	//Function

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();
	
	//Render
	void render();
	
	//Core
	void run();
};

#endif