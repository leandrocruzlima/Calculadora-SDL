#ifndef BASICGUI_H
#define BASICGUI_H

#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <tuple>
/*
 * Inicializa
*/
void BG_Init();
/**
 * Fecha
 */
void BG_Shutdown();
/** 
 * Renderiza um botão na tela.
 */
std::tuple<bool, const char*> BG_CreateButton(
    SDL_Window* janela,
    SDL_Renderer* renderer,
    int width,
    int height,
    int x,
    int y,
    int mouse[3],
    const char* text,
    const char* id,
    SDL_Event* event
);

void BG_CreateTextBar(
    SDL_Window* janela,
    SDL_Renderer* renderer,
    int w,
    int h,
    int x,
    int y,
    const char* value
);

#endif