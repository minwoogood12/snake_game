#pragma once

#include "Board.hpp"
#include "Snake.hpp"
#include "Gate.hpp"
#include "Score.hpp"

class SnakeGame{
public:
    SnakeGame();
    void startGame();
    void resetGame();

private:
    Board board;
    Snake snake;
    Gate gate;
    Score score;
    bool isRunning;
    int gameDelay;

    int gateTime;
    int gateTimeCount = 0;

    bool isGateMade = false;

    void showFailMessage();
    void update();
    void endGame();
};