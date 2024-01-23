#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../include/panel.h"

int main() {

	printf("Tu puntuacion es: 1\n");
	initPanel();

	int quit = 0;
	SDL_Event e;

	while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
							quit = 1;
							printf("Tu puntuacion fue: %d", puntaje());
					}
					handleInput();
			}

			update();
			drawRect();
			/* Ajusta la velocidad del juego. */
			SDL_Delay(200); 
	}

	closePanel();

	return 0;
}
