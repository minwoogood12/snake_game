#pragma once

#include "Board.hpp"
#include "Gate.hpp"
#include "Score.hpp"
#include <algorithm>
#include <deque>

using namespace std;

class Snake
{
public:
    Snake(pair<int, int> startNode);
    pair<int, int> getHead() { return headNode; }
    void move(char input, Board & board, Gate &gate, Score &score);
    void draw(Board &board);
    bool isDead() const { return is_Dead; }
    deque<pair<int, int>> getSnakeBody() { return snakeBody; };

private:
    deque<pair<int, int>> snakeBody;
    pair<int, int> headNode;
    pair<int, int> preNode;
    char direction;
    bool is_Dead = false; // 실패 여부를 나타내는 변수
    int detectCollision(pair<int, int> point, Board &board, Gate &gate, Score &score);
    void moveToAnotherGate(pair<int, int> inGatePos, Board &board, Gate &gate, Score &score);
    void die();
    };