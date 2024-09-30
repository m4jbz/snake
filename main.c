#include <stdio.h>
#include <time.h>
#include "raylib.h"

#define WIDTH 800
#define HEIGHT 600
#define H_WIDTH WIDTH/2
#define H_HEIGHT HEIGHT/2
#define SIZE (Vector2){ 20.0f, 20.0f }
#define UP 265
#define DOWN 264
#define LEFT 263
#define RIGHT 262

typedef struct {
	Vector2 pos;
	Vector2 vel;
	Color color;
} Snake;

Snake init_snake(Snake s)
{
	s.pos = (Vector2){ H_WIDTH, H_HEIGHT };
	s.vel = (Vector2){ 0, 0 };
	s.color = DARKGREEN;
	return s;
}

Vector2 move(Vector2 pos, Vector2 vel)
{
	pos.x += vel.x;
	pos.y += vel.y;
	return pos;
}

int main()
{
	Snake snake;
	snake = init_snake(snake);
	Vector2 apple;

	SetRandomSeed(time(NULL));

	InitWindow(WIDTH, HEIGHT, "Snake");
	SetTargetFPS(60); // fps

	while(!WindowShouldClose()) {
		ClearBackground(BLACK);
		BeginDrawing();
		DrawFPS(10, 10);	
		DrawRectangleV(snake.pos, SIZE, snake.color);

		int key = GetKeyPressed();
		switch (key) {
			case UP:
				snake.vel = (Vector2){ 0, -1 };
				break;
			case DOWN:
				snake.vel = (Vector2){ 0, 1 };
				break;
			case LEFT:
				snake.vel = (Vector2){ -1, 0 };
				break;
			case RIGHT:
				snake.vel = (Vector2){ 1, 0 };
				break;
		}
		snake.pos = move(snake.pos, snake.vel);

		EndDrawing();
	}

	return 0;
}
