#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

namespace edb {
    #define INVALID_COMPONENT 0
    // start simple with just an enum registry.
    typedef enum {
        COMPONENT_TYPE_POSITION = 1, // << 0,
    } ComponentType;

    struct Component {
        static const ComponentType type = INVALID_COMPONENT;
    };
}

#endif // COMPONENT_H_INCLUDED
