#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "edb/System.h"
#include "Components.h"

class RenderSystem : public edb::SystemR<RenderSystem>
{

    public:
        RenderSystem();
        RenderSystem(SDL_Renderer *renderer);
        ~RenderSystem();
        void render(float delta);

    private:
        SDL_Renderer *renderer;
};

#endif // RENDERSYSTEM_H
