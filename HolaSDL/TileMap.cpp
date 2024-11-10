#include "TileMap.h"

#include <fstream>
#include <sstream>
#include <iostream>

TileMap::TileMap(Game* game, Texture* background)
	: _game(game), _background(background)
{
	loadTileMap();
}

int TileMap::render() const
{
	// Primera columna de la matriz del mapa visible en la ventana
	int col0 = _game->getMapOffset() / TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = _game->getMapOffset() % TILE_SIDE;

	// Recuadro donde se pintará la tesela en la ventana
	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int col = 0; col < _game->WIN_WIDTH + 2; ++col) {
		rect.x = -d0 + col * TILE_SIDE;

		for (int row = 0; row < _game->WIN_HEIGHT; ++row) {
			// Índice en el conjunto de patrones de la matriz de índices
			int indice = _tileIndices[row][col0 + col];

			// Si el índice es -1 no se pinta nada
			if (indice != -1) {
				// Separa número de fila y de columna
				int frameCol = indice % 9;
				int frameRow = indice / 9;

				rect.y = row * TILE_SIDE;

				// Usa renderFrame para pintar la tesela
				_background->renderFrame(rect, frameRow, frameCol);
			}
		}
	}
	return 0;
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
		std::vector<int> row;
		std::stringstream ss(line);
		std::string number;

		while (std::getline(ss, number, ',')) {
			row.push_back(std::stoi(number));
		}

		_tileIndices.push_back(row);
	}

	file.close();

	// Imprimir los valores para verificar
	std::cout << "Contenido de la matriz tileIndices:" << std::endl;
	for (const auto& row : _tileIndices) {
		for (int num : row) {
			std::cout << num << " ";
		}
		std::cout << std::endl;
	}
}

