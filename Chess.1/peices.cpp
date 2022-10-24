#include "peices.h"
#include <cmath>

peice::peice(const char* texture, SDL_Renderer* ren ,string bOw,int row, int collum,string name)
{
	
	renderer = ren;
	peiceTex = IMG_LoadTexture(renderer, texture);
	team = bOw;
	xpos = collum;
	ypos = row;
	Name = name;


}

peice::peice()
{
	renderer = NULL;
	peiceTex = NULL;
	

	xpos = NULL;
	ypos = NULL;
}

void peice::move(int row, int collum)
{

	
	ypos = ypos - row;
	xpos = xpos - collum;
	
	
}

void peice::showMove(int row, int collum)
{
	
}

void peice::makeGreen(int xpos, int ypos)
{
	

	destRect.x = xpos * squareSize;
	destRect.y = ypos * squareSize;
	destRect.w = squareSize;
	destRect.h = squareSize;

	green = IMG_LoadTexture(renderer, "green.png");
	SDL_RenderCopy(renderer, green, NULL, &destRect);
}

void peice::update()
{
	destRect.x = xpos * squareSize;
	destRect.y = ypos * squareSize;
	destRect.w = squareSize;
	destRect.h = squareSize;

}

void peice::render()
{
	SDL_RenderCopy(renderer, peiceTex, NULL, &destRect);
	
}

bool peice::isMove(int prevR, int currentR, int prevC, int current, peice *arr[][8])
{
	return false;
}

bool peice::isFriendly(int prevR, int currentR, int prevC, int currentC, peice* arr[][8])
{
	if ((arr[prevR][prevC] != NULL) && (arr[currentR][currentC] != NULL))
	{
		if (arr[prevR][prevC]->team == arr[currentR][currentC]->team)
		{
			return true;
		}
		else return false;
	}
	return false;
}





Pawn::Pawn(const char* texture, SDL_Renderer* ren, string bOw, int row, int collum,string name) :peice(texture, ren, bOw, row, collum,name)
{
}



void Pawn::showMove(int row, int collum)
{
	if (team == "white")
	{
		if (row == 6)
		{
			makeGreen(collum, row - 1);
			makeGreen(collum, row - 2);

		}
		else {
			makeGreen(collum, row - 1);
		}
	}
	else if (team == "black")
	{
		if (row == 1)
		{
			makeGreen(collum, row + 1);
			makeGreen(collum, row + 2);

		}
		else {
			makeGreen(collum, row + 1);
		}
	}
	
}

bool Pawn::isMove(int prevR, int currentR, int prevC, int currentC, peice *arr[][8])
{

	int teamMove;// varible to change method functianilty to work for both team 
		if (arr[prevR][prevC]->team == "white")
	{
		teamMove = 1;
	}
	else if (arr[prevR][prevC]->team == "black")
	{
		teamMove = -1;
	}

	
	if (prevC == currentC) // see if user has clicked in the same collum as pawn
	{
		//cout <<"current peice  "<< arr[prevR][prevC]<<" infront "<<arr[prevR + 1][prevC] << endl;
		if (arr[prevR - teamMove][prevC] == NULL) //see if there is a peice infront of pawn 
		{
			if ((prevR - currentR) == teamMove) // see if the use has moved one row 
			{
				move(teamMove, 0);
				return true;
			}
			if (arr[prevR][prevC]->team == "white")
			{
				if (((prevR == 6) && (currentR == 4)) && (arr[prevR - (2 * teamMove)][prevC] == NULL))// if in start position can move 2 squares 
				{
					move(2 * teamMove, 0);
					return true;
				}
			}
			if (arr[prevR][prevC]->team == "black")
			{
				if (((prevR == 1) && (currentR == 3)) && (arr[prevR - (2 * teamMove)][prevC] == NULL))// if in start position can move 2 squares 
				{
					move(2 * teamMove, 0);
					return true;
				}
			}
			
		}
	}
	
	if (((arr[prevR][prevC ] != NULL) &&(arr[prevR][prevC]->team != arr[currentR][currentC]->team)) || ((arr[prevR][prevC] != NULL) && (arr[prevR][prevC]->team != arr[currentR][currentC]->team)))//if a peice diganol and if its enemy peice 
	{

		if (currentR == prevR - teamMove)// check user has clicked the row infront of peice 
		{
		
			if (currentC == prevC + teamMove)//check if the peice to the top right of pawn is a enemy peice 
			{
				
				move(teamMove, -teamMove);
				return true;
			}
			else if (currentC == prevC -teamMove)//check if the peice to the top left of pawn is a enemy peice 
			{
				
				move(teamMove, teamMove);
				return true;
			}
		}
	}
		return false;
}

Rook::Rook(const char* texture, SDL_Renderer* ren, string bOw, int row, int collum, string name) : peice(texture, ren, bOw, row, collum,name)
{
}

bool Rook::isMove(int prevR, int currentR, int prevC, int currentC, peice* arr[][8])
{
	bool friends = isFriendly(prevR, currentR, prevC, currentC, arr);
	if (friends == true)
	{
		return false;
	}
	int diff;
	int direction=1;
	cout << " prevR is " << prevR << " currentR is " << currentR << " prevC is " << prevC << " currentC is " << currentC << endl;
	if (prevR == currentR) //check if same row
	{
		diff = (currentC - prevC) ; // find how many collums they are apart 
		if (diff > 0)
		{
			cout << "right "<<endl;
			direction = 1;//moving to the right
		}
		else if (diff < 0)
		{
			
			direction = -1; //moving to the left 
			diff = sqrt(diff * diff); // make the difference a positive number 
		}
		for (int x = 1; x < diff; x++)// start x at 1 so it doesnt check the starting square
		{
		
			int collski = (prevC + (x * direction));
			
			if (arr[prevR][collski] != NULL)//if array peice in the same row but collum staartiong at 1 to the direction of peice 
			{
				
				
				cout << arr[prevR][x]->Name<<endl;
				
				return false;
			}

		}
		move(0, -(diff *direction) );
		return true;

	}
	if (prevC == currentC) //check if same collum
	{
		diff = currentR - prevR; // find how many rows they are apart 
		if (diff > 0)
		{
			
			direction = 1;//moving to the up
		}
		else if (diff < 0)
		{
			
			direction = -1; //moving to the down 
			diff = sqrt(diff * diff); // make the difference a positive number 
		}
		for (int x = 1; x < diff; x++)// start x at 1 so it doesnt check the starting square
		{
			
			if (arr[(prevR + (x * direction))][prevC] != NULL)//if array peice in the same row but collum staartiong at 1 to the direction of peice 
			{
				cout<<arr[prevR + (x * direction)][prevC]->Name << endl;
				
				return false;
			}

		}
		move( -(diff * direction),0);
		return true;

	}
	return false;
}



knight::knight(const char* texture, SDL_Renderer* ren, string bOw, int row, int collum, string name) : peice(texture, ren, bOw, row, collum,name)
{
}

bool knight::isMove(int prevR, int currentR, int prevC, int currentC, peice* arr[][8])
{
	bool friends = isFriendly(prevR, currentR, prevC, currentC, arr);
	if (friends == true)
	{
		return false;
	}

	if ((prevR - currentR == 2) && (prevC - currentC == 1))
	{
		move(2, 1);
		return true;
	}
	else if ((prevR - currentR == 2) && (prevC - currentC == -1))
	{
		move(2, -1);
		return true;
	}
	else if ((prevR - currentR == -2) && (prevC - currentC == 1))
	{
		move(-2, 1);
		return true;
	}
	else if ((prevR - currentR == -2) && (prevC - currentC == -1))
	{
		move(-2, -1);
		return true;
	}
	else if ((prevR - currentR == 1) && (prevC - currentC == 2))
	{
		move(1, 2);
		return true;
	}
	else if ((prevR - currentR == 1) && (prevC - currentC == -2))
	{
		move(1, -2);
		return true;
	}
	else if ((prevR - currentR == -1) && (prevC - currentC == 2))
	{
		move(-1, 2);
		return true;
	}
	else if ((prevR - currentR == -1) && (prevC - currentC == -2))
	{
		move(-1, -2);
		return true;
	}

	return false;
}

Bishop::Bishop(const char* texture, SDL_Renderer* ren, string bOw, int row, int collum, string name) : peice(texture, ren, bOw, row, collum, name)
{
}

bool Bishop::isMove(int prevR, int currentR, int prevC, int currentC, peice* arr[][8])
{
	bool friends = isFriendly(prevR, currentR, prevC, currentC, arr);
	if (friends == true)
	{
		return false;
	}
	//cout << "in here ";
	int rowDist = currentR - prevR;
	int collDist = currentC - prevC;
	int rowDirection;
	int collDirection;
	if (rowDist > 0)
	{
		rowDirection = 1;
	}
	else
	{
		rowDirection = -1;

	}
	if (collDist > 0)
	{
		collDirection = 1;
	}
	else
	{
		collDirection = -1;
	}
	rowDist = sqrt(rowDist * rowDist);
	collDist = sqrt(collDist * collDist);

	if (collDist == rowDist)
	{
		
		
		rowDist = sqrt(rowDist * rowDist);
		collDist = sqrt(collDist * collDist);
		for (int x = 1; x < rowDist; x++)
		{
		
			
			if (arr[prevR+(x*rowDirection)][prevC+(x*collDirection)]!=NULL)
			{
				
				return false;
			}
			
		}
		move(-(rowDist * rowDirection),-( collDist * collDirection));
		return true;

	}
	return false;
}

Queen::Queen(const char* texture, SDL_Renderer* ren, string bOw, int row, int collum, string name) : peice(texture, ren, bOw, row, collum, name)
{
	
}

bool Queen::isMove(int prevR, int currentR, int prevC, int currentC, peice* arr[][8])
{
	bool friends = isFriendly(prevR, currentR, prevC, currentC, arr);
	if (friends == true)
	{
		return false;
	}
	int diff;
	int direction = 1;
	
	if (prevR == currentR) //check if same row
	{
		diff = (currentC - prevC); // find how many collums they are apart 
		if (diff > 0)
		{
			
			direction = 1;//moving to the right
		}
		else if (diff < 0)
		{
		
			direction = -1; //moving to the left 
			diff = sqrt(diff * diff); // make the difference a positive number 
		}
		for (int x = 1; x < diff; x++)// start x at 1 so it doesnt check the starting square
		{
		
			int collski = (prevC + (x * direction));
		
			if (arr[prevR][collski] != NULL)//if array peice in the same row but collum staartiong at 1 to the direction of peice 
			{


				cout << arr[prevR][x]->Name << endl;
			
				return false;
			}

		}
		move(0, -(diff * direction));
		return true;

	}
	if (prevC == currentC) //check if same collum
	{
		diff = currentR - prevR; // find how many rows they are apart 
		if (diff > 0)
		{
			
			direction = 1;//moving to the up
		}
		else if (diff < 0)
		{
			
			direction = -1; //moving to the down 
			diff = sqrt(diff * diff); // make the difference a positive number 
		}
		for (int x = 1; x < diff; x++)// start x at 1 so it doesnt check the starting square
		{
		
			if (arr[(prevR + (x * direction))][prevC] != NULL)//if array peice in the same row but collum staartiong at 1 to the direction of peice 
			{
				cout << arr[prevR + (x * direction)][prevC]->Name << endl;
			
				return false;
			}

		}
		move(-(diff * direction), 0);
		return true;

	}
	int rowDist = currentR - prevR;
	int collDist = currentC - prevC;
	int rowDirection;
	int collDirection;
	if (rowDist > 0)
	{
		rowDirection = 1;
	}
	else
	{
		rowDirection = -1;

	}
	if (collDist > 0)
	{
		collDirection = 1;
	}
	else
	{
		collDirection = -1;
	}
	rowDist = sqrt(rowDist * rowDist);
	collDist = sqrt(collDist * collDist);

	if (collDist == rowDist)
	{
		

		rowDist = sqrt(rowDist * rowDist);
		collDist = sqrt(collDist * collDist);
		for (int x = 1; x < rowDist; x++)
		{

			//cout << "x is " << x << " y is " << y;
			if (arr[prevR + (x * rowDirection)][prevC + (x * collDirection)] != NULL)
			{
				
				return false;
			}

		}
		move(-(rowDist * rowDirection), -(collDist * collDirection));
		return true;

	}
	return false;


}

King::King(const char* texture, SDL_Renderer* ren, string bOw, int row, int collum, string name) : peice(texture, ren, bOw, row, collum, name)
{
}

bool King::isMove(int prevR, int currentR, int prevC, int currentC, peice* arr[][8])
{
	if (currentR - prevR == 1)
	{
		if (currentC - prevC == 1)
		{
			move(-1, -1);
			return true;
		}
		if (currentC - prevC == -1)
		{
			move(-1, 1);
			return true;
		}
		else
		{
			move(-1, 0);
			return true;
		}
	}
	if (currentR - prevR == -1)
	{
		if (currentC - prevC == 1)
		{
			move(1, -1);
			return true;
		}
		if (currentC - prevC == -1)
		{
			move(1, 1);
			return true;
		}
		else
		{
			move(1, 0);
			return true;
		}
	}
	else if (currentC - prevC == 1)
	{
		move(0, -1);
		return true;
	}
	else if (currentC - prevC == -1)
	{
		move(0, 1);
		return true;
	}
	return false;
}
