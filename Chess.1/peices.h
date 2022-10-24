#pragma once
#include "game.h"
#include<vector>


using namespace std;


const int squareSize = 80;

class peice
{
public:
	peice(const char* texture, SDL_Renderer* ren, string bOw, int row, int collum,string name);
	peice();
	//~peice();

	void move(int row,int collum);
	virtual void showMove(int row, int collum);

	void makeGreen(int xpos, int ypos);

	void update();
	void render();
	int xpos;
	int ypos;
	string Name;

	int numOfMoves;

	int greenx;
	int greeny;
	
	virtual bool isMove(int prevR, int currentR, int prevC, int currentC, peice *arr[][8]);
	string team;

	bool isFriendly(int prevR, int currentR, int prevC, int currentC, peice* arr[][8]);



protected:
	
	
	


	SDL_Texture* green;
	SDL_Texture* peiceTex;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer; 

	/*int row;
	int collum;
	string imageName;
	string team;*/
};

class Pawn : public peice
{
public:
	Pawn(const char* texture, SDL_Renderer* ren ,string bOw, int row, int collum,string name);
	//int showMoves();
	string Name;
	void showMove(int row, int collum);
	bool isMove(int prevR, int currentR, int prevC, int currentC, peice *arr[][8]);
protected:
	
};

class Rook : public peice
{
public:
	Rook(const char* texture, SDL_Renderer* ren, string bOw, int row, int collum,string name);
	bool isMove(int prevR, int currentR, int prevC, int currentC, peice* arr[][8]);
	//int showMoves();
protected:
	
};

class knight : public peice
{
public:
	knight(const char* texture, SDL_Renderer* ren, string bOw, int row, int collum, string name);
	//int showMoves();
	bool isMove(int prevR, int currentR, int prevC, int currentC, peice* arr[][8]);
protected:
	int moveRule;
};

class Bishop : public peice
{
public:
	Bishop(const char* texture, SDL_Renderer* ren, string bOw, int row, int collum, string name);
	//int showMoves();
	bool isMove(int prevR, int currentR, int prevC, int currentC, peice* arr[][8]);
protected:
	int moveRule;
};

class Queen : public peice
{
public:
	Queen(const char* texture, SDL_Renderer* ren, string bOw, int row, int collum, string name);
	//int showMoves();
	bool isMove(int prevR, int currentR, int prevC, int currentC, peice* arr[][8]);
protected:
	int moveRule;
};

class King : public peice
{
public:
	King(const char* texture, SDL_Renderer* ren, string bOw, int row, int collum, string name );
	//int showMoves();
	bool isMove(int prevR, int currentR, int prevC, int currentC, peice* arr[][8]);
protected:
	int moveRule;
};