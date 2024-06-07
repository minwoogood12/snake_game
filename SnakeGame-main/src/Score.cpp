#include "Score.hpp"
#include <ncurses.h>

Score::Score(Board &board)
{

}

void Score::showScore()
{
    mvprintw(4, board.getWidth() * ADJUST_VAL + 2, "Score Board");
    mvprintw(5, board.getWidth() * ADJUST_VAL + 2, "B : %d / %d", currentLength, maxLength);
    mvprintw(6, board.getWidth() * ADJUST_VAL + 2, "+: %d", growthCount);
    mvprintw(7, board.getWidth() * ADJUST_VAL + 2, "-: %d", poisonCount);
    mvprintw(8, board.getWidth() * ADJUST_VAL + 2, "G: %d", gateCount);

    if (maxLength >= 10)
    {
        lengthMission = true;
    }
    if(growthCount >= 5){
        growthMission = true;
    }
    if(poisonCount >= 2){
        poisonMission = true;
    }
    if(gateCount >= 1){
        gateMission = true;
    }

    mvprintw(10, board.getWidth() * ADJUST_VAL + 2, "Mission");
    mvprintw(11, board.getWidth() * ADJUST_VAL + 2, "B: 10 (%c)", lengthMission ? 'v' : ' ');
    mvprintw(12, board.getWidth() * ADJUST_VAL + 2, "+: 5 (%c)", growthMission ? 'v' : ' ');
    mvprintw(13, board.getWidth() * ADJUST_VAL + 2, "-: 2 (%c)", poisonMission ? 'v' : ' ');
    mvprintw(14, board.getWidth() * ADJUST_VAL + 2, "G: 1 (%c)", gateMission ? 'v' : ' ');
}

bool Score::isMisisonFinished(){

    if(maxLength >= 4){
        return true;
    }
    else{
        return false;
    }
    /*
    if(lengthMission && growthMission && poisonMission && gateMission){
        return true;
    }
    else{
        return false;
    }
    */
}

