#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../include/panel.h"

int main() {

	int speed;
	printf("Escoge un nivel:\n1) Dificil\n2) Fácil\n-> ");
	scanf("%d", &speed);
	float snakeSpeed = (float) speed / 10;  


	initPanel();

	int quit = 0;
	SDL_Event event;

	Uint32 startTime = SDL_GetTicks();

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

	Uint32 currentTime = SDL_GetTicks();
	Uint32 deltaTime = currentTime - startTime;

	if (deltaTime >= snakeSpeed * 1000) {
		drawRect();
		update();
		startTime = currentTime;  
	}

	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				quit = 1;
			}
			handleInput();
		}

		Uint32 currentTime = SDL_GetTicks();
		Uint32 deltaTime = currentTime - startTime;

		if (deltaTime >= snakeSpeed * 1000) {
			drawRect();
			update();
			startTime = currentTime;  
		}
	}


	closePanel();

	return 0;
}
