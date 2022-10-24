#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "res_path.h"
#include "cleanup.h"

/*
 * Lesson 3: SDL Extension Libraries
 */
 //Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
//calculate the square size by dividing screen into 8x8 squars 
const int SquareSize = 640 / 8;

/*
 * Log an SDL error with some error message to the output stream of our choice
 * @param os The output stream to write the message too
 * @param msg The error message to write, format will be msg error: SDL_GetError()
 */
void logSDLError(std::ostream& os, const std::string& msg) {
	os << msg << " error: " << SDL_GetError() << std::endl;
}
/*
 * Loads an image into a texture on the rendering device
 * @param file The image file to load
 * @param ren The renderer to load the texture onto
 * @return the loaded texture, or nullptr if something went wrong.
 */
SDL_Texture* loadTexture(const std::string& file, SDL_Renderer* ren) {
	SDL_Texture* texture = IMG_LoadTexture(ren, file.c_str());
	if (texture == nullptr) {
		logSDLError(std::cout, "LoadTexture");
	}
	return texture;
}
/*
 * Draw an SDL_Texture to an SDL_Renderer at position x, y, with some desired
 * width and height
 * @param tex The source texture we want to draw
 * @param rend The renderer we want to draw too
 * @param x The x coordinate to draw too
 * @param y The y coordinate to draw too
 * @param w The width of the texture to draw
 * @param h The height of the texture to draw
 */
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h) {
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

int main(int, char**) {
	//Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	//Setup our window and renderer
	SDL_Window* window = SDL_CreateWindow("Lesson 3", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	//The textures we'll be using
	//const std::string resPath = getResourcePath("Lesson3");
	SDL_Texture* black = loadTexture("black.png", renderer);
	SDL_Texture* white = loadTexture("white.png", renderer);

	//Make sure they both loaded ok
	if (black == nullptr || white == nullptr) {
		cleanup(black, white, renderer, window);
		SDL_Quit();
		return 1;
	}

	//A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	for (int i = 0; i < 3; ++i) {
		//Clear the window
		SDL_RenderClear(renderer);

		//Determine how many tiles we'll need to fill the screen
		int xTiles = 8;
		int yTiles = 8;

		//Draw the tiles by calculating their positions
		for (int x = 0; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				int decide = (x + y) % 2;
				if (decide == 0)
				{
					renderTexture(white, renderer, x * SquareSize, y * SquareSize, SquareSize, SquareSize);
				}
				else if (decide == 0)
				{
					renderTexture(black, renderer, x * SquareSize, y * SquareSize, SquareSize, SquareSize);
				}

			}

		}

		//Our event union
		SDL_Event e;
		//For tracking if we want to quit
		bool quit = false;
		while (!quit) {
			//Read any events that occured, for now we'll just quit if any event occurs
			while (SDL_PollEvent(&e)) {
				//If user closes the window
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				//If user presses any key
				if (e.type == SDL_KEYDOWN) {
					quit = true;
				}
				//If user clicks the mouse
				if (e.type == SDL_MOUSEBUTTONDOWN) {
					quit = true;
				}
			}


			SDL_RenderPresent(renderer);
		}
	}

	//Destroy the various items
	cleanup(black, white, renderer, window);
	IMG_Quit();
	SDL_Quit();

	return 0;
}