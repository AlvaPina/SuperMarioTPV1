#include <iostream>
#include <vector>
#include <string>

#include "Game.h"
#include "Texture.h"
#include "TileMap.h"
#include "Player.h"

using namespace std;

#include <string>
#include <fstream>
#include "Game.h"

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
	TextureSpec{"background.png", 8, 7},
	{"mario.png", 12, 1},
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
	: seguir(true), mapOffset(0)
{
	// Inicializa la SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Super Mario Bros",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH * WINDOW_SCALE,
		WIN_HEIGHT * WINDOW_SCALE,
		SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 97, 132, 248, 255);	// Color de fondo

	if (window == nullptr || renderer == nullptr)
		throw "Error cargando SDL"s;

	// Carga las texturas
	for (int i = 0; i < NUM_TEXTURES; ++i)
		textures[i] = new Texture(renderer,
			(textureRoot + textureSpec[i].name).c_str(),
			textureSpec[i].numRows,
			textureSpec[i].numColumns);

	// Crea los objetos del juego
	//perro = new Dog(this, -textures[DOG]->getFrameWidth(), 390);
}

Game::~Game()
{
	// Elimina los objetos del juego
	//delete perro;

	// Elimina las texturas
	for (Texture* texture : textures)
		delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void
Game::run()
{
	// Bucle principal del juego
	while (seguir) {
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
	SDL_RenderClear(renderer);

	// Pinta los objetos del juego
	/*textures[BACKGROUND]->render();
	perro->render();*/

	SDL_RenderPresent(renderer);
}

void
Game::update()
{
	// Actualiza los objetos del juego
	//perro->update();
}

void
Game::handleEvents()
{
	// Procesamiento de eventos
	SDL_Event evento;

	while (SDL_PollEvent(&evento)) {
		if (evento.type == SDL_QUIT)
			seguir = false;
		else if (evento.type == SDL_KEYDOWN) {
			//perro->handleEvent(evento);
		}
	}
}


int Game::renderTileMap()
{
	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = mapOffset / TILE_MAP; // TILE_MAP es un atributo de game, es estatico y no es privado
	// Anchura oculta de esa primera columna
	int d0 = mapOffset % TILE_MAP;

	// Recuadro donde se pintar� la tesela en la ventana
	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < WIN_WIDTH + 1; ++i) {
		for (int j = 0; j < WIN_HEIGHT; ++j) {
			// �ndice en el conjunto de patrones de la matriz de �ndices
			int indice = indices[x0 + i][j];

			// Separa n�mero de fila y de columna
			int fx = indice % 9;
			int fy = indice / 9;

			rect.x = -d0 + i * TILE_SIDE;
			rect.y = j * TILE_SIDE;

			// Usa renderFrame para pintar la tesela
			background->renderFrame(rect, fx, fy);
		}
	}
	return 1;
}

void Game::loadObjectMap() {
	const char* DEFAULT_MAP = "world1.txt";

	// Carga el mapa
	ifstream file(DEFAULT_MAP); ///// lo hemos cambiado de istream a ifstream

	// Leemos el mapa l�nea a l�nea para evitar acarreo de errores
	// y permitir extensiones del formato
	string line;
	getline(file, line);

	while (!file) {
		// Usamos un stringstream para leer la l�nea como si fuera un flujo
		ifstream lineStream(line); ///// lo hemos cambiado de istream a ifstream

		char tipo;
		lineStream >> tipo;

		switch (tipo) {
		case 'M':
			//player = new Player(this, lineStream);
			break;
			// uno para cada objeto
		}
	}
}

//Player::Player(Game* game, istream& in)
//	: game(game)
//{
//	in >> position; // ser� in Point2D que sabe leerse
//	in >> numLives; // el n�mero de vidas
//}