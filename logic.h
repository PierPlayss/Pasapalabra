#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>


bool mouseclick(int& mouseX, int& mouseY, int tablero[][4], int& acumulatedpoints, int answPoints[][4],int answers,int multiplicador);

bool settingsmouse(int x, int y, int buttons[]);