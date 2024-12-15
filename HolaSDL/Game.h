#pragma once
#include "checkML.h"

// Biblioteca est�ndar de C++
#include <array>
#include <vector>
#include <string>

// Biblioteca SDL
#include <SDL.h>
#include <SDL_ttf.h>

// Nuestras clases
#include "Texture.h"
#include "Collision.h"
#include "gameList.h"

// Forward declaration
class SceneObject;

using uint = unsigned int;

//Fordward declarations
class TileMap;
class Block;
class Player;
class Goomba;
class Koopa;
class Mushroom;
class InfoBar;

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
	bool _exit;
	int _mapOffset;
	int _points;
	TTF_Font* _font; // Fuente del juego
	TileMap* _tile;
	GameList<SceneObject> _objects;
	std::vector<SceneObject*> _objectQueue;
	int _nextObject = 0;
	Player* _player;
	InfoBar* _infoBar;

public:
	Game();
	~Game();

	void run();

	void update();
	void render() const;
	void handleEvents();
	void loadObjectMap();
	void addVisibleObjects();
	void addObject(SceneObject*);

	// Getters
	Texture* getTexture(TextureName name) const { return _textures[name]; }
	SDL_Renderer* getRenderer() const { return _renderer; }
	SDL_Texture* getFontTexture(const std::string& text, SDL_Color color, SDL_Renderer* renderer) const;
	int getMapOffset() const { return _mapOffset; }
	int getPoints() { return _points; }
	Player* getPlayer() { return _player; }
	void addMapOffset(int number);
	int getPlayerLives() const;
	
	void addPoints(int pointsToAdd) { _points += pointsToAdd; }


	Collision checkCollision(const SDL_Rect& rect, Collision::Target target);

	// Constante globales
	static constexpr uint WIN_WIDTH = 500;
	static constexpr uint WIN_HEIGHT = 500;
	static constexpr uint FRAME_RATE = 30;
	static constexpr uint GRAVITY = 2;
	static constexpr float SPEED_LIMIT = 30;
	static constexpr float GRAVITY_MAX_VELOCITY = 25;
	static constexpr uint TILE_SIDE = 32;
	static constexpr uint TILE_MAP = 16;

};


