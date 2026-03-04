#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "basicgui.h"
#include <tuple>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

const char* RenderButtons(
	SDL_Window* janela,
	SDL_Renderer* renderer,
	int mouse[3],
	SDL_Event* evento
) {
	// Variáveis da posição da grade em relação a tela
	int gridbuttonx{110}, gridbuttony{10};
	// Cria uma grid 3x4 dos números
	const char* numpad[12] = {
		"7", "8", "9",
		"4", "5", "6",
		"1", "2", "3",
		"X", "0", "X"
	};
	// Botões da grid
	const char* result = nullptr;
	for (int a = 0; a < 4; a++) {
		for (int b = 0; b < 3; b++) {
				if (numpad[a*3+b] != "X") {

				auto [k, l] = BG_CreateButton(janela, renderer, 50, 50, gridbuttonx, gridbuttony, mouse, numpad[a * 3 + b], numpad[a * 3 + b], evento);
				
				if (k && mouse[2] == 1){
					mouse[2] = 2;
					result = l;
				}
			}
			gridbuttonx -= 55;
		}
		gridbuttonx = 110;
		gridbuttony -= 55;
	}
	gridbuttony = 10;

	return result;
}

long double operand(
	long double var1,
	long double var2,
	int STAGE
){
	if (STAGE == 1) {
		var1 += var2;
	}
	if (STAGE == 2) {
		var1 -= var2;
	}
	if (STAGE == 3) {
		var1 *= var2;
	}
	if (STAGE == 4) {
		if (var2 != 0){
			var1 /= var2;
		} else {
			var1 = 0;
		}
	}
	return var1;
}

int main(int argc, char** args){
	// Variáveis a serem inicializadas

	/**
	* 	STAGE:
    * 		0: NULL
	* 		1: SOMA
	* 		2: SUBTRAÇÃO
	* 		3: MULTPLICAÇÃO
	* 		4: DIVISÃO
	*/

	int STAGE = 0;

	double valores[2] = {};
	int valores_pointer = 0;
	long double r = 0.0;
	const char* operators[4] = {"+", "-", "×", "÷"};

	string fdisplay = " ";
	int counter = 1;

	
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
		410, // Altura da janela
		SDL_WINDOW_SHOWN // Permite a tela ser visível
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

			}
			if (evento.type == SDL_MOUSEBUTTONDOWN) {
				mouse[2] = 1;
			}
			if (evento.type == SDL_MOUSEBUTTONUP) {
				mouse[2] = 0;
			}
		}
		// Criação de formas, preenchimentos entram aqui, por exemplo:
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 0);
		SDL_RenderClear(renderer);
		//Captura o resultado de cada botão
		const char* result = RenderButtons(janela, renderer, mouse, &evento);
		const char* lastresult;
		if (result != nullptr) {
			if (counter < 16) {
				fdisplay += result;
				counter += 1;
			}
		}
		// Cria os operadores
		for (int i = 0; i < 4; i++){
			auto [k, l] = BG_CreateButton(janela, renderer, 50, 50, -65, 10 - i * 55, mouse, operators[i], operators[i], &evento);
			if (k && mouse[2] == 1 and fdisplay != " ") {
				mouse[2] = 2;
				STAGE = i+1;
				counter = 0;

				if (valores_pointer < 2) {
					valores[valores_pointer] = stold(fdisplay);
					fdisplay = " ";
				}
				
				valores_pointer += 1;
				if (result != nullptr){
					string temp = result;
					if (temp.empty() && isdigit(temp[0])) {
						valores[valores_pointer] = stold(temp);
						fdisplay = " ";
					}
				}
				if (valores_pointer >= 2){
					r = operand(valores[0], valores[1], STAGE);
					if (r == static_cast<long long>(r)){
						fdisplay = to_string(static_cast<long long>(r));
					} else {
						fdisplay = to_string(r);
					}
					valores_pointer = 0;
					valores[1] = 0;
				}

			}
		}
		auto [f, g] = BG_CreateButton(janela, renderer, 50, 50, 0, -155, mouse, "=", "=", &evento);
		if (f && mouse[2] == 1 and fdisplay != " ") {
			mouse[2] = 2;
			if (valores_pointer == 1) {
				r = operand(valores[0], stold(fdisplay), STAGE);
				valores[0] = r;
				if (r == static_cast<long long>(r)){
					fdisplay = to_string(static_cast<long long>(r));
				} else {
					fdisplay = to_string(valores[0]);
					cout << valores[0] << ", " << valores[1] << endl << STAGE << endl << fdisplay << "\n\n";
				}
				valores_pointer = 0;
				counter = 0;
			}
		}
		auto [a, b] = BG_CreateButton(janela, renderer, 50, 50, 110, -155, mouse, "C", "C", &evento);
		if (a && mouse[2] == 1) {
			valores[2] = {};
			fdisplay = " ";
			counter = 0;
			valores_pointer = 0;
		}
		BG_CreateTextBar(janela, renderer, 230, 140, 110, 170, fdisplay.c_str());


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
