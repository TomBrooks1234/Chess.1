//#pragma once
#include "game.h"
//#include "stdafx.h"
#include <iostream>
#include <iomanip> // only used to tidy up the console output here
#undef main
#include <string>
#include"menu.cpp"


const int screenSize = 640;

game* play = nullptr;


int main(int argc, const char* argv[])
{
	//menu();
	bool correct = false;
	int decide;
	while (correct == false)
	{
		cout << "welcome to my chess game" << endl;
		cout << "input the index number of option you wish to pick" << endl;
		cout << "1: start a new game" << endl;
		cout << "2 load prevoiuse game" << endl;
		cin >> decide;
		if ((decide == 1) || (decide == 2))
		{
			correct = true;
		}
	}
	

	play = new game();
	if (decide == 1)
	{
		play->init("chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenSize, screenSize,true);
	}
	else if (decide == 2)
	{
		play->init("chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenSize, screenSize, false);
	}

	while (play->running())
	{
		

		play->handleEvents();
		play->update();
		play->render();
		
		
	}
	if (!empty(play->WINNER))
	{
		cout << "Congratulations " << play->WINNER << " team you WON!!!";
	}
	
	play->clean();
	return 0;



}
