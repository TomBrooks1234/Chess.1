#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#pragma once
#include <string>
#include <fstream> 

using namespace std;

class game 
{
public:
	game(); //constructor 
	~game(); //deconstructor

	void init(const char* title, int xpos, int ypos, int width, int height,bool newG);

	bool clicked = false;
	int prevC = 0;
	int prevR = 0;
	bool moved;//bool varible to see if square clicked was a move

	void handleEvents();
	void renderPosition(SDL_Texture* tex,int x, int y, int w, int h);

	void update();
	void render();
	void clean();
	void addPeices();
	bool running();
	bool show;
	
	void save(ofstream& peiceFile);
	void load(ifstream& peiceFile);

	string WINNER;

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int Collum;
	int Row;
	bool isRunning;
	
	int xInput;
	int yInput;
	
	
	int SquareSize = 80;

	string teamTurn = "white";
	void findSquare();

};
struct Positions
{
	int leftB;
	int rightB;
	int topB;
	int bottomB;

};


