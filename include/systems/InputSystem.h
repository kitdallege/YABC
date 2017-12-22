#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "edb/Entity.h"
#include "edb/System.h"


struct InputSystem : edb::SystemH<InputSystem>
{
    InputSystem();
    ~InputSystem();
    void handle_input(bool &running);
};

#endif // INPUTSYSTEM_H
