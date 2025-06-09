#include "PauseState.h"

void PauseState::CreateButtons()
{

	Button* bot = new Button(this, game->getTexture(Game::CONTINUAR), 150, 300);
	bot->Connect([this]() {game->continueGame(); });
	gameObjects.push_back(bot);
	addEventListener(bot);

}


void PauseState::render() const
{
	SDL_RenderClear(game->getRenderer());
	for (const auto& object : gameObjects) {
		object->Render();
	}

	SDL_RenderPresent(game->getRenderer());
}

void PauseState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);
}

void PauseState::save(ostream& save) const
{
}

void PauseState::addEventListener(EventHandler* listener)
{
	GameState::addEventListener(listener);
}

void PauseState::addObject(GameObject* object)
{
}
