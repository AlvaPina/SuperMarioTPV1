#pragma once

// Biblioteca est�ndar de C++
#include <array>
#include <vector>

// Biblioteca SDL
#include <SDL.h>

// Nuestras clases
#include "Texture.h"
#include "Collision.h"

using uint = unsigned int;

//Fordward declarations
class TileMap;
class Block;
class Player;
class Goomba;
class Koopa;
class Mushroom;

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
	SDL_Window* _window = nullptr;
	// Renderizador de la SDL (para dibujar)
	SDL_Renderer* _renderer = nullptr;
	// Array con todas las texturas del juego
	std::array<Texture*, NUM_TEXTURES> _textures;
	// Interruptor para terminar el juego
	int _mapOffset;
	bool _exit;
	TileMap* _tile;
	Player* _player;
	std::vector<Block*> _bloques;
	std::vector<Goomba*> _goombas;
	std::vector<Koopa*> _koopas;
	std::vector<Mushroom*> _mushrooms;

public:
	Game();
	~Game();

	void run();

	void update();
	void render() const;
	void handleEvents();
	void loadObjectMap();

	Texture* getTexture(TextureName name) const { return _textures[name]; }
	int getMapOffset() const { return _mapOffset; }
	void addMapOffset(int number);

	Collision checkCollision(const SDL_Rect& rect, bool fromPlayer);

	// Constante globales
	static constexpr uint WIN_WIDTH = 500;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint FRAME_RATE = 50;
	static constexpr uint GRAVITY = 15;
	static constexpr uint TILE_SIDE = 32;
	static constexpr uint TILE_MAP = 16;

	

};


