#pragma once
#include <string>
#include "peices.h"
#include "source.cpp"

peice::peice(string IName, int rowN, int collumN)
{
	imageName = IName;
	int row = rowN;
	int collum = collumN;
	//SDL_Texture* imageName = loadTexture("W Pawn.png", renderer);
	//renderTexture(imageName, renderer, row * SquareSize, collum * SquareSize, SquareSize, SquareSize);
}

void peice::move()
{

}
