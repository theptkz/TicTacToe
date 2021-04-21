//
//  AI.hpp
//  TicTacToePractise
//
//  Created by Sonar Systems on 17/03/2016.
//
//

#pragma once

#include "cocos2d.h"
#include <vector>
#include <array>

class AI
{
public:
    AI();
    
    int PlacePiece( int post[3][3], int moveIndex );
private:
    int minimax(int ( post )[3][3], int depth, bool isAI);
    bool rowCrossed(int ( post )[3][3]); 
    bool columnCrossed(int ( post )[3][3]); 
    bool diagonalCrossed(int ( post )[3][3]); 
    bool gameOver(int ( post )[3][3]);

    int aiPiece;
    int playerPiece;
    
    std::vector<std::array<int, 6>> checkMatchVector;

};