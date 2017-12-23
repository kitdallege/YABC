#ifndef COMPONENTS_H_INCLUDED
#define COMPONENTS_H_INCLUDED

#include <SDL2/SDL.h>

#include "edb/Component.h"
#include "math/Vec2.h"

// implement
enum edb::ComponentType : unsigned int {
//    COMPONENT_TYPE_INVALID  = -1,
    COMPONENT_TYPE_POSITION = 1, // 1 << 0 // 0
    COMPONENT_TYPE_INPUT    = 2, // 1 << 1 // 1
    COMPONENT_TYPE_RENDERER = 4, // 1 << 2 // 2
};

struct InputComponent : edb::Component {
    Vec2 mouse_location;

    static const edb::ComponentType type = edb::COMPONENT_TYPE_INPUT;
};

struct SpatialComponent : edb::Component {
    Vec2 position;
    SpatialComponent(Vec2 position) : position(position) {};
    static const edb::ComponentType type = edb::COMPONENT_TYPE_POSITION;
};

struct RenderableComponent : edb::Component {
    SDL_Rect *src_rect;
    SDL_Rect *dest_rect;
    SDL_Texture *texture;
    RenderableComponent(){};
    RenderableComponent(SDL_Rect *src_rect, SDL_Rect *dest_rect, SDL_Texture *texture) : src_rect(src_rect), dest_rect(dest_rect), texture(texture) {}
    static const edb::ComponentType type = edb::COMPONENT_TYPE_RENDERER;
};

#endif // COMPONENTS_H_INCLUDED
