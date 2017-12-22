#include <iostream>

#include "RenderSystem.h"
#include "edb/EntityDb.h"

RenderSystem::RenderSystem(edb::EntityDb &db, SDL_Renderer *renderer) : SystemR(db), renderer(renderer), edb(db)
{
    std::cout << "RenderSystem: constructor: " << std::endl;
    std::cout << (&db) << " : " << (&edb) << std::endl;
}

RenderSystem::~RenderSystem()
{
    std::cout << "RenderSystem: " << renderer << "My time for die`n!" << std::endl;
    renderer = NULL;
}

void RenderSystem::render(float delta)
{
    auto comps = edb.componentStorage.view<RenderableComponent>();
    std::cout << "render update: " <<  comps.size() << std::endl;
    std::cout << "RenderSystem::render " << (renderer) << std::endl;
    for (auto const &c : comps) {
        //std::cout << "SDL_RenderCopy(renderer, c.texture, " << c.src_rect << ", " << c.dest_rect << std::endl;
        SDL_RenderCopy(renderer, c.texture, NULL, NULL);
    }

}
