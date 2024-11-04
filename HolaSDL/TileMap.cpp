#include "TileMap.h"

#include <fstream>
#include <sstream>
#include <iostream>

TileMap::TileMap(Game* game, Texture* background)
	: _game(game), _background(background)
{
	mapOffset = 0;
	loadTileMap();
}

int TileMap::renderTileMap()
{
	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = mapOffset / TILE_MAP; // TILE_MAP es un atributo de game, es estatico y no es privado
	// Anchura oculta de esa primera columna
	int d0 = mapOffset % TILE_MAP;

	// Recuadro donde se pintar? la tesela en la ventana
	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < _game->WIN_WIDTH + 1; ++i) {
		for (int j = 0; j < _game->WIN_HEIGHT; ++j) {
			// ?ndice en el conjunto de patrones de la matriz de ?ndices
			int indice = _tileIndices[x0 + i][j];

			// Separa n?mero de fila y de columna
			int fx = indice % 9;
			int fy = indice / 9;

			rect.x = -d0 + i * TILE_SIDE;
			rect.y = j * TILE_SIDE;

			// Usa renderFrame para pintar la tesela
			_background->renderFrame(rect, fx, fy);
		}
	}
	return 1;
}

void TileMap::loadTileMap()
{
	std::ifstream file("../assets/maps/world1.csv");

	if (!file.is_open()) {
		std::cerr << "Error: No se pudo abrir el archivo del mapa de teselas" << std::endl;
		return;
	}

	std::string line;

	while (std::getline(file, line)) {
		std::cout << line;
	}
}

