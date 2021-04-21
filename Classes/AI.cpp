//
//  AI.cpp
//  TicTacToePractise
//
//  Created by Sonar Systems on 17/03/2016.
//
//

#include "AI.h"
#include "Definitions.h"

#include <iostream>

using namespace std;
AI::AI( )
{ 
    if ( O_PIECE == playerPiece )
    {
        aiPiece = X_PIECE;
    }
    else
    {
        aiPiece = O_PIECE;
    }
}

bool AI::rowCrossed(int post[3][3]) 
{ 
	for (int i=0; i<3; i++) 
	{ 
		if (post[i][0] ==  post[i][1] && 
			 post[i][1] ==  post[i][2] && 
			 post[i][0] != 99) 
			return (true); 
	} 
	return(false); 
} 

// A function that returns true if any of the column 
// is crossed with the same player's move 
bool AI::columnCrossed(int post[3][3]) 
{ 
	for (int i=0; i<3; i++) 
	{ 
		if ( post[0][i] ==  post[1][i] && 
			 post[1][i] ==  post[2][i] && 
			post[0][i] != 99) 
			return (true); 
	} 
	return(false); 
} 

// A function that returns true if any of the diagonal 
// is crossed with the same player's move 
bool AI::diagonalCrossed(int post[3][3]) 
{ 
	if ( post[0][0] ==  post[1][1] && 
		 post[1][1] ==  post[2][2] && 
		 post[0][0] != 99) 
		return(true); 
		
	if ( post[0][2] ==  post[1][1] && 
		 post[1][1] ==  post[2][0] && 
		 post[0][2] != 99) 
		return(true); 

	return(false); 
} 

// A function that returns true if the game is over 
// else it returns a false 
bool AI::gameOver(int post[3][3]) 
{ 
	return(AI::rowCrossed(post) || AI::columnCrossed(post) || AI::diagonalCrossed(post) ); 
}

int AI::minimax(int post[3][3],int depth, bool isAI)
{
	int score = 0;
	int bestScore = 0;
	if (AI::gameOver(post) == true)
	{
		if (isAI == true)
			return -1;
		if (isAI == false)
			return +1;
	}
	else
	{
		if(depth < 9)
		{
			if(isAI == true)
			{
				bestScore = -999;
				for(int i=0; i<3; i++)
				{
					for(int j=0; j<3; j++)
					{
						if (post[i][j] == 99)
						{
							post[i][j] = 1;
							score = minimax(post, depth + 1, false);
							post[i][j] = 99;
							if(score > bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
			else
			{
				bestScore = 999;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						if (post[i][j] == 99)
						{
							post[i][j] = 0;
							score = AI::minimax(post, depth + 1, true);
							post[i][j] = 99;
							if (score < bestScore)
							{
								bestScore = score;
							}
						}
					}
				}
				return bestScore;
			}
		}
		else
		{
			return 0;
		}
	}
}

int AI::PlacePiece( int post[3][3], int moveIndex )
{
    int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (post[i][j] == 99)
			{
				post[i][j] = 1;
				score = AI::minimax(post, moveIndex+1, false);
				post[i][j] = 99;
				if(score > bestScore)
				{
					bestScore = score;
					x = i;
					y = j;
				}
            }
		}
	}
    return x*3+y;
}

