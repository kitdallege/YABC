#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "edb/Entity.h"
#include "edb/System.h"


struct InputSystem : public edb::SystemH<InputSystem>
{
    InputSystem(edb::EntityDb& edb);
    ~InputSystem();
    void handle_input(bool &running);
};

#endif // INPUTSYSTEM_H
