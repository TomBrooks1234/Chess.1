#pragma once
#include "game.h"
#include <string>

class board 
{
public:
	board(SDL_Renderer* ren);

	void drawBoard();
	void render(SDL_Texture* colour, int x, int y);
	int squareSize = 80;
	


private:

	SDL_Rect dst;

	SDL_Texture* black;
	SDL_Texture* white;

	SDL_Renderer* renderer;
};

