#ifndef PANEL_H
#define PANEL_H
#include <SDL2/SDL.h>
#include <panel.h>

int initPanel();
void drawRect();
void spawnFood();
void update();
void handleInput();
int checkCollision();
void closePanel();

#endif 
