#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Entity.hpp"
class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	SDL_Texture* Points(const char* msg, int x, int y, int r, int g, int b, int size,int& w, int& h);
	void cleanUp();
	void clear();
	void render(Entity& p_entity, double angle, float multiplicador);
	void render(Entity& p_entity,float multiplicador);
	void render(Entity& p_entity, SDL_Rect& rect);
	void display();
	void animation(Entity& p_entity, SDL_Rect &rect, SDL_Rect& pos);
	void drawText(const char* msg, int x, int y, int r, int g, int b, int size);


	
private:
	SDL_Renderer* renderer;
	SDL_Window *window = nullptr;
	

};


