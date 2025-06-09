#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"
#include "GameObject.h"
#include "EventHandler.h"
#include <list>
#include <functional>

using namespace std;

using callBack = function<void(void)>;

class Button : public GameObject, public EventHandler
{
protected:
	Vector2D<int> pos;
	Texture* text = nullptr;
	callBack callB;

public:
	Button(GameState* game, Texture* t, int posX, int posY) : GameObject(game), text(t), pos(Vector2D(posX, posY)) {}
	void Connect(callBack call);
	void Render() const override;
	void Update() override {};
	void handleEvent(const SDL_Event& event) override;

	SDL_Rect GetRect()
	{
		SDL_Rect rect;

		rect.x = pos.getX();
		rect.y = pos.getY();
		rect.w = text->getFrameWidth();
		rect.h = text->getFrameHeight();

		return rect;
	}
};

