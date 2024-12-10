#include "InfoBar.h"

InfoBar::InfoBar(Game* game) : GameObject(game){
}
InfoBar::~InfoBar() {

}
void InfoBar::Render() const {
    SDL_Color color = { 255, 255, 0, 255 };

    // Generar las texturas de los textos
    SDL_Texture* text = game->getFontTexture(
        "Points: " + std::to_string(game->getPoints()),
        color, game->getRenderer());

    // Renderizar las texturas (asumiendo un tamaño de texto fijo)
    if (text) {
        SDL_Rect destRect = { 100, 100, 150, 30 }; // Posición y tamaño de renderizado
        SDL_RenderCopy(game->getRenderer(), text, nullptr, &destRect);
        SDL_DestroyTexture(text); // Liberar textura
    }
}
void InfoBar::Update() {

}
