#include "Player.h"
#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"


Player::Player(Texture* text, Vector2D<int> pos, Game* gam, int livs, bool movR, bool supMar):
	texture(text), position(pos), game(gam), lives(livs), movingRight(movR), SuperMario(supMar)
{
	onTheFloor = false;
}

void Player::render()
{



}

void Player::update()
{


}

void Player::hit()
{
	if (SuperMario) SuperMario = false;
	else lives--; // ha muerto
}

void Player::handleEvent()
{
	
}
