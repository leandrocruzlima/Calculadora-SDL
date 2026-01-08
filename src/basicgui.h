#ifndef BASICGUI_H
#define BASICGUI_H

#include <SDL2/SDL.h>
/** 
 * Renderiza um botão na tela.
 */
void CreateButton(
    SDL_Window* janela,
    SDL_Renderer* renderer,
    int width,
    int height,
    int x,
    int y,
    int mouse[2]
);

#endif