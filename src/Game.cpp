#include <iostream>
#include <memory>

#include "Game.h"

#include "edb/EntityDb.h"
#include "edb/System.h"
#include "Components.h"
#include "systems/InputSystem.h"
#include "systems/RenderSystem.h"


bool default_running = true;

Game::Game()
{
    //ctor
}

Game::Game(SDL_Window *window, SDL_Renderer *renderer) :
        running(default_running), window(window), renderer(renderer) {
    edb = edb::EntityDb();
    edb.add_system<InputSystem>();
    //edb.add_system<RenderSystem>(renderer);
//    edb::Entity e = edb.create_entity();
//    eDB.add_component<InputComponent>(e);
//    std::unique_ptr<edb::SystemI> sp(new RenderSystem(renderer));
//    edb.add_system(std::move(sp));
    // TODO: Need an archtypes to throw common entities in.
    // add systems
    //    eDB.add_system<RenderSystem>();
    //    // create entities
    //    edb::Entity e = eDB.create_entity();
    //    // associate components
    //    std::unique_ptr<InputComponent> ic(new InputComponent());
    //    eDB.add_component<InputComponent>(e, std::move(ic));
    //    //eDB.add_component(e, edb::COMPONENT_TYPE_INPUT, std::move(cp));
    //    //std::unique_ptr<edb::Component> cp(new RenderableComponent());
    //    //eDB.add_component(e, edb::COMPONENT_TYPE_RENDERER, std::move(cp));
    //    //systems.push_back(std::move(p));
}

void Game::handle_input() {
    for (auto &sys : edb.systems) {
        sys->handle_input(running);
    }
}

void Game::step_simulation(float delta) {
    for (auto &sys : edb.systems) {
        sys->step_simulation(delta);
    }
}

void Game::render(float iterpolation) {
    for (auto &sys : edb.systems) {
        sys->render(iterpolation);
    }
}

Game::~Game()
{
    //dtor
}
