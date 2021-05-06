#include <RenderWindow.hpp>

RenderWindow::RenderWindow(const char * title, int w, int h) : window(nullptr), renderer(nullptr)
{
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    if(!this->window) {
        std::cout << "Couldn't create Window ! Error: " << SDL_GetError() << std::endl;
        exit(-1);
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    // SDL_Texture *texture = SDL_CreateTexture(renderer, )
}

RenderWindow::~RenderWindow() {
    SDL_DestroyWindow(this->window);
    std::cout << "Window destroyed ! " << std::endl;
}

SDL_Texture *RenderWindow::loadTexture(const char *path) {
    SDL_Texture *texture{nullptr};
    texture = IMG_LoadTexture(this->renderer, path);

    if(!texture) {
        std::cout << "Failed to load texture. Error " << SDL_GetError() << std::endl;
        exit(-1);
    }
    return texture;
}

void RenderWindow::DrawPoint(int a, int b) {
    SDL_RenderDrawPoint(this->renderer, a, b); //Renders on middle of screen.
}

void RenderWindow::Present() {
    SDL_RenderPresent(this->renderer); 
}

void RenderWindow::SetColor(int x = 0, int y = 0, int z = 0) {
    SDL_SetRenderDrawColor(this->renderer, x, y, z, 255);
}

void RenderWindow::Clear() {
    SDL_RenderClear(this->renderer);
}


