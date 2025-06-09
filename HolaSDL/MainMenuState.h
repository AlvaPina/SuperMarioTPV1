#pragma once
#include "GameState.h"
#include "Button.h"

class Game;

class MainMenuState : public GameState
{
private:
	SDL_Renderer* renderer = nullptr;

public:

	//MainMenuState() {};
	MainMenuState(Game* g) : GameState(g) {
		CreateButtons();
	};
	void CreateButtons();
	void update() {};
	void render() const;
	void handleEvent(const SDL_Event& event);

	void save(ostream& save) const;
	Game* getGame() const
	{
		return game;
	}
	void addEventListener(EventHandler* listener);
	void addObject(GameObject* object);
};
