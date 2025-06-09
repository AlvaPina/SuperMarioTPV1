#include "checkML.h"
#include "Button.h"

void Button::Connect(callBack call)
{
	callB = call;
}

void Button::Render() const
{
	SDL_Rect rect;
	rect.w = text->getFrameWidth();
	rect.h = text->getFrameHeight();
	rect.x = pos.getX();
	rect.y = pos.getY();

	text->render(rect);
}

void Button::handleEvent(const SDL_Event& event)
{
	SDL_Point point = { event.button.x, event.button.y };

	SDL_Rect auxRect = GetRect();

	if (SDL_PointInRect(&point, &auxRect))
	{
		// HACER CHAMPIÑON VISIBLE

		if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
		{
			callB();
		}
	}
}
