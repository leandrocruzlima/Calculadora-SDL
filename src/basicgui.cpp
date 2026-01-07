#include "basicgui.h"

void CreateButton(
    SDL_Window* janela,
    SDL_Renderer* renderer,
    int width,
    int height,
    int x,
    int y
) {
        int swidth, sheight;
        // Cria o botão
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_GetWindowSize(janela, &swidth, &sheight);
		SDL_Rect rect {swidth/2 - x, sheight/2 - y, width, height};
		SDL_RenderFillRect(renderer, &rect);
        // Sombra do botão
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_Rect rect2 {swidth/2 - x - 5, sheight/2 - y - 5, width, height};
		SDL_RenderFillRect(renderer, &rect2);
}