#include "basicgui.h"

void CreateButton(
    SDL_Window* janela,
    SDL_Renderer* renderer,
    int width,
    int height,
    int x,
    int y
) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		SDL_GetWindowSize(janela, &width, &height);
		// cout << width << " " << height << endl;
		// Carregar retângulo
		SDL_Rect rect {width/2 - x, height/2 - y, 50, 50};
		SDL_RenderFillRect(renderer, &rect);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

		SDL_Rect rect2 {width/2 - x - 5, height/2 - y - 5, 50, 50};
		SDL_RenderFillRect(renderer, &rect2);
}