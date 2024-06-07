#pragma once
#include <algorithm>
#include <deque>
#include "Board.hpp"

using namespace std;
class Gate
{
public:
    void makeGate(Board &board);
    void drawGate(Board &board);
    void addTime(int duration);
    pair<int, int> firstGate;
    pair<int, int> secondGate;
    pair<int, int> makeGatePos(Board &board);
    void checkGate(Board &board);
    void makeGateInvincible();
    void makeGateUnInvincible();

private:
    int lifeTime = 0;
    bool isInvincible = false;
};