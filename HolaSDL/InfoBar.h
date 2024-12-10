#ifndef INFOBAR_H
#define INFOBAR_H

#include "GameObject.h"

class Cannon;

class InfoBar : public GameObject
{
public:
	InfoBar(Game* game);
	~InfoBar();
	virtual void Render() const override;
	virtual void Update() override;
};
#endif



