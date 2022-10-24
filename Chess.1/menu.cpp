#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

void menu()
{
	int flags = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //cheching to see if sdl2 libary set up correctly 
	{
		std::cout << "subsystem initialised" << std::endl;
		SDL_Window* window = SDL_CreateWindow("menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, flags); //creating the screen window 
		if (window) // is true
		{
			std::cout << "window created" <<  std::endl;

		}
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0); //creating the renderer
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created" << std::endl;
		}
		
		SDL_Texture* menu = IMG_LoadTexture(renderer, "chessMenu.png");
		
		////Our event union
		//SDL_Event e;
		////For tracking if we want to quit
		//bool quit = false;
		//while (!quit) {
		//	//Read any events that occured, for now we'll just quit if any event occurs
		//	while (SDL_PollEvent(&e)) {
		//		//If user closes the window
		//		if (e.type == SDL_QUIT) {
		//			quit = true;
		//		}
		//		//If user presses any key
		//		if (e.type == SDL_KEYDOWN) {
		//			quit = true;
		//		}
		//		//If user clicks the mouse
		//		if (e.type == SDL_MOUSEBUTTONDOWN) {
		//			quit = true;
		//		}
		//	}


		//	SDL_RenderPresent(renderer);
		//}
	}
	}
