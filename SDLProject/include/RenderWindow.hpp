#pragma once
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderWindow {
public:
    RenderWindow(const char *title, int w, int h);
    ~RenderWindow();
    void DrawPoint(int, int);
    void Present();
    void SetColor(int, int, int);
    void Clear();

    SDL_Texture *loadTexture(const char *);
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};

