#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "PlayState.h"
#include "Game.h"
#include "Texture.h"
#include "TileMap.h"
#include "Player.h"
#include "Block.h"
#include "Goomba.h"
#include "Vector2D.h"
#include "InfoBar.h"

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
//const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
//	TextureSpec{"background.png", 9, 7},
//	{"mario.png", 7, 1},
//	{"supermario.png", 22, 1},
//	{"firemario.png", 21, 1},
//	{"goomba.png", 3, 1},
//	{"koopa.png", 4, 1},
//	{"piranha.png", 2, 1},
//	{"plant.png", 4, 1},
//	{"shell.png", 2, 1},
//	{"star.png", 4, 1},
//	{"blocks.png", 6, 1},
//	{"portada.png", 1, 1}
//};

PlayState::PlayState(Game* game) : GameState(game), _mapOffset(0), _points(0) {
	// Inicializa la SDL
	//SDL_Init(SDL_INIT_EVERYTHING);
	//_window = SDL_CreateWindow("Super Mario Bros",
	//	SDL_WINDOWPOS_CENTERED,
	//	SDL_WINDOWPOS_CENTERED,
	//	WIN_WIDTH,
	//	WIN_HEIGHT,
	//	SDL_WINDOW_SHOWN);

	//TTF_Init();

	//_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	//SDL_SetRenderDrawColor(_renderer, 138, 132, 248, 255);	// Color de fondo

	//if (_window == nullptr || _renderer == nullptr)
	//	throw "Error cargando SDL"s;

	// Carga las texturas
	//for (int i = 0; i < NUM_TEXTURES; ++i)
	//	_textures[i] = new Texture(_renderer,
	//		(textureRoot + textureSpec[i].name).c_str(),
	//		textureSpec[i].numRows,
	//		textureSpec[i].numColumns);

	_tile = new TileMap(this, getTexture(Game::BACKGROUND));
	_infoBar = new InfoBar(this);
	//_objects.push_back(_infoBar);

	// Crea los objetos del juego
	loadObjectMap();

	_font = TTF_OpenFont("../assets/fonts/retro.ttf", 24);
	if (!_font) {
		std::cerr << "Error al cargar la fuente: " << TTF_GetError() << std::endl;
	}

}

PlayState::~PlayState()
{
	// Elimina los objetos del juego
	//delete _player;
	delete _infoBar;
	delete _tile;

	// Eliminar objetos de la lista
	//for (auto object : _objects) {
	//	delete object;
	//}

	// Desactiva la SDL
	//SDL_DestroyRenderer(_renderer);
	//SDL_DestroyWindow(_window);
	//SDL_Quit();

	//Font
	//if (_font) {
	//	TTF_CloseFont(_font);
	//	_font = nullptr;
	//}
	//TTF_Quit();
}

//void
//PlayState::run()
//{
//	// Bucle principal del juego
//	while (!_exit) {
//		// Marca de tiempo del inicio de la iteraci�n
//		uint32_t inicio = SDL_GetTicks();
//
//		update();       // Actualiza el estado de los objetos del juego
//		render();       // Dibuja los objetos en la venta
//		//handleEvent(); // Maneja los eventos de la SDL
//
//		// Tiempo que se ha tardado en ejecutar lo anterior
//		uint32_t elapsed = SDL_GetTicks() - inicio;
//
//		// Duerme el resto de la duraci?n del frame
//		if (elapsed < FRAME_RATE)
//			SDL_Delay(FRAME_RATE - elapsed);
//	}
//}

void
PlayState::render() const
{
	// Pinta los objetos del juego
	_tile->render();
	_infoBar->Render();

	// Renderiza los objetos del juego
	for (const auto& object : _objects) {
		object->Render();
	}

	SDL_RenderPresent(getRenderer());
}

void
PlayState::update()
{
	addVisibleObjects();
	// Actualiza los objetos del juego
	for (const auto& object : _objects) {
		object->Update();
	}
}

void
PlayState::handleEvent(const SDL_Event& event)
{
	// Procesamiento de eventos
	//while (SDL_PollEvent(event)) {
	//	if (event.type == SDL_QUIT) {
	//		_exit = true;
	//	}
	//	else {
	//		_player->handleEvent(event);
	//	}
	//}

	GameState::handleEvent(event);
}

void
PlayState::loadObjectMap() {
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

		Vector2D<int>  auxPos(auxX * TILE_SIDE, auxY * TILE_SIDE);

		switch (tipo) {
		case 'M': {
			int auxLiv;
			lineStream >> auxLiv;

			_player = new Player(getTexture(Game::MARIO), auxPos, this, auxLiv, false, Player::MarioState::BASE_MARIO);
			addObject(_player);
			eventHandlers.push_back(_player);
			break;
		}
		case 'B': {
			string auxtype;
			lineStream >> auxtype;

			if (auxtype == "B") {
				Block* block = new Block(this, Block::LADRILLO, auxPos, getTexture(Game::BLOCKS), Block::BlockContent::EMPTY);
				_objectQueue.push_back(block);
			}
			else if (auxtype == "?") {
				lineStream >> auxtype;
				Block* block;
				if (auxtype == "C")
				{
					block = new Block(this, Block::SORPRESA, auxPos, getTexture(Game::BLOCKS), Block::BlockContent::COIN);
				}
				else
				{
					block = new Block(this, Block::SORPRESA, auxPos, getTexture(Game::BLOCKS), Block::BlockContent::POWER_UP);
				}
				_objectQueue.push_back(block);
			}
			break;
		}
		case 'G': {
			Goomba* goomba = new Goomba(getTexture(Game::GOOMBA), auxPos, this);
			_objectQueue.push_back(goomba);
			break;
		}
		}
	}
}

void
PlayState::addVisibleObjects()
{
	// Borde derecho del mapa (más una casilla)
	const int rightThreshold = _mapOffset + Game::WIN_WIDTH + Game::TILE_SIDE;

	while (_nextObject < _objectQueue.size() && _objectQueue[_nextObject]->getWorldPos().getX() < rightThreshold)
		addObject(_objectQueue[_nextObject++]->Clone());
}

void PlayState::addObject(SceneObject* sceneObject)
{
	_objects.push_back(sceneObject);
}

void
PlayState::restartLevel()
{
	_mapOffset = 0;
	_nextObject = 0;

	for (auto it = _objects.begin(); it != _objects.end(); ) {
		SceneObject* obj = *it;
		if (obj != _player) {
			delete obj;
		}
		++it;
	}

	_player->resetPosition();
}

SDL_Texture* PlayState::getFontTexture(const std::string& text, SDL_Color color, SDL_Renderer* renderer) const
{
	if (!_font) return nullptr;

	// Renderizar el texto en una superficie
	SDL_Surface* textSurface = TTF_RenderText_Solid(_font, text.c_str(), color);
	if (!textSurface) {
		std::cerr << "Error al renderizar texto: " << TTF_GetError() << std::endl;
		return nullptr;
	}

	// Convertir la superficie en textura
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);

	if (!texture) {
		std::cerr << "Error al crear textura del texto: " << SDL_GetError() << std::endl;
	}

	return texture;
}

void
PlayState::addMapOffset(int number)
{
	_mapOffset += number;
}

int
PlayState::getPlayerLives() const
{
	return _player->GetVidas();
}

Collision PlayState::checkCollision(const SDL_Rect& rect, Collision::Target target)
{
	Collision collisionResult = NO_COLLISION;

	// Colisiones con TileMap
	Collision tileCol = _tile->hit(rect, target);
	collisionResult = tileCol;

	//std::cout << tileCol.colliderPosition.getX() << " " << tileCol.colliderPosition.getX() << "| ";

	// Colisiones con otros objetos
	for (const auto& object : _objects) {
		Collision objectCollision = object->Hit(rect, target);
		// Si colisiona en el EjeX
		if (objectCollision.horizontal != 0) {
			collisionResult.horizontal = objectCollision.horizontal;
		}
		// Si colisiona en el EjeY
		if (objectCollision.vertical != 0) {
			collisionResult.vertical = objectCollision.vertical;
		}
		if (objectCollision.result != Collision::NONE) {
			collisionResult.result = objectCollision.result;
			return collisionResult;
		}
	}
	return collisionResult;
}

void PlayState::addEventListener(EventHandler* listener)
{
	GameState::addEventListener(listener);
}