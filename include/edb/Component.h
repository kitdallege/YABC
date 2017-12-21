#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

namespace edb {

    typedef unsigned int ComponentIndex;

    #define INVALID_COMPONENT -1
    // start simple with just an enum registry.
    enum ComponentType : unsigned int;

    // base interface to a component is its 'type' attribute.
    struct Component {
        static const ComponentType type;

        virtual ~Component(){};
    };
}

#endif // COMPONENT_H_INCLUDED
