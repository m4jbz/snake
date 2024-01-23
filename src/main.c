#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../include/panel.h"

int main() {

	initPanel();

	int quit = 0;
	SDL_Event event;

	int teclaPresionada = 0;

	while (!teclaPresionada) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				teclaPresionada = 1; 
			} else if (event.type == SDL_KEYDOWN) {
				teclaPresionada = 1; 
			}
		}
	}

	drawRect();
	update();
	SDL_Delay(250);

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = 1;
				printf("Tu puntuacion fue: %d\n", puntaje());
			}
			handleInput();
		}

		drawRect();
		update();
		/* Ajusta la velocidad del juego. */
		SDL_Delay(250); 
	}


	closePanel();

	return 0;
}
