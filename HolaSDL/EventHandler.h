#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL.h>
#include <iostream>

class EventHandler {
public:
    // M�todo virtual puro para manejar los eventos. Las clases derivadas deben implementarlo.
    virtual void handleEvent(const SDL_Event& event) = 0;

    // Virtual destructor para asegurar una correcta destrucci�n de objetos derivados.
    virtual ~EventHandler() = default;
};

#endif // EVENT_HANDLER_H
