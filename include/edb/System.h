#ifndef SYSTEM_H
#define SYSTEM_H
#include <iostream>

#include "edb/Entity.h"
#include "edb/Component.h"

#include <set>

namespace edb {

    struct SystemI {
        virtual ~SystemI() {};
        virtual void handle_input(bool &running) = 0;
//        {
//            std::cout << "SystemI::handle_input" << std::endl;
//        };
//        //void update(float delta) {};
        virtual void step_simulation(float delta) = 0;
//        {
//            std::cout << "SystemI::step_simulation" << std::endl;
//        };
        virtual void render(float iterpolation) = 0;
//        {
//            std::cout << "SystemI::render" << std::endl;
//        };
    };

    template<typename T>
    struct System : SystemI
    {
        const std::set<ComponentType> needed;
        void handle_input_(bool &running)
        {
            static_cast<T const&>(*this).handle_input(running);
        }
        void step_simulation_(float delta)
        {
            static_cast<T const&>(*this).step_simulation(delta);
        }
        void render_(float iterpolation)
        {
            static_cast<T const&>(*this).render(iterpolation);
        }
    };
}
#endif // SYSTEM_H
