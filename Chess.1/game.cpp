#include "game.h"
#include <iostream>
#include "peices.h"
#include "board.h"

//array of square structures
Positions square[8][8];


peice* bord[8][8];

board* background;

using namespace std;

game::game()
{

}

game:: ~game()
{

}

void game::init(const char* title, int xpos, int ypos, int width, int height,bool newG)
{
	int flags = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //cheching to see if sdl2 libary set up correctly 
	{
		cout << "subsystem initialised" << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags); //creating the screen window 
		if (window) // is true
		{
			cout << "window created" << endl;

		}
		renderer = SDL_CreateRenderer(window, -1, 0); //creating the renderer
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "renderer created" << endl;
		}
		isRunning = true;

	}

	background = new board(renderer);
	
	if (newG == true)
	{
		addPeices();
	}
	else if (newG == false)
	{
		ifstream aFile("lastGame.txt");
		load(aFile);
		teamTurn = "white";

	}


	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			square[x][y].leftB = SquareSize * x;
			square[x][y].rightB = SquareSize * (x + 1);
			square[x][y].topB = SquareSize * y;
			square[x][y].bottomB = SquareSize * (y + 1);

		}
	}
}




//handles inputs
void game::handleEvents ()
{
	ofstream outfile("lastGame.txt");
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		//if red x clicked 
		save(outfile);
		isRunning = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
	//if mouse clicked 
		xInput = event.button.x;
		yInput = event.button.y;
		 //gets x and y coordinates
		findSquare(); //finds what square was clicked 
		//cout << Row << Collum << endl;
		cout << "clicked " << clicked << " arr member prev " << bord[prevR][prevC] << " team turn" << teamTurn << endl;
		cout << " c is " << Collum << " r is " << Row<<endl;

		if ((clicked == true)&&(bord[prevR][prevC] != NULL)&&(bord[prevR][prevC]->team ==teamTurn)) {//checks if the use clicked the board twice to avoid expectation thrown, make sure first click was a peice and 
			cout << "in here"<<endl;
			moved =bord[prevR][prevC]->isMove(prevR, Row, prevC, Collum,bord); // checks to see if move is legal and if soo carries out the move 
			
			if (moved == true) // if peice has been moved
			{
				if ((bord[Row][Collum] != NULL)&&(bord[Row][Collum]->Name =="king")) //checks to see if kings been destroyed 
				{
					WINNER = bord[prevR][prevC]->team; //sets winning team
					isRunning = false;
				}
				//updates board position
				bord[Row][Collum] = bord[prevR][prevC];
				bord[prevR][prevC] = 0;
				//changees which users turn it is 
				if (teamTurn == "white")
				{
					teamTurn = "black";
				}
				else
				{
					teamTurn = "white";
				}
			}
			
			
			
		}

		//storing last input
		prevC = Collum;
		prevR = Row;
		
		clicked = true; // means that a peice has been clicked and the program can safley show moves
		
		break;

	}
}

void game::renderPosition(SDL_Texture* tex,int x, int y, int w, int h)
{
	// creates render rectangle information
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(renderer, tex, NULL, &dst);


}

void game::update() //update game posiions
{

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (bord[x][y] != NULL)
			{
				bord[x][y]->update();

			}
		}
	}


	
}

void game::render()
//reners every object in the game 
{
	SDL_RenderClear(renderer); 

	background->drawBoard();

	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (bord[x][y] != NULL)
			{
				
				bord[x][y]->render();
				

			}
		}
	}
	
	SDL_RenderPresent(renderer);

}

void game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

}

void game::addPeices()
{// adds all peices in a new game 
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			bord[x][y] = NULL;
		}
	}
	//white peices

	for (int x = 0; x < 8; x++)
	{
		bord[6][x] = new Pawn("W Pawn.png", renderer, "white", 6, x,"pawn");
	}
	bord[7][0] = new Rook("W Rook.png", renderer, "white", 7, 0, "rook");
	bord[7][7] = new Rook("W Rook.png", renderer, "white", 7, 7, "rook");

	bord[7][1] = new knight("W Knight.png",renderer,"white",7,1,"knight");
	bord[7][6] = new knight("W Knight.png", renderer, "white", 7, 6, "knight");

	bord[7][2] = new Bishop("W Bishop.png", renderer, "white", 7, 2, "bishop");
	bord[7][5] = new Bishop("W Bishop.png", renderer, "white", 7, 5, "bishop");

	bord[7][3] = new Queen("W Queen.png", renderer, "white", 7, 3, "queen");

	bord[7][4] = new King("W King.png", renderer, "white", 7, 4, "king");

	//black peices 
	for (int x = 0; x < 8; x++)
	{
		bord[1][x] = new Pawn("B Pawn.png", renderer, "black", 1, x,"pawn");
	}

	bord[0][0] = new Rook("B Rook.png", renderer, "black", 0, 0, "rook");
	bord[0][7] = new Rook("B Rook.png", renderer, "black", 0, 7, "rook");

	bord[0][1] = new knight("B Knight.png", renderer, "black", 0, 1, "knight");
	bord[0][6] = new knight("B Knight.png", renderer, "black", 0,6, "knight");

	bord[0][2] = new Bishop("B Bishop.png", renderer, "black", 0, 2, "bishop");
	bord[0][5] = new Bishop("B Bishop.png", renderer, "black", 0, 5, "bishop");

	bord[0][3] = new Queen("B Queen.png", renderer, "black", 0, 3, "queen");

	bord[0][4] = new King("B King.png", renderer, "black", 0, 4, "king");

}

bool game::running()
{
	return isRunning;
}

void game::save(ofstream& peiceFile)
{
	//function to save peices at the end of the game 
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (bord[x][y] == NULL)
			{
				peiceFile << NULL<<endl;
			}
			else {
				peiceFile << "1" << endl;
				peiceFile << bord[x][y]->Name<< " " << bord[x][y]->team << " " << bord[x][y]->xpos << " " << bord[x][y]->ypos << endl;
			}
			
		
		}
	}
	
}

void game::load(ifstream& peiceFile)
{
	// sets evey ellement in array to null
	string templine;
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			bord[x][y] = NULL;
		}
	}
	
	while(!peiceFile.eof())
	{

		string name;
		string team;
		int xpos;
		int ypos;
		
		getline(peiceFile, templine);
		cout <<templine<<endl;
		 //loads file and checks what peices where were and adds the to the array at there previouse positions
		if (templine == "1")
		{
			peiceFile >> name >> team >> xpos >> ypos;
			
			if (name == "pawn")
			{
				if (team == "white")
				{
					bord[xpos][ypos] = new Pawn("W Pawn.png", renderer, "white",ypos, xpos, "pawn");
						
				}
				else
				{
					bord[xpos][ypos] = new Pawn("B Pawn.png", renderer, "black", ypos, xpos,  "pawn");
				}
			}
			else if (name == "rook")
			{
				if (team == "white")
				{
					bord[xpos][ypos] = new Rook("W Rook.png", renderer, "white",  ypos, xpos, "rook");

				}
				else
				{
					bord[xpos][ypos] = new Rook("B Rook.png", renderer, "black", ypos, xpos, "rook");
				}
			}
			else if (name == "knight")
			{
				if (team == "white")
				{
					bord[xpos][ypos] = new knight("W Knight.png", renderer, "white", ypos, xpos, "knight");

				}
				else
				{
					bord[xpos][ypos] = new knight("B Knight.png", renderer, "black", ypos, xpos, "knight");
				}
			}
			else if (name == "bishop")
			{
				if (team == "white")
				{
					bord[xpos][ypos] = new Bishop("W Bishop.png", renderer, "white", ypos, xpos, "bishop");

				}
				else
				{
					bord[xpos][ypos] = new Bishop("B Bishop.png", renderer, "black", ypos, xpos, "bishop");
				}
			}
			else if (name == "queen")
			{
				if (team == "white")
				{
					bord[xpos][ypos] = new Queen("W Queen.png", renderer, "white", ypos, xpos, "queen");

				}
				else
				{
					bord[xpos][ypos] = new Queen("B Queen.png", renderer, "black", ypos, xpos, "queen");
				}
			}
			else if (name == "king")
			{
				if (team == "white")
				{
					bord[xpos][ypos] = new King("W King.png", renderer, "white", ypos, xpos, "king");

				}
				else
				{
					bord[xpos][ypos] = new King("B King.png", renderer, "black", ypos, xpos, "king");
				}
			}
		}
			

			
		

		
	}
}











void game::findSquare()
{
	bool loop1 = false;
	bool loop2 = false;
	//algorithm to find what square user has pressed 
	int counter1 = 0;
	int counter2 = 0;
	while (loop1 == false)
	{

		//checks what collum the click was in 
		if ((xInput > square[counter1][1].leftB) && (xInput < square[counter1][1].rightB))
		{

			Collum = counter1;
			loop1 = true;
			
		}
		counter1++;


	}
	//checks what row the click was in
	loop1 = false;
	while (loop2 == false)
	{


		if ((yInput > square[1][counter2].topB) && (yInput < square[1][counter2].bottomB))
		{
			Row = counter2;
			loop2 = true;
		
		}
		counter2++;


	}
	loop2 = false;
}
