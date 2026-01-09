#include "basicgui.h"
#include <iostream>

using namespace std;

static TTF_Font* font = nullptr;

void BG_Init(){
    font = TTF_OpenFont("../fonts/arial.ttf", 27);
    if (!font) {
        cout << "Erro ao inicializar fonte: " << TTF_GetError() << endl;
    }
}

void BG_Shutdown() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

void BG_CreateButton(
    SDL_Window* janela,
    SDL_Renderer* renderer,
    int width,
    int height,
    int x,
    int y,
    int mouse[3],
    const char* text
) {
        int swidth, sheight;
        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, SDL_Color{0, 0, 0, 255});
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        int text_w = surface->w;
        int text_h = surface->h;
        SDL_FreeSurface(surface);
        
        // Sombra
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_GetWindowSize(janela, &swidth, &sheight);
		SDL_Rect rect {swidth/2 - x, sheight/2 - y, width, height};
		SDL_RenderFillRect(renderer, &rect);
        // Luz do botão
        if (mouse[0] >= swidth/2 - x - 5 and mouse[0] <= swidth/2 - x - 5 + width and mouse[1] >= sheight/2 - y - 5 and mouse[1] <= sheight/2 - y - 5 + height){
            if (mouse[2] == 1){
		        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0);
            } else {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
            }

        } else {
		    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        }
		SDL_Rect rect2 {swidth/2 - x - 5, sheight/2 - y - 5, width, height};
		SDL_RenderFillRect(renderer, &rect2);

        SDL_Rect text_rect {rect.x + (rect.w - text_w) / 2, rect.y + (rect.h - text_h) / 2, text_w, text_h};
        SDL_RenderCopy(renderer, texture, nullptr, &text_rect);
        SDL_DestroyTexture(texture);
}