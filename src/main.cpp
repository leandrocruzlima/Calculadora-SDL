#include <iostream>
#include <SDL2/SDL.h>
#include "basicgui.h"

using namespace std;

int main(int argc, char** args){
	int mouse[2] = {};
	// Inicializa SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Erro ao inicializar SDL: " << SDL_GetError() << endl;
		return 1;
	}
	// Inicializa janela
	SDL_Window* janela = SDL_CreateWindow(
		"XZip v1",
		SDL_WINDOWPOS_CENTERED, // Posição horizontal da janela
		SDL_WINDOWPOS_CENTERED, // Posição vertical da janela
		500, // Largura da janela
		300, // Altura da janela
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE // Configura a janela para ser visível e redimensonável
	);
	int width, height;
	// Checagem
	if (!janela){
		cout << "Erro ao criar janela: " << SDL_GetError() << endl;
		return 1;
	}
	// Inicializa o renderizador
	SDL_Renderer* renderer = SDL_CreateRenderer(
		janela, // O renderizador amira na janela como alvo de renderização
		-1, // Índice do driver de renderização (-1 = primeiro disponível)
		SDL_RENDERER_ACCELERATED // Flag de aceleração
	);
	// Checagem
	if (!renderer){
		cout << "Erro ao inicializar o renderizador: " << SDL_GetError() << endl;
		return 1;
	}
	
	// loop
	// Cria-se uma variável booleana, que fará o loop repetir no momento em que ela se torna falsa:
	bool rodando = true;
	// Detecta os eventos do SDL e salva na variável evento
	SDL_Event evento;
	// Loop principal
	while (rodando){
		// Carrega os eventos
		while (SDL_PollEvent(&evento)){
			if (evento.type == SDL_QUIT){
				// Encerra o loop, encerrando todo o programa com isso:
				rodando = false;
			}
			if (evento.type == SDL_MOUSEMOTION) {
				mouse[0] = evento.motion.x;
				mouse[1] = evento.motion.y;
				cout << "Mouse detected - " << "x: " << mouse[0] << " y: " << mouse[1] << endl;

			}
		}
		// Criação de formas, preenchimentos entram aqui, por exemplo:
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
		SDL_RenderClear(renderer);
		CreateButton(janela, renderer, 50, 50, 0, 0, mouse);
		CreateButton(janela, renderer, 50, 50, 100, 0, mouse);
		// Mostra o frame
		SDL_RenderPresent(renderer);
		// Reproduz numa taxa de aproximadamente 60 frames por segundo:
		SDL_Delay(16);
	}
	// Aqui é o que é executado depois da while ser rompida
	SDL_DestroyWindow(janela); // Destrói a janela
	SDL_DestroyRenderer(renderer); // Destrói o renderizador
	SDL_Quit(); // Fecha o SDL
	return 0;
}