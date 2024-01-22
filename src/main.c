#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "../include/panel.h"

int main() {

	initPanel();

	int quit = 0;
	SDL_Event e;

	while (!quit) {
			while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
							quit = 1;
					}
					handleInput();
			}

			update();
			drawRect();
			SDL_Delay(200); // Ajusta la velocidad del juego
	}

	closePanel();

	return 0;
}
