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
    SDL_RendererFlip flip;	// Indica en que direccion se rota el sprite
    Texture* texture;
    int scale;
    int gravity; // gravedad local del objeto
    bool isStatic; // Indica si el Objecto tendr� f�sicas
    bool flippingVelocity; // Indica si el Objecto se flipea en base a su velocidad
    bool colliding; // Indica si est� tocando algo
public:
    SceneObject(Game* game, Texture* texture, Point2D<int> pos, Vector2D<int> velocity = { 0, 0 }, bool isStatic = true);
    virtual ~SceneObject();

    virtual void Render() const override = 0;
    virtual void Update() override = 0;
    virtual bool Hit(SDL_Rect* rectDeAtaque, bool fromPlayer) = 0;

    void move();
    void manageFlip();

    // Getters y setters
    const Point2D<int> getPos() const;
    const SDL_Rect getRect() const;
    void setPosition(int x, int y);
    void setVelocity(int vx, int vy);
    void setStatic(bool isStatic);
    void setGravity(int gravity);
    void setScale(int scale);
};
#endif

