#include <iostream>
#include <vector>
#include <string>

#include "Game.h"
#include "Texture.h"
#include "Player.h"

using namespace std;

int renderTileMap()
{
	vector<vector<int>> indices;  // atributo de TileMap
	Texture* background;  // atributo de TileMap

	constexpr int TILE_SIDE = 32;  // constantes estáticas en Game
	constexpr int WINDOW_WIDTH = 18;
	constexpr int WINDOW_HEIGHT = 16;

	int mapOffset;  // atributo de Game

	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = mapOffset / TILE_MAP;
	// Anchura oculta de esa primera columna
	int d0 = mapOffset % TILE_MAP;

	// Recuadro donde se pintará la tesela en la ventana
	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < WINDOW_WIDTH + 1; ++i) {
		for (int j = 0; j < WINDOW_HEIGHT; ++j) {
			// Índice en el conjunto de patrones de la matriz de índices
			int indice = indices[x0 + i][j];

			// Separa número de fila y de columna
			int fx = indice % 9;
			int fy = indice / 9;

			rect.x = -d0 + i * TILE_SIDE;
			rect.y = j * TILE_SIDE;

			// Usa renderFrame para pintar la tesela
			background->renderFrame(rect, fx, fy);
		}
	}
}

Game::loadObjectMap() {
	const char* DEFAULT_MAP = "world1.txt";

	// Carga el mapa
	istream file(DEFAULT_MAP);

	// Leemos el mapa línea a línea para evitar acarreo de errores
	// y permitir extensiones del formato
	string line;
	getline(file, line);

	while (!file) {
		// Usamos un stringstream para leer la línea como si fuera un flujo
		stringstream lineStream(line);

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
//	in >> position; // será in Point2D que sabe leerse
//	in >> numLives; // el número de vidas
//}