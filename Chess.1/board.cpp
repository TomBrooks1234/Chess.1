#include "board.h"



using namespace std;


int bORw(int x, int y)
{
	int decide = (x + y) % 2;
	if (decide == 0)
	{
		return 0;
		
	}
	else if (decide != 0)
	{
		return 1;
	}
}

board::board(SDL_Renderer* ren)
{
	black = IMG_LoadTexture(ren, "black.png");
	white = IMG_LoadTexture(ren, "white.png");
	renderer = ren;
}

void board::drawBoard()
{
	
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			int temp = bORw(x, y);
			if (temp == 1)
			{
				board::render(white, x*squareSize, y*squareSize);
			}
			else if (temp == 0)
			{
				render(black, x * squareSize, y * squareSize);
			}

		}

	}
}

void board::render(SDL_Texture* colour,int x,int y)
{
	dst.x = x;
	dst.y = y;
	dst.w = squareSize;
	dst.h = squareSize;
	
	SDL_RenderCopy(renderer,colour , NULL, &dst);
}