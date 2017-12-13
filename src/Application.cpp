#include "Application.h"
#include <iostream>
#include <chrono>
#include <SDL2/SDL_image.h>



Application::Application()
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
}

constexpr std::chrono::milliseconds timestep(16);


void Application::run(void)
{
    // TODO: Convert to using once gcc >= 4.8
    SDL_Event event;
    typedef std::chrono::high_resolution_clock clock;
    std::chrono::milliseconds lag(0);
    auto time_start = clock::now();
    bool running = true;
    do {
        auto time_now = clock::now();
        auto delta_time = time_now - time_start;
        lag += std::chrono::duration_cast<std::chrono::milliseconds>(delta_time);
        time_start = time_now;
        // InputHandlerSystem
        while(SDL_PollEvent(&event)) {
            std::cout << "Event: " << std::endl;
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    break;
                default:
                    break;
            }
        }
        while(lag >= timestep) {
//            std::cout << "- update: " << lag.count() << std::endl;
            lag -= timestep;
            SDL_Delay(5);
        }
        // calculate how close or far we are from the next timestep
        auto alpha = (float) lag.count() / timestep.count();
        //auto interpolated_state = interpolate(current_state, previous_state, alpha);
        //std::cout << "alpha : " << alpha << std::endl;
//        std::cout << "render: " << alpha << std::endl;
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    } while(running);
}

Application::~Application()
{
    std::cout << "Cleaning up." << std::endl;
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
