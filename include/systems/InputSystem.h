#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "edb/Entity.h"
#include "edb/System.h"


struct InputSystem : edb::System<InputSystem>
{
    InputSystem();
    ~InputSystem();
    void handle_input(bool &running);
    void step_simulation(float delta){};
    void render(float delta){};
};

#endif // INPUTSYSTEM_H
