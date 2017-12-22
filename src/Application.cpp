#include "Application.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <SDL2/SDL_image.h>

#include "edb/EntityDb.h"
#include "edb/System.h"
#include "Components.h"
#include "systems/RenderSystem.h"

constexpr std::chrono::milliseconds timestep(1000/60);
static edb::EntityDb eDB = edb::EntityDb();


Application::Application() : renderer(NULL)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s", SDL_GetError());
    }
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
    window = SDL_CreateWindow("YABC", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 480,
                              320, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Unable to initialize Window: %s", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Unable to initialize Renderer: %s",
                     SDL_GetError());
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    game = Game(window, renderer);
    game.init();
    std::cout << "return for Application()" << std::endl;
}




void Application::run(void)
{
    // TODO: Convert to `using clock = ` once on gcc >= 4.8
    typedef std::chrono::high_resolution_clock clock;
    std::chrono::milliseconds lag(0);
    auto time_start = clock::now();
    do {
        auto time_now = clock::now();
        auto delta_time = time_now - time_start;
        lag += std::chrono::duration_cast<std::chrono::milliseconds>(delta_time);
        time_start = time_now;
        // update hook
        game.handle_input();
        while(lag >= timestep) {
            lag -= timestep;
            // runloop hook
            game.step_simulation(timestep.count());
        }
        // calculate how close or far we are from the next timestep
        auto iterpolation = (float) lag.count() / timestep.count();
        // render hook
        game.render(iterpolation);
        SDL_Delay(10);
    } while(game.running);
}

Application::~Application()
{
    std::cout << "Cleaning up." << std::endl;
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
