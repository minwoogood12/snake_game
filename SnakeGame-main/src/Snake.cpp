#include "Snake.hpp"
#include "Gate.hpp"
#include "Score.hpp"

Snake::Snake(pair<int, int> startNode) : headNode(startNode)
{
    // 뱀 초기화
    snakeBody.clear();
    snakeBody.push_back(startNode);
    snakeBody.push_back((pair<int, int>){startNode.first + 1, startNode.second});
    snakeBody.push_back((pair<int, int>){startNode.first + 2, startNode.second});

    headNode = startNode;
    preNode = make_pair(999999, 99999);

    direction = 'U';
}

// 뱀 그리기
void Snake::draw(Board &board)
{
    // 먼저 원래 뱀들 없애고 다시 그린다.
    board.removeSnakes();
    // head 그리기
    board.updateMap(headNode.first, headNode.second, 3);
    // 나머지 그리기
    for (int i = 1; i < snakeBody.size(); i++)
    {
        board.updateMap(snakeBody[i].first, snakeBody[i].second, 4);
    }

    board.drawMap();
}

void Snake::move(char input, Board &board, Gate &gate, Score &score)
{

    score.currentLength = snakeBody.size();
    // 무빙 메커니즘: 정해진 방향으로 앞에 있는 노드만 변하고, 뒤의 노드를 삭제하면 된다.
    // head가 움직일 노드만 방향별로 정해주면 된다.
    pair<int, int> tmpPoint;
    switch (input)
    {
    case 'U':
        tmpPoint = make_pair(headNode.first - 1, headNode.second);
        direction = 'U';
        break;
    case 'L':
        tmpPoint = make_pair(headNode.first, headNode.second - 1);
        direction = 'L';
        break;
    case 'R':
        tmpPoint = make_pair(headNode.first, headNode.second + 1);
        direction = 'R';
        break;
    case 'D':
        tmpPoint = make_pair(headNode.first + 1, headNode.second);
        direction = 'D';
        break;
    case 'X':
        move(direction, board, gate, score);
        return;
    }

    int collisionType = detectCollision(tmpPoint, board, gate, score);

    if (tmpPoint.first == preNode.first && tmpPoint.second == preNode.second)
    {
        die();
    }

    if (collisionType == 1)
    {
        // growth
        snakeBody.push_front(tmpPoint);
        // maxLength update
        if(score.maxLength < snakeBody.size()){
            score.maxLength = snakeBody.size();
        }
        score.growthCount++;
    }
    else if (collisionType == -1)
    {
        // poison
        snakeBody.push_front(tmpPoint);
        snakeBody.pop_back();
        snakeBody.pop_back();

        score.poisonCount++;
        if (snakeBody.size() < 3)
        {
            die();
        }
    }
    else if (collisionType == 0)
    {
        // 죽음.
        return;
    }
    else if (collisionType == 2)
    {
        // gate
        score.gateCount++;
        return;
    }
    else
    {
        snakeBody.push_front(tmpPoint);
        snakeBody.pop_back();
    }

    preNode = headNode;
    headNode = tmpPoint;
}

int Snake::detectCollision(pair<int, int> point, Board &board, Gate &gate, Score &score)
{
    if (board.findvalue(point.first, point.second) == 1 || board.findvalue(point.first, point.second) == 4)
    {
        die();
        return 0;
    }
    else if (board.findvalue(point.first, point.second) == 5)
    {
        return 1;
    }
    else if (board.findvalue(point.first, point.second) == 6)
    {
        return -1;
    }
    else if (board.findvalue(point.first, point.second) == 7)
    {
        moveToAnotherGate(point, board, gate, score);
        return 2;
    }
    return 100;
}

void Snake::moveToAnotherGate(pair<int, int> inGatePos, Board &board, Gate &gate, Score &score)
{
    gate.makeGateInvincible();

    pair<int, int> outGatePos;

    if (gate.firstGate.first == inGatePos.first && gate.firstGate.second == inGatePos.second)
    {
        outGatePos = gate.secondGate;
    }
    else
    {
        outGatePos = gate.firstGate;
    }

    // outgate 벽 위치?

    if (outGatePos.first == 0)
    {
        direction = 'D';
    }
    else if (outGatePos.first == board.getHeight()-1){
        direction = 'U';
    }
    else if(outGatePos.second == 0){
        direction = 'R';
    }
    else if(outGatePos.second == board.getWidth()-1){
        direction = 'L';
    }
    headNode = outGatePos;
    move(direction, board, gate, score);
    gate.makeGateUnInvincible();
}

void Snake::die()
{
    is_Dead = true;
}
