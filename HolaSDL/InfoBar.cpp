#include "InfoBar.h"

InfoBar::InfoBar(PlayState* game) : GameObject(game){
}
InfoBar::~InfoBar() {

}
void InfoBar::Render() const {
    SDL_Color color = { 255, 255, 255, 255 };
    Game* game = gameState->getGame();

    // Generar las texturas de los textos
    SDL_Texture* PointsText = game->getFontTexture(
        "Points: " + std::to_string(static_cast<PlayState*>(gameState)->getPoints()),
        color, game->getRenderer());
    SDL_Texture* LivesText = game->getFontTexture(
        "Lives: " + std::to_string(static_cast<PlayState*>(gameState)->getPlayerLives()),
        color, game->getRenderer());

    // Renderizar las texturas (asumiendo un tamaño de texto fijo)
    if (PointsText) {
        SDL_Rect destRect = { 20, 20, 150, 30 }; // Posición y tamaño de renderizado
        SDL_RenderCopy(game->getRenderer(), PointsText, nullptr, &destRect);
        SDL_DestroyTexture(PointsText); // Liberar textura
    }
    if (LivesText) {
        SDL_Rect destRect = { 330, 20, 150, 30 }; // Posición y tamaño de renderizado
        SDL_RenderCopy(game->getRenderer(), LivesText, nullptr, &destRect);
        SDL_DestroyTexture(LivesText); // Liberar textura
    }
}
void InfoBar::Update() {

}
