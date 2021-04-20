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

AI::AI( int playerPiece )
{
    this->playerPiece = playerPiece;
    
    if ( O_PIECE == playerPiece )
    {
        aiPiece = X_PIECE;
    }
    else
    {
        aiPiece = O_PIECE;
    }
    
    checkMatchVector.push_back( { 0, 2, 1, 2, 2, 2 } );
    checkMatchVector.push_back( { 0, 2, 0, 1, 0, 0 } );
    checkMatchVector.push_back( { 0, 2, 1, 1, 2, 0 } );
    checkMatchVector.push_back( { 2, 2, 1, 2, 0, 2 } );
    checkMatchVector.push_back( { 2, 2, 2, 1, 2, 0 } );
    checkMatchVector.push_back( { 2, 2, 1, 1, 0, 0 } );
    checkMatchVector.push_back( { 0, 0, 0, 1, 0, 2 } );
    checkMatchVector.push_back( { 0, 0, 1, 0, 2, 0 } );
    checkMatchVector.push_back( { 0, 0, 1, 1, 2, 2 } );
    checkMatchVector.push_back( { 2, 0, 2, 1, 2, 2 } );
    checkMatchVector.push_back( { 2, 0, 1, 0, 0, 0 } );
    checkMatchVector.push_back( { 2, 0, 1, 1, 0, 2 } );
    checkMatchVector.push_back( { 0, 1, 1, 1, 2, 1 } );
    checkMatchVector.push_back( { 1, 2, 1, 1, 1, 0 } );
    checkMatchVector.push_back( { 2, 1, 1, 1, 0, 1 } );
    checkMatchVector.push_back( { 1, 0, 1, 1, 1, 2 } );
    checkMatchVector.push_back( { 0, 1, 2, 1, 1, 1 } );
    checkMatchVector.push_back( { 1, 2, 1, 0, 1, 1 } );
    checkMatchVector.push_back( { 0, 2, 2, 0, 1, 1 } );
    checkMatchVector.push_back( { 2, 2, 0, 0, 1, 1 } );
    checkMatchVector.push_back( { 0, 2, 2, 2, 1, 2 } );
    checkMatchVector.push_back( { 0, 0, 2, 0, 1, 0 } );
    checkMatchVector.push_back( { 0, 2, 0, 0, 0, 1 } );
    checkMatchVector.push_back( { 2, 2, 2, 0, 2, 1 } );
}

void AI::PlacePiece( int ( *gridArray )[3][3], cocos2d::Sprite *gridPieces[3][3], int *gameState )
{
    try
    {
        // check if AI can win
        for ( int i = 0; i < checkMatchVector.size( ); i++ )
        {
            CheckSection( checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2], checkMatchVector[i][3], checkMatchVector[i][4], checkMatchVector[i][5], AI_PIECE, gridArray, gridPieces );
        }

        // check if player can win
        for ( int i = 0; i < checkMatchVector.size( ); i++ )
        {
            CheckSection( checkMatchVector[i][0], checkMatchVector[i][1], checkMatchVector[i][2], checkMatchVector[i][3], checkMatchVector[i][4], checkMatchVector[i][5], PLAYER_PIECE, gridArray, gridPieces );
        }
    
        // check if center is empty
        CheckIfPieceIsEmpty( 1, 1, gridArray, gridPieces );
        
        // check if a corner is empty
        CheckIfPieceIsEmpty( 0, 2, gridArray, gridPieces );
        CheckIfPieceIsEmpty( 2, 2, gridArray, gridPieces );
        CheckIfPieceIsEmpty( 0, 0, gridArray, gridPieces );
        CheckIfPieceIsEmpty( 2, 0, gridArray, gridPieces );
        
        // check for any other empty piece
        CheckIfPieceIsEmpty( 1, 2, gridArray, gridPieces );
        CheckIfPieceIsEmpty( 0, 1, gridArray, gridPieces );
        CheckIfPieceIsEmpty( 2, 1, gridArray, gridPieces );
        CheckIfPieceIsEmpty( 1, 0, gridArray, gridPieces );
    }
    catch ( int error )
    {
        
    }
    
    *gameState = STATE_PLAYING;
}

void AI::CheckSection( int x1, int y1, int x2, int y2, int X, int Y, int pieceToCheck, int ( *gridArray )[3][3], cocos2d::Sprite *gridPieces[3][3] )
{
    // check if 2 pieces match
    if ( ( *gridArray )[x1][y1] == pieceToCheck && ( *gridArray )[x2][y2] == pieceToCheck )
    {
        if ( EMPTY_PIECE == ( *gridArray )[X][Y] )
        {
            ( *gridArray )[X][Y] = AI_PIECE;
            gridPieces[X][Y]->setTexture( O_PIECE_FILEPATH );
            
            gridPieces[X][Y]->setVisible( true );
            
            gridPieces[X][Y]->runAction( cocos2d::FadeIn::create( PIECE_FADE_IN_TIME ) );
            
            throw -1;
        }
    }
}

void AI::CheckIfPieceIsEmpty( int X, int Y, int ( *gridArray )[3][3], cocos2d::Sprite *gridPieces[3][3] )
{
    // check if
    if ( EMPTY_PIECE == ( *gridArray )[X][Y] )
    {
        ( *gridArray )[X][Y] = AI_PIECE;
        gridPieces[X][Y]->setTexture( O_PIECE_FILEPATH );
        
        gridPieces[X][Y]->setVisible( true );
        
        gridPieces[X][Y]->runAction( cocos2d::FadeIn::create( PIECE_FADE_IN_TIME ) );
        
        throw -2;
    }
}

int minimax(char board[][SIDE], int depth, bool isAI)
{
	int score = 0;
	int bestScore = 0;
	if (gameOver(board) == true)
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
				for(int i=0; i<SIDE; i++)
				{
					for(int j=0; j<SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = COMPUTERMOVE;
							score = minimax(board, depth + 1, false);
							board[i][j] = ' ';
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
				for (int i = 0; i < SIDE; i++)
				{
					for (int j = 0; j < SIDE; j++)
					{
						if (board[i][j] == ' ')
						{
							board[i][j] = HUMANMOVE;
							score = minimax(board, depth + 1, true);
							board[i][j] = ' ';
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

// Function to calculate best move
int bestMove(char board[][SIDE], int moveIndex)
{
	int x = -1, y = -1;
	int score = 0, bestScore = -999;
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			if (board[i][j] == ' ')
			{
				board[i][j] = COMPUTERMOVE;
				score = minimax(board, moveIndex+1, false);
				board[i][j] = ' ';
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
