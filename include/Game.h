#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "edb/EntityDb.h"

class Game
{
    public:
        bool running;
        Game();
        Game(SDL_Window *window, SDL_Renderer *renderer);
        ~Game();

        void init(); // resource initialization.
        void handle_input();
        void step_simulation(float delta);
        void render(float iterpolation);

    protected:

    private:
        // make these shared_ptr's
        SDL_Window      *window;
        SDL_Renderer    *renderer;
        edb::EntityDb         edb;

};

#endif // GAME_H
