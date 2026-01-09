#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "basicgui.h"

using namespace std;

int main(int argc, char** args){
	int mouse[3] = {};
	// Inicializa SDL
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Erro ao inicializar SDL: " << SDL_GetError() << endl;
		return 1;
	}
	TTF_Init();

	// Inicializa janela
	SDL_Window* janela = SDL_CreateWindow(
		"Calculadora SDL",
		SDL_WINDOWPOS_CENTERED, // Posição horizontal da janela
		SDL_WINDOWPOS_CENTERED, // Posição vertical da janela
		250, // Largura da janela
		400, // Altura da janela
		SDL_WINDOW_SHOWN // Configura a janela para ser visível e redimensonável
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
	
	BG_Init();

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
				//cout << "Mouse detected - " << "x: " << mouse[0] << " y: " << mouse[1] << endl;

			}
			if (evento.type == SDL_MOUSEBUTTONDOWN) {
				mouse[2] = 1;
			}
			if (evento.type == SDL_MOUSEBUTTONUP) {
				mouse[2] = 0;
			}
		}
		// cout << mouse[2] << endl;
		// Criação de formas, preenchimentos entram aqui, por exemplo:
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
		SDL_RenderClear(renderer);
		// Primeiros botões (Prototipagem)
		BG_CreateButton(janela, renderer, 50, 50, 110, 10, mouse, "7");
		BG_CreateButton(janela, renderer, 50, 50, 55, 10, mouse, "8");
		BG_CreateButton(janela, renderer, 50, 50, 0, 10, mouse, "9");
		BG_CreateButton(janela, renderer, 50, 50, -55, 10, mouse, "C");
		BG_CreateButton(janela, renderer, 50, 50, 110, -45, mouse, "4");
		BG_CreateButton(janela, renderer, 50, 50, 55, -45, mouse, "5");
		BG_CreateButton(janela, renderer, 50, 50, 0, -45, mouse, "6");
		BG_CreateButton(janela, renderer, 50, 50, 110, -100, mouse, "1");
		BG_CreateButton(janela, renderer, 50, 50, 55, -100, mouse, "2");
		BG_CreateButton(janela, renderer, 50, 50, 0, -100, mouse, "3");


		// Mostra o frame
		SDL_RenderPresent(renderer);
		// Reproduz numa taxa de aproximadamente 60 frames por segundo:
		SDL_Delay(16);
	}

	// Aqui é o que é executado depois da while ser rompida
	SDL_DestroyWindow(janela); // Destrói a janela
	SDL_DestroyRenderer(renderer); // Destrói o renderizador
	BG_Shutdown(); // Fecha fontes de basicgui.cpp
	TTF_Quit(); // Fecha fontes e texturas
	SDL_Quit(); // Fecha o SDL
	return 0;
}