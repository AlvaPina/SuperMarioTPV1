#pragma once
#include "checkML.h"

#include "Texture.h"
#include "SceneObject.h"
#include "Game.h"
class Lift : SceneObject
{
public:
	Lift(Game* game, Texture* text, Vector2D<int> pos);
	~Lift();

	void Render() const override;
	void Update() override;
	Collision Hit(const SDL_Rect& rectDeAtaque, Collision::Target target) override;
private:
	bool _dir = false;  //Arriba u abajo 
	int _minPos;		//Posicion mas baja
	const int _MOVING_LENGHT = 100; //Lo que se desplazara arriba
	const int _SPEED = 3;
};

