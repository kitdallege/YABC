#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <vector>
#include <memory>

#include <SDL2/SDL.h>

#include "edb/System.h"
#include "Components.h"

class RenderSystem : public edb::System<RenderSystem>
{

    public:
        RenderSystem();
        RenderSystem(SDL_Renderer *renderer);
        ~RenderSystem();

        void handle_input(bool &running){}
        void step_simulation(float delta){}
        void render(float delta);

    private:
        SDL_Renderer *renderer;
        //std::vector<RenderableComponent> &components;
};

#endif // RENDERSYSTEM_H
