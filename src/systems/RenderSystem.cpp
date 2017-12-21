#include <iostream>

#include "RenderSystem.h"



RenderSystem::RenderSystem() : renderer(NULL)
{
//    components = &edb.renderableComponents;
    std::cout << "RenderSystem: constructor" << std::endl;
}

RenderSystem::RenderSystem(SDL_Renderer *renderer) : renderer(renderer)
{
    std::cout << "RenderSystem: I'm alive!" << std::endl;
}

RenderSystem::~RenderSystem()
{
    std::cout << "RenderSystem: " << renderer << "My time for die`n!" << std::endl;
    renderer = NULL;
}

void RenderSystem::render(float delta)
{
//    std::cout << "render update: " <<  (*components).size() << std::endl;
    SDL_RenderClear(renderer);
//    for (auto c : components) {
//        std::cout << "render update" << std::endl;
//    }
    SDL_RenderPresent(renderer);
}
