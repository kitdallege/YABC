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
    edb.add_input_system<InputSystem>();
    edb.add_render_system<RenderSystem>(renderer);
    edb::Entity e = edb.create_entity();
    edb.add_component<InputComponent>(e);
    std::cout << "edb.inputSystems: "       << edb.inputSystems.size() << std::endl;
    std::cout << "edb.simulationSystems: "  << edb.simulationSystems.size() << std::endl;
    std::cout << "edb.renderSystems: "      << edb.renderSystems.size() << std::endl;
}

void Game::handle_input() {
    for (auto &sys : edb.inputSystems) {
        sys->handle_input(running);
    }
}

void Game::step_simulation(float delta) {
    for (auto &sys : edb.simulationSystems) {
        sys->step_simulation(delta);
    }
}

void Game::render(float iterpolation) {
    for (auto &sys : edb.renderSystems) {
        sys->render(iterpolation);
    }
}

Game::~Game()
{
    //dtor
}
