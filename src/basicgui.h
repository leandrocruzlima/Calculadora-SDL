#ifndef BASICGUI_H
#define BASICGUI_H

#include <SDL2/SDL.h>

void CreateButton(
    SDL_Window* janela,
    SDL_Renderer* renderer,
    int width,
    int height,
    int x,
    int y
);

#endif