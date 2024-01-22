#include <SDL2/SDL.h>
#include <time.h>
#include <stdio.h>

#define PANEL_W 640
#define PANEL_H 480
#define SNAKE_SIZE 20

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

/* Estructuras. */
typedef struct {
	int x, y;
} Point;

typedef struct {
	Point position;
  Point velocity;
} SnakeSegment;

SnakeSegment snake[100];
Point food;

int snakeLength = 1;
int direction = 0; 


int initPanel();
void drawRect();
void spawnFood();
void update();
void handleInput();
int checkCollision();
void closePanel();


int initPanel() {

	/* Creación del panel y manejo de error sobre este. */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "No se pudo iniciar SDL: %s\n", SDL_GetError());
		return 1;
	}

	/* Creación del panel y manejo de error sobre este. */
	window = SDL_CreateWindow("Panel", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, PANEL_W, PANEL_H, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		fprintf(stderr, "No se pudo crear el panel: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	/* Creación del renderer y manejo de error sobre este. */
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		fprintf(stderr, "No se pudo crear el panel: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// Inicializa la serpiente
	snake[0].position.x = PANEL_W / 2;
	snake[0].position.y = PANEL_H / 2;
	snake[0].velocity.x = SNAKE_SIZE;
	snake[0].velocity.y = 0;

	// Inicializa la semilla para generar números aleatorios
	srand(time(NULL));

	// Genera la primera ubicación de la comida
	spawnFood();

	return 0;

}

void handleInput() {
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP] && direction != 2) {
        direction = 0;
    } else if (state[SDL_SCANCODE_RIGHT] && direction != 3) {
        direction = 1;
    } else if (state[SDL_SCANCODE_DOWN] && direction != 0) {
        direction = 2;
    } else if (state[SDL_SCANCODE_LEFT] && direction != 1) {
        direction = 3;
    }
}

void drawRect() {

	/* Asignación del color al panel. */
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	/* Limpiar la pantalla con el color de fondo. */
	SDL_RenderClear(renderer);

	// Dibuja la serpiente
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < snakeLength; i++) {
			SDL_Rect rect = {snake[i].position.x, snake[i].position.y, SNAKE_SIZE, SNAKE_SIZE};
			SDL_RenderFillRect(renderer, &rect);
	}

	// Dibuja la comida
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect foodRect = {food.x, food.y, SNAKE_SIZE, SNAKE_SIZE};
	SDL_RenderFillRect(renderer, &foodRect);

	/* Actualizar la pantalla. */
	SDL_RenderPresent(renderer);

}


void update() {
	// Mueve la serpiente
	for (int i = snakeLength - 1; i > 0; i--) {
		snake[i].position = snake[i - 1].position;
	}

	// Cambia la dirección de la cabeza de la serpiente
	switch (direction) {
		case 0:
			snake[0].position.y -= SNAKE_SIZE;
			break;
		case 1:
			snake[0].position.x += SNAKE_SIZE;
			break;
		case 2:
			snake[0].position.y += SNAKE_SIZE;	
			break;
		case 3:
			snake[0].position.x -= SNAKE_SIZE;;
			break;
	}

	// Verifica colisiones
	if (checkCollision()) {
		printf("¡Game Over!\n");
		closePanel();
		exit(0);
	}

	// Verifica si la cabeza de la serpiente alcanza la comida
	if (snake[0].position.x == food.x && snake[0].position.y == food.y) {
		snakeLength++;
		spawnFood();
	}
}

void spawnFood() {
	food.x = (rand() % (PANEL_W / SNAKE_SIZE)) * SNAKE_SIZE;
	food.y = (rand() % (PANEL_H / SNAKE_SIZE)) * SNAKE_SIZE;
}

int checkCollision() {
	// Verifica colisiones con las paredes
	if (snake[0].position.x < 0 || snake[0].position.x >= PANEL_W ||
		snake[0].position.y < 0 || snake[0].position.y >= PANEL_H) {
		return 1;
	}

	// Verifica colisiones con la serpiente misma
	for (int i = 1; i < snakeLength; i++) {
		if (snake[0].position.x == snake[i].position.x &&
			snake[0].position.y == snake[i].position.y) {
			return 1;
		}
	}

	return 0;
}

void closePanel() {

	/* Liberar recursos. */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}
