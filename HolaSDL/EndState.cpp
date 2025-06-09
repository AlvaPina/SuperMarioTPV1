#include "EndState.h"

void EndState::CreateButtons()
{

	Button* bot = new Button(this, game->getTexture(Game::VOLVE_RMENU), 100, 300);
	bot->Connect([this]() {game->startGame(); });
	gameObjects.push_back(bot);
	addEventListener(bot);

	Button* bote = new Button(this, game->getTexture(Game::SE_ACABO), 150, 200);
	gameObjects.push_back(bote);
	addEventListener(bote);

}


void EndState::render() const
{
	SDL_RenderClear(game->getRenderer());
	for (const auto& object : gameObjects) {
		object->Render();
	}

	SDL_RenderPresent(game->getRenderer());
}

void EndState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);
}

void EndState::save(ostream& save) const
{
}

void EndState::addEventListener(EventHandler* listener)
{
	GameState::addEventListener(listener);
}

void EndState::addObject(GameObject* object)
{
}
