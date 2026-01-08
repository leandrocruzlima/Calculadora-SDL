#include "basicgui.h"

void CreateButton(
    SDL_Window* janela,
    SDL_Renderer* renderer,
    int width,
    int height,
    int x,
    int y,
    int mouse[2]
) {
        int swidth, sheight;
        // Sombra
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_GetWindowSize(janela, &swidth, &sheight);
		SDL_Rect rect {swidth/2 - x, sheight/2 - y, width, height};
		SDL_RenderFillRect(renderer, &rect);
        // Luz do botão
        if (mouse[0] >= swidth/2 - x - 5 and mouse[0] <= swidth/2 - x - 5 + width and mouse[1] >= sheight/2 - y - 5 and mouse[1] <= sheight/2 - y - 5 + height){
		    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
        } else {
		    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        }
		SDL_Rect rect2 {swidth/2 - x - 5, sheight/2 - y - 5, width, height};
		SDL_RenderFillRect(renderer, &rect2);
}