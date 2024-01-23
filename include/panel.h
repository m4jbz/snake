#ifndef PANEL_H
#define PANEL_H
#include <SDL2/SDL.h>

int initPanel();
void drawRect();
void spawnFood();
void update();
void handleInput();
int checkCollision();
int puntaje();
void closePanel();

#endif 
