#include <iostream>
#include "EntityDb.h"


namespace edb {
    EntityDb::EntityDb() : inputSystems(), simulationSystems(), renderSystems(),
                           componentStorage(), nextEntity(1)
    {
        inputSystems.reserve(10);
        simulationSystems.reserve(10);
        renderSystems.reserve(10);
    }
}
