#pragma once

// Biblioteca est�ndar de C++
#include <array>

// Biblioteca SDL
#include <SDL.h>

// Nuestras clases
#include "Texture.h"

using uint = unsigned int;

//Fordward declarations
class TileMap;
class Block;
class Player;

//
// Clase que representa el juego y controla todos sus aspectos
//
class Game
{
public:
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		MARIO,
		SUPERMARIO,
		FIREMARIO,
		GOOMBA,
		KOOPA,
		PIRANHA,
		PLANT,
		SHELL,
		STAR,
		BLOCKS,
		NUM_TEXTURES,  // Truco C++: n�mero de texturas definidas
	};

private:
	// Ventana de la SDL (se destruir� en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;
	// Interruptor para terminar el juego
	int mapOffset;
	bool exit;
	TileMap* tile;
	Block* block;
	Player* player;

public:
	void run();

	void update();
	void render() const;
	void handleEvents();
	void loadObjectMap();

	Texture* getTexture(TextureName name) const { return textures[name]; }
	int getMapOffset() const { return mapOffset; }

	// Constante globales
	static constexpr uint WIN_WIDTH = 18;
	static constexpr uint WIN_HEIGHT = 16;
	static constexpr uint FRAME_RATE = 50;
	static constexpr uint WINDOW_SCALE = 35;	// escala el tama�o de la ventana

	Game();
	~Game();

};


