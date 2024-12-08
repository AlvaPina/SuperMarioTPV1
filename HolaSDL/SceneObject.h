#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <string>

#include "checkML.h"
#include "GameObject.h"
#include "Vector2D.h"

class SceneObject : public  GameObject
{
protected:
    Point2D<int> pos; // Posicion en la pantalla
    Vector2D<int> velocity;
    SDL_RendererFlip flip;	// Indica en que direccion se rota el sprite
    Texture* texture;
    int scale;
    int gravity; // gravedad local del objeto
    bool isStatic; // Indica si el Objecto tendr� f�sicas
    bool flippingVelocity; // Indica si el Objecto se flipea en base a su velocidad
    bool colliding; // Indica si est� tocando algo
    Collision tryToMove(const Vector2D<int>& velocity, Collision::Target target);
    void manageFlip();
    void renderPositions() const;
    void setTexture(Texture* newTexture);
public:
    SceneObject(Game* game, Texture* texture, Point2D<int> pos, Vector2D<int> velocity = { 0, 0 }, bool isStatic = true);
    virtual ~SceneObject();

    virtual void Render() const override = 0;
    virtual void Update() override = 0;
    virtual Collision Hit(const SDL_Rect& rectDeAtaque, Collision::Target target) = 0;

    // Getters y setters
    const Point2D<int> getScreenPos() const;
    const Point2D<int> getWorldPos() const;
    const SDL_Rect getScreenRect() const;   // Para renderizar
    const SDL_Rect getWorldRect() const;    // Para colisiones
    void setPosition(int x, int y);
    void setVelocity(int vx, int vy);
    void setStatic(bool isStatic);
    void setGravity(int gravity);
    void setScale(int scale);
};
#endif

