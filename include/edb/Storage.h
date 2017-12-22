#ifndef STORAGE_H_INCLUDED
#define STORAGE_H_INCLUDED

#include "edb/Entity.h"
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

            // TODO: Add
            // - remove(edb::Entity e) : removes the associated component for this entity.
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
            // some type of `const std::vector<edb::Entity>& join<CType1, CType2>()`
            // which returns a vector of entities which are in both

    };
}

#endif // STORAGE_H_INCLUDED
