#ifndef SYSTEM_H
#define SYSTEM_H
#include <iostream>

#include "edb/Entity.h"
#include "edb/Component.h"

#include <set>

namespace edb {

    // TODO: Split into 3 'System' bases one for each handle_input,step_simulation,render
    // it would allow
    struct SystemI {
        virtual ~SystemI() {};
        virtual void handle_input(bool &running) {};
        virtual void step_simulation(float delta) {};
        virtual void render(float iterpolation) {};
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

    struct SystemHI {
        virtual ~SystemHI() {};
        virtual void handle_input(bool &running) = 0;
    };
    template<typename T>
    struct SystemH : SystemHI
    {
        void handle_input_(bool &running)
        {
            static_cast<T const&>(*this).handle_input(running);
        }
    };

    struct SystemSI {
        virtual ~SystemSI() {};
        virtual void step_simulation(float delta) = 0;
    };
    template<typename T>
    struct SystemS : SystemSI
    {
        void step_simulation_(float delta)
        {
            static_cast<T const&>(*this).step_simulation(delta);
        }
    };

    struct SystemRI {
        virtual ~SystemRI() {};
        virtual void render(float iterpolation) = 0;
    };
    template<typename T>
    struct SystemR : SystemRI
    {
        void render_(float iterpolation)
        {
            static_cast<T const&>(*this).render(iterpolation);
        }
    };


}
#endif // SYSTEM_H
