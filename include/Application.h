#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
#include <string>
#include <SDL2/SDL.h>

#include "Game.h"

class Application
{

public:

    Application();
    ~Application();

    void run(void);

private:
    //    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
    Game game;
    SDL_Window *window;
    SDL_Renderer *renderer;
    static const std::string TITLE;
    static const int DISPLAY_WIDTH = 640;
    static const int DISPLAY_HEIGHT = 480;
};

#endif // APPLICATION_H
