#ifndef ENTITYDB_H
#define ENTITYDB_H

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "edb/Entity.h"
//#include "edb/Component.h"
#include "edb/System.h"
#include "Components.h"

namespace edb {

    struct EntityDb {
        std::vector<std::unique_ptr<edb::SystemI>> systems;
        // NOTE: To make this truly cache-friendly you'd basically have a
        // vector 'per' component-type so that you could store
        // objects (not unique_ptr's) contiguously in memory.
        /* Tables */
        std::vector<InputComponent>         inputComponents;
        std::vector<SpatialComponent>       spatialComponents;
        std::vector<RenderableComponent>    renderableComponents;
        /* TODO: Use this table/index combination for the main store.
        // Systems will then be able to ref vector's of components
        // compute the 'intersection of entity keys'
        // and iterate using the ecIndex(s) to walk through the component vectors.
        */
        /* Index */
        std::map<edb::ComponentType, std::map<edb::Entity, edb::ComponentIndex> > ecIndex;
        std::map<edb::ComponentType, std::map<edb::ComponentIndex, edb::Entity>> eciIndex;

        //std::map<edb::ComponentType, std::vector<edb::Component>> cIndex;
        // Pros: It makes compaction of cIndex (after component/entity removal) a lot
        // easier [from O(n) to O(1)].
        // Cons: It doubles the memory space for indexes. (([32-to-64]bits per entry) * num-entries) * 2) :/
        // Note: Boost.Bimap is ideal as its basically bimap =  map<x,y> + map<y,x>
        // TODO: remove below 'ecIndex'.
        //std::map<edb::Entity, std::map<edb::ComponentType, edb::Component>> ecIndex;
        edb::Entity nextEntity;

        EntityDb();
        ~EntityDb();

        // system creation & registry
        void add_system(std::unique_ptr<edb::SystemI> system);

        template <typename S, typename ... Args>
        void add_system(Args&&... args){
            static_assert(std::is_base_of<edb::SystemI, S>::value, "S must be a SystemI");
            std::unique_ptr<S> p(new S(std::forward<Args>(args)...));
            add_system(std::move(p));
        }

        // entity & component creation and linkage
        edb::Entity create_entity();


        bool add_component(edb::Entity e, edb::ComponentType ct, std::unique_ptr<edb::Component> c);

        template<typename C>
        bool add_component(edb::Entity e, std::unique_ptr<C> c) {
            static_assert(std::is_base_of<edb::Component, C>::value, "C must be a Component");
            return add_component(e, C::type, std::move(c));
        }

        // listen/notify methods

    };
}
#endif // ENTITYDB_H
