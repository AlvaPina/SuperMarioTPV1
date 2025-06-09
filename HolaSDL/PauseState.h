#pragma once
#include "GameState.h"
#include "Button.h"

class Game;

class PauseState : public GameState
{
private:
	SDL_Renderer* renderer = nullptr;

public:

	//MainMenuState() {};
	PauseState(Game* g) : GameState(g) {
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
