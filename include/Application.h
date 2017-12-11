#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include <SDL2/SDL.h>


class Application
{
    public:
        Application();
        ~Application();

        void run(void);
        /*
        SDL_Window Get*window() { return *window; }
        void Set*window(SDL_Window val) { *window = val; }
        SDL_Renderer Get*renderer() { return *renderer; }
        void Set*renderer(SDL_Renderer val) { *renderer = val; }
        static const string GetTITLE() { return TITLE; }
        void SetTITLE(static const string val) { TITLE = val; }
        static const int GetDISPLAY_WIDTH() { return DISPLAY_WIDTH; }
        void SetDISPLAY_WIDTH(static const int val) { DISPLAY_WIDTH = val; }
        static const int GetDISPLAY_HEIGHT() { return DISPLAY_HEIGHT; }
        void SetDISPLAY_HEIGHT(static const int val) { DISPLAY_HEIGHT = val; }
        */

    protected:

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        static const std::string TITLE;
        static const int DISPLAY_WIDTH = 640;
        static const int DISPLAY_HEIGHT = 480;
};

#endif // APPLICATION_H
