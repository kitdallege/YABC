#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "edb/System.h"

class RenderSystem : public edb::SystemR<RenderSystem>
{

    public:
        RenderSystem();
        RenderSystem(edb::EntityDb& edb, SDL_Renderer *renderer);
        ~RenderSystem();
        void render(float delta);

    private:
        SDL_Renderer    *renderer;
        edb::EntityDb   &edb;
};

#endif // RENDERSYSTEM_H
