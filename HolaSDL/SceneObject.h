#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "checkML.h"
#include "GameObject.h"
#include "Vector2D.h"

class SceneObject : public  GameObject
{
protected:
    Point2D<int> pos;
    Vector2D<int> velocity;
    SDL_Rect rect;
    int scale;
    bool isStatic; // Indica si el Objecto tendrá físicas
public:
    SceneObject(Game* game, Point2D<int> pos, Vector2D<int> velocity = { 0, 0 }, bool isStatic = true, int scale = 1);
    virtual ~SceneObject();
    virtual void Render() const override = 0;
    virtual void Update() override = 0;
    virtual bool Hit(SDL_Rect* rectDeAtaque, bool fromPlayer) = 0;

    // Getters y setters
    const SDL_Rect& getRect() const;
    const Point2D<int> getPos() const;
    void setPosition(int x, int y);
    void setVelocity(int vx, int vy);
    void setStatic(bool isStatic);
};
#endif

