#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "InputSystem.h"
#include "Components.h"
#include "edb/EntityDb.h"

InputSystem::InputSystem(edb::EntityDb& db) : SystemH(edb), edb(db)
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
    auto ip = edb.componentStorage.view<InputComponent>();
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
//        std::cout << "Event: " << std::endl;
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

    int *x, *y;
    SDL_GetMouseState(x, y);
    InputComponent ic = ip.at(0);
    ic.mouse_location.x = (float) *x;
    ic.mouse_location.y = (float) *y;
}
