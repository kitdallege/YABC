#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "edb/Entity.h"
#include "edb/System.h"


class InputSystem : public edb::SystemH<InputSystem>
{

    public:
        InputSystem(edb::EntityDb& edb);
        ~InputSystem();
        void handle_input(bool &running);

    private:
        edb::EntityDb   &edb;
};

#endif // INPUTSYSTEM_H
