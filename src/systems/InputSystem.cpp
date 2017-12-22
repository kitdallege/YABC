#include "InputSystem.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "Components.h"

InputSystem::InputSystem(edb::EntityDb&edb) : SystemH(edb)
{
    std::cout << "InputSystem: I'm alive! " << (&edb) << std::endl;
}

InputSystem::~InputSystem()
{
    std::cout << "InputSystem dtor" << std::endl;
    std::cout << "InputSystem: My time for die`n!" << std::endl;
}

void InputSystem::handle_input(bool &running)
{
    std::cout << "InputSystem::handle_input" << std::endl;
    SDL_Event event;
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
}
