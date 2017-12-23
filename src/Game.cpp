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
    // register systems
    edb.add_input_system<InputSystem>();
    edb.add_render_system<RenderSystem>(renderer);

    // background
    edb::Entity background = edb.create_entity();
    auto texture = IMG_LoadTexture(renderer, "assets/backgrounds/space1.png");
    if(texture == nullptr) {
        std::cout << "Failed to load texture " << SDL_GetError() << std::endl;
        std::cout << getcwd(0, 0) << std::endl;
    }
    std::cout << "texture: " << texture << std::endl;
    edb.add_component<RenderableComponent>(background, (SDL_Rect *)NULL, (SDL_Rect *)NULL, std::move(texture));

    // ball
    edb::Entity ball = edb.create_entity();
    auto ballTexture = IMG_LoadTexture(renderer, "assets/breakout_pieces.png");
    if(ballTexture== nullptr) {
        std::cout << "Failed to load texture " << SDL_GetError() << std::endl;
        std::cout << getcwd(0, 0) << std::endl;
    }
    std::cout << "texture: " << texture << std::endl;
    SDL_Rect *ballDest = new SDL_Rect{400, 200, 20, 20};
    SDL_Rect *ballSrc = new SDL_Rect{84, 136, 8, 8};
    edb.add_component<RenderableComponent>(ball, ballSrc, ballDest, std::move(ballTexture));

    // paddle
    edb::Entity paddle = edb.create_entity();
    SDL_Rect *paddleDest = new SDL_Rect{600, 680, 100, 20};
    SDL_Rect *paddleSrc = new SDL_Rect{144, 175, 64, 20};
    edb.add_component<RenderableComponent>(paddle, paddleSrc, paddleDest, std::move(ballTexture));
    edb.add_component<SpatialComponent>(paddle, Vec2 {600, 680});
    edb.add_component<InputComponent>(paddle);
    std::cout << "edb.inputSystems: "       << edb.inputSystems.size() << std::endl;
    std::cout << "edb.simulationSystems: "  << edb.simulationSystems.size() << std::endl;
    std::cout << "edb.renderSystems: "      << edb.renderSystems.size() << std::endl;
    std::cout << "game: " << (&edb) << std::endl;
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
