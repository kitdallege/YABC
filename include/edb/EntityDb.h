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
    template<typename CType>
    class BaseStorage
    {
        std::vector<CType> table;
        std::map<edb::Entity, edb::ComponentIndex> ecIndex;
        std::map<edb::ComponentIndex, edb::Entity> eciIndex;

        public:
            template <typename ... Args>
            void add(edb::Entity e, Args&&... args)
            {
                auto idx = table.size();
                table.emplace_back(std::forward<Args>(args)...);
                ecIndex[e] = idx;
                eciIndex[idx] = e;
            }

            // remove(edb::Entity e) : removes the associated component for
            // this entity.
            const std::vector<CType>& view()
            {
                return table;
            }

    };
    class ComponentStorage : private BaseStorage<InputComponent>,
                    private BaseStorage<SpatialComponent>,
                    private BaseStorage<RenderableComponent>
    {
        public:
            template<typename CType, typename ... Args>
            void add(edb::Entity e, Args&&... args)
            {
                BaseStorage<CType>::add(e, std::forward<Args>(args)...);
            }

            template<typename CType>
            const std::vector<CType>& view()
            {
                return BaseStorage<CType>::view();
            }

    };

    struct EntityDb {
        //TODO: bust out into a vector per system-type
        // input/simulation/render
        std::vector<std::unique_ptr<edb::SystemHI>> inputSystems;
        std::vector<std::unique_ptr<edb::SystemSI>> simulationSystems;
        std::vector<std::unique_ptr<edb::SystemRI>> renderSystems;
        std::vector<std::unique_ptr<edb::SystemI>> systems;
        ComponentStorage componentStorage;
        edb::Entity nextEntity;

        EntityDb();
        ~EntityDb();

        // system creation & registry
//        void add_system(std::unique_ptr<edb::SystemI> system);

        template <typename S, typename ... Args>
        void add_system(Args&&... args){
            static_assert(std::is_base_of<edb::SystemI, S>::value, "S must be a SystemI");
            std::unique_ptr<S> p(new S(std::forward<Args>(args)...));
//            add_system(std::move(p));
        }

        template <typename S, typename ... Args>
        void add_input_system(Args&&... args){
            static_assert(std::is_base_of<edb::SystemHI, S>::value, "S must be a SystemHI");
            std::unique_ptr<S> p(new S(std::forward<Args>(args)...));
            inputSystems.push_back(std::move(p));
        }

        template <typename S, typename ... Args>
        void add_simulation_system(Args&&... args){
            static_assert(std::is_base_of<edb::SystemSI, S>::value, "S must be a SystemHI");
            std::unique_ptr<S> p(new S(std::forward<Args>(args)...));
            simulationSystems.push_back(std::move(p));
        }

        template <typename S, typename ... Args>
        void add_render_system(Args&&... args){
            static_assert(std::is_base_of<edb::SystemRI, S>::value, "S must be a SystemHI");
            std::unique_ptr<S> p(new S(std::forward<Args>(args)...));
            renderSystems.push_back(std::move(p));
        }

        // entity & component creation and linkage
        edb::Entity create_entity();

        template<typename C, typename ... Args>
        bool add_component(edb::Entity e, Args&&... args) {
            static_assert(std::is_base_of<edb::Component, C>::value, "C must be a Component");
            componentStorage.add<C>(e, std::forward<Args>(args)...);
            return true;
        }
        // listen/notify methods
    };
}
#endif // ENTITYDB_H
