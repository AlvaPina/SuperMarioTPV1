#include "MainMenuState.h"

void MainMenuState::CreateButtons()
{

	Button* bot = new Button(this, game->getTexture(Game::NIVEL1), 150, 300);
	bot->Connect([this]() {game->startGame(); });
	gameObjects.push_back(bot);
	addEventListener(bot);

}


void MainMenuState::render() const
{
	SDL_RenderClear(game->getRenderer());
	game->getTexture(Game::MAINMENU)->render();
	for (const auto& object : gameObjects) {
		object->Render();
	}	
	
	SDL_RenderPresent(game->getRenderer());
}

void MainMenuState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);
}

void MainMenuState::save(ostream& save) const
{
}

//void MainMenuState::hasDied(GameList<GameObject, true>::anchor it)
//{
//}

void MainMenuState::addEventListener(EventHandler* listener)
{
	GameState::addEventListener(listener);
}

void MainMenuState::addObject(GameObject* object)
{
}
