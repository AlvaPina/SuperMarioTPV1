#pragma once

// Biblioteca estándar de C++
#include <array>

// Biblioteca SDL
#include <SDL.h>

// Nuestras clases
#include "Texture.h"

using uint = unsigned int;

//
// Clase que representa el juego y controla todos sus aspectos
//
class Game
{
public:
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		DOG,
		HELICOPTER,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};

private:
	// Ventana de la SDL (se destruirá en el destructor)
	SDL_Window* window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* renderer = nullptr;
	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> textures;
	// Interruptor para terminar el juego
	bool seguir;

	int mapOffset;  // atributo de Game obtener con getter

public:
	void run();

	void update();
	void render() const;
	void handleEvents();
	void loadObjectMap();
	int renderTileMap();

	Texture* getTexture(TextureName name) const { return textures[name]; }
	int getMapOffset() const { return mapOffset; }

	// Constante globales
	static constexpr uint WIN_WIDTH = 32;
	static constexpr uint WIN_HEIGHT = 16;
	static constexpr uint FRAME_RATE = 50;
	static constexpr uint TILE_SIDE = 32;
	static constexpr uint TILE_MAP = 16;

	int indices[WIN_WIDTH][WIN_HEIGHT];

	Game();
	~Game();
};


