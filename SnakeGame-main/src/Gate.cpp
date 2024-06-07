#include "Gate.hpp"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <iostream>
#include <string>

void Gate::makeGate(Board &board)
{
    board.makeMapBorder();
    firstGate = makeGatePos(board);
    secondGate = makeGatePos(board);
}

pair<int, int> Gate::makeGatePos(Board &board){
  
   srand(static_cast<unsigned int>(time(0)));
  
    while (true)
    {
        int randY;
        int randX;

        int wallPosType = rand() % 4;
        switch (wallPosType)
        {
        case 0:
            randX = 0;
            randY = rand() % board.getHeight();
            break;
        case 1:
            randY = board.getHeight() - 1;
            randX = rand() % board.getWidth();
            break;
        case 2:
            randX = board.getWidth() - 1;
            randY = rand() % board.getHeight();
            break;
        case 3:
            randY = 0;
            randX = rand() % board.getWidth();
            break;
        }

        if (board.findvalue(randY, randX) == 1)
        {
            board.updateMap(randY, randX, 7);
            return (pair<int, int>){randY, randX};
        }
    }
}

void Gate::checkGate(Board &board){
    if (lifeTime >= 10000000 && !isInvincible)
    {
        board.updateMap(firstGate.first, firstGate.second, 1);
        board.updateMap(secondGate.first, secondGate.second, 1);
        lifeTime = 0;
        makeGate(board);
    }
}

void Gate::addTime(int duration){
    if(!isInvincible){
        lifeTime += duration;
    }
}

void Gate::makeGateInvincible(){
    lifeTime = 0;
    isInvincible = true;
}

void Gate::makeGateUnInvincible(){
    isInvincible = false;
}