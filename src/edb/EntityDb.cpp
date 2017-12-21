#include <iostream>

#include "EntityDb.h"


namespace edb {

    EntityDb::EntityDb() : systems(), ecIndex(), eciIndex(), nextEntity(1) {}

    EntityDb::~EntityDb()
    {
        //dtor
    }
    void EntityDb::add_system(std::unique_ptr<edb::SystemI> system) {
        std::cout << "Adding system" << std::endl;
        systems.push_back(std::move(system));
    }

    edb::Entity EntityDb::create_entity() {
        return nextEntity++;
    }


//    bool EntityDb::add_component(edb::Entity e, edb::ComponentType ct, std::unique_ptr<edb::Component> c) {
//        switch (ct) {
//            case COMPONENT_TYPE_POSITION:
//                {
//                    auto idx = spatialComponents.size();
//                    spatialComponents.push_back(*(SpatialComponent *)(c.release()));
//                    ecIndex[ct][e] = idx;
//                    eciIndex[ct][idx] = e;
//                }
//                break;
//            case COMPONENT_TYPE_INPUT:
//                {
//                    inputComponents.push_back(*dynamic_cast<InputComponent *>(c.release()));
//                }
//                break;
//            default:
//                break;
//        }
//        std::cout << "Adding component: " << ct << std::endl;
//        return false;
//    }
}
