#pragma once
#include "Board.hpp"

class Score{
public:
    Score(Board &board);
    int maxLength = 3;
    int growthCount = 0;
    int poisonCount = 0;
    int gateCount = 0;
    int currentLength = 3;

    bool lengthMission = false;
    bool growthMission = false;
    bool poisonMission = false;
    bool gateMission = false;

    void showScore();
    bool isMisisonFinished();

private:
    Board board = Board(0, 0);
};