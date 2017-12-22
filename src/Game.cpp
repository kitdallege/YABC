#include <unistd.h>

#include <iostream>
#include <memory>
#include <SDL2/SDL_image.h>

#include "Game.h"
#include "edb/EntityDb.h"
#include "edb/System.h"
#include "Components.h"
#include "systems/InputSystem.h"
#include "systems/RenderSystem.h"


bool default_running = true;

Game::Game()
{
    std::cout << "Game::Game() called " << std::endl;
}

Game::Game(SDL_Window *window, SDL_Renderer *renderer) :
        running(default_running), window(window), renderer(renderer), edb(std::move(edb::EntityDb())) {
}

void Game::init() {
    std::cout << "game: " << (&edb) << std::endl;
    edb.add_input_system<InputSystem>();
    edb.add_render_system<RenderSystem>(renderer);
    edb::Entity e = edb.create_entity();
    edb.add_component<InputComponent>(e);
    auto texture = IMG_LoadTexture(renderer, "assets/backgrounds/space1.png");
    if(texture == nullptr) {
        std::cout << "Failed to load texture " << SDL_GetError() << std::endl;
        std::cout << getcwd(0, 0) << std::endl;
    }
    std::cout << "texture: " << texture << std::endl;
    edb.add_component<RenderableComponent>(e, (SDL_Rect *)NULL, (SDL_Rect *)NULL, std::move(texture));
    std::cout << "edb.inputSystems: "       << edb.inputSystems.size() << std::endl;
    std::cout << "edb.simulationSystems: "  << edb.simulationSystems.size() << std::endl;
    std::cout << "edb.renderSystems: "      << edb.renderSystems.size() << std::endl;
    std::cout << "game: " << (&edb) << std::endl;
}

void Game::handle_input() {
    std::cout << "game: " << (&edb) << std::endl;
    std::cout << "edb.inputSystems: "       << edb.inputSystems.size() << std::endl;
    for (auto &sys : edb.inputSystems) {
        sys->handle_input(running);
    }
}

void Game::step_simulation(float delta) {
    std::cout << "game: " << (&edb) << std::endl;
    for (auto &sys : edb.simulationSystems) {
        sys->step_simulation(delta);
    }
}

void Game::render(float iterpolation) {
    std::cout << "Game::render " << (renderer) << std::endl;
    SDL_RenderClear(renderer);
    for (auto &sys : edb.renderSystems) {
        sys->render(iterpolation);
    }
    SDL_RenderPresent(renderer);
}

Game::~Game()
{
    //dtor
}
