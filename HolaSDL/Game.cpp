#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "Game.h"
#include "Texture.h"
#include "TileMap.h"
#include "Player.h"
#include "Block.h"
#include "Goomba.h"
#include "Vector2D.h"

using namespace std;


// Formato de la especificaci�n de una textura
struct TextureSpec
{
	const char* name;	// Ruta del archivo
	uint numColumns;	// N�mero de frames por fila
	uint numRows;		// N�mero de frames por columna
};

// Directorio ra�z de los archivos de textura
const string textureRoot = "../assets/imgs/";

// Especificaci�n de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	{"mario.png", 7, 1},
	{"supermario.png", 22, 1},
	{"firemario.png", 21, 1},
	{"goomba.png", 3, 1},
	{"koopa.png", 4, 1},
	{"piranha.png", 2, 1},
	{"plant.png", 4, 1},
	{"shell.png", 2, 1},
	{"star.png", 4, 1},
	{"blocks.png", 6, 1},
};

Game::Game()
	: _exit(false), _mapOffset(0)
{
	// Inicializa la SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("Super Mario Bros",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH,
		WIN_HEIGHT,
		SDL_WINDOW_SHOWN);

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(_renderer, 138, 132, 248, 255);	// Color de fondo

	if (_window == nullptr || _renderer == nullptr)
		throw "Error cargando SDL"s;

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		_textures[i] = new Texture(_renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows,
			textureSpec[i].numColumns);

	_tile = new TileMap(this, _textures[BACKGROUND]);

	// Crea los objetos del juego
	//perro = new Dog(this, -textures[DOG]->getFrameWidth(), 390);
	loadObjectMap();
}

Game::~Game()
{
	// Elimina los objetos del juego
	//delete perro;

	// Elimina las texturas
	for (Texture* texture : _textures)
		delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void
Game::run()
{
	// Bucle principal del juego
	while (!_exit) {
		// Marca de tiempo del inicio de la iteraci�n
		uint32_t inicio = SDL_GetTicks();

		update();       // Actualiza el estado de los objetos del juego
		render();       // Dibuja los objetos en la venta
		handleEvents(); // Maneja los eventos de la SDL

		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - inicio;

		// Duerme el resto de la duraci?n del frame
		if (elapsed < FRAME_RATE)
			SDL_Delay(FRAME_RATE - elapsed);
	}
}

void
Game::render() const
{
	SDL_RenderClear(_renderer);

	// Pinta los objetos del juego
	_tile->render();
	_player->Render();
	
	//Bloques
	for (const auto& block : _bloques) block->render();
	
	//Goombas
	for (const auto& goomba : _goombas) goomba->render();

	//...

	SDL_RenderPresent(_renderer);
}

void
Game::update()
{
	// Actualiza los objetos del juego
	for (const auto& block : _bloques) {
		block->update();
	}
	for (const auto& goomba : _goombas) goomba->update();

	_player->Update();
}

void
Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT){
			_exit = true;
		} 
		else {
			_player->handleEvent(evento);
		}
	}
}

void Game::loadObjectMap() {
	const char* DEFAULT_MAP = "../assets/maps/world1.txt";

	// Carga el mapa
	ifstream file(DEFAULT_MAP); ///// lo hemos cambiado de istream a ifstream

	// Leemos el mapa l�nea a l�nea para evitar acarreo de errores
	// y permitir extensiones del formato
	string line;

	while (getline(file, line)) {
		// Usamos un stringstream para leer la línea como si fuera un flujo
		stringstream lineStream(line);

		char tipo;
		lineStream >> tipo;

		int auxX, auxY;
		lineStream >> auxX;
		lineStream >> auxY;

		Vector2D<int>  auxPos(auxX, auxY - 1);

		switch (tipo) {
		case 'M': {
			int auxLiv;
			lineStream >> auxLiv;

			_player = new Player(_textures[MARIO], auxPos, this, auxLiv, false, Player::MarioState::BASE_MARIO);
			break;
		}
		case 'B': {
			string auxtype;
			lineStream >> auxtype;

			if (auxtype == "B") {
				Block* block = new Block(this, Block::LADRILLO, auxPos, _textures[BLOCKS], Block::BlockContent::EMPTY);
				_bloques.push_back(block);
			}
			else if (auxtype == "?") {
				lineStream >> auxtype;
				if(auxtype == "C")
				{
					Block* block = new Block(this, Block::SORPRESA, auxPos, _textures[BLOCKS], Block::BlockContent::COIN);
					_bloques.push_back(block);
				}
				else
				{
					Block* block = new Block(this, Block::SORPRESA, auxPos, _textures[BLOCKS], Block::BlockContent::POWER_UP);
					_bloques.push_back(block);
				}
			}
			break;
		}
		case 'G': {
			Goomba* goomba = new Goomba(_textures[GOOMBA], auxPos, this);
			_goombas.push_back(goomba);
			break;
		}
		}
	}
}

void Game::addMapOffset(int number)
{
	_mapOffset += number;
}

Collision Game::checkCollision(const SDL_Rect& rect, bool fromPlayer)
{
	Collision collisionResult{ false, false };

	// Colisiones con TileMap
	if (_tile->hit(rect, fromPlayer)) {
		collisionResult.collides = true;
	}

	// Colisiones con otros objetos...

	return collisionResult;
}

//Player::Player(Game* game, istream& in)
//	: game(game)
//{
//	in >> position; // ser� in Point2D que sabe leerse
//	in >> numLives; // el n�mero de vidas
//}