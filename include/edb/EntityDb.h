#ifndef ENTITYDB_H
#define ENTITYDB_H

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "edb/Entity.h"
#include "edb/Storage.h"
#include "edb/System.h"
#include "Components.h"

namespace edb {

    struct EntityDb {
        // vector per 'system-type'.
        std::vector<std::unique_ptr<edb::SystemHI>> inputSystems;
        std::vector<std::unique_ptr<edb::SystemSI>> simulationSystems;
        std::vector<std::unique_ptr<edb::SystemRI>> renderSystems;
        // single contiguous vector per ComponentType.
        ComponentStorage componentStorage;
        edb::Entity nextEntity;

        EntityDb();

        template <typename S, typename ... Args>
        void add_input_system(Args&&... args){
            static_assert(std::is_base_of<edb::SystemHI, S>::value, "S must be a SystemHI");
            std::unique_ptr<S> p(new S(*this, std::forward<Args>(args)...));
            std::cout << "add_input_system: " << (this) << std::endl;
            inputSystems.push_back(std::move(p));
        }

        template <typename S, typename ... Args>
        void add_simulation_system(Args&&... args){
            static_assert(std::is_base_of<edb::SystemSI, S>::value, "S must be a SystemSI");
            std::cout << "add_simulation_system: " << (this) << std::endl;
            std::unique_ptr<S> p(new S(*this, std::forward<Args>(args)...));
            simulationSystems.push_back(std::move(p));
        }

        template <typename S, typename ... Args>
        void add_render_system(Args&&... args){
            static_assert(std::is_base_of<edb::SystemRI, S>::value, "S must be a SystemRI");
            std::cout << "add_render_system: " << (this) << std::endl;
            std::unique_ptr<S> p(new S(*this, std::forward<Args>(args)...));
            renderSystems.push_back(std::move(p));
        }

        // entity & component creation and linkage
        edb::Entity create_entity(){
            return nextEntity++;
        }

        template<typename C, typename ... Args>
        bool add_component(edb::Entity e, Args&&... args) {
            static_assert(std::is_base_of<edb::Component, C>::value, "C must be a Component");
            componentStorage.add<C>(e, std::forward<Args>(args)...);
            return true;
        }
        // TODO: Listen/Notify methods
    };
}
#endif // ENTITYDB_H
