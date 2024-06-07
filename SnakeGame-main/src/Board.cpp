#include "Board.hpp"
#include <cstdlib>
#include <ctime>
#include "Item.hpp"
#include <thread>
#include <iostream>
#include <string>

using namespace std;

Board::Board(int height, int width) : height(height), width(width)
{
    // 맵 사이즈 지정.
    map.resize(height, std::vector<int>(width, 0));

    // Create window for board
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    board_win = newwin(height, width * ADJUST_VAL, (yMax / 2) - height / 2, (xMax / 2) - width * ADJUST_VAL / 2);

    // 맵의 테두리는 1이 입력되도록 설정한다.
    makeMapBorder();

    drawMap();
}

// 맵 테두리 업데이트
void Board::makeMapBorder()
{
    for (int x = 0; x < width; ++x)
    {
        updateMap(0, x, 1);          // 상단 벽
        updateMap(height - 1, x, 1); // 하단 벽
    }

    // 좌측과 우측 벽
    for (int y = 0; y < height; ++y)
    {
        updateMap(y, 0, 1);         // 좌측 벽
        updateMap(y, width - 1, 1); // 우측
    }

    // immune wall 생성
    updateMap(0, 0, 2);
    updateMap(0, width - 1, 2);
    updateMap(height - 1, 0, 2);
    updateMap(height - 1, width - 1, 2);
}

void Board::updateMap(int y, int x, int value)
{
    // 알맞은 값이 들어왔을때
    if (y >= 0 && y < height && x >= 0 && x < width)
    {
        map[y][x] = value;
        drawMap();
    }
}

// 맵 전체 그리기
void Board::drawMap()
{
    // 지우기
    werase(board_win);
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            drawCell(y, x, map[y][x]);
        }
    }
    wrefresh(board_win);
}

void Board::drawCell(int y, int x, int value)
{
    // 맵이 완벽한 사각형이 아니므로 X를 2배한 값을 사용한다.
    int fixedX = x * 2;
    start_color();
    // init_pair(pairingNum, 글자색, 배경색)
    // 배경 pair
    init_pair(1, COLOR_RED, COLOR_WHITE);
    // snake 머리 이유는 모르지만 RED가 초록색이 됨.
    init_pair(2, COLOR_RED, COLOR_YELLOW);
    // snake 몸통부분
    init_pair(3, COLOR_RED, COLOR_BLUE);

    init_pair(4, COLOR_RED, COLOR_GREEN);
    init_pair(5, COLOR_RED, COLOR_RED);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);

    switch (value)
    {
    case 0:
        mvwprintw(board_win, y, fixedX, " ");
        mvwprintw(board_win, y, fixedX + 1, " ");
        break;
    case 1:
        // 색쌍 활성화
        waddch(board_win, ' ' | COLOR_PAIR(1));
        waddch(board_win, ' ' | COLOR_PAIR(1));
        break;
    case 2:
        // 색쌍 활성화
        waddch(board_win, ' ' | COLOR_PAIR(1));
        waddch(board_win, ' ' | COLOR_PAIR(1));
        break;
    case 3:
        waddch(board_win, ' ' | COLOR_PAIR(2));
        waddch(board_win, ' ' | COLOR_PAIR(2));
        break;
    case 4:
        waddch(board_win, ' ' | COLOR_PAIR(3));
        waddch(board_win, ' ' | COLOR_PAIR(3));
        break;
    
    case 5:
        waddch(board_win, ' ' | COLOR_PAIR(4));
        waddch(board_win, ' ' | COLOR_PAIR(4));
        break;
    
    case 6:
        waddch(board_win, ' ' | COLOR_PAIR(5));
        waddch(board_win, ' ' | COLOR_PAIR(5));
        break;

    case 7:
        waddch(board_win, ' ' | COLOR_PAIR(6));
        waddch(board_win, ' ' | COLOR_PAIR(6));
        break;
    }
    
}

void Board::removeSnakes()
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(map[i][j] == 3 || map[i][j] == 4){
                map[i][j] = 0;
            }
        }
    }

}

int Board::findvalue(int y, int x){
    return map[y][x];
}

void::Board::updateItem(int duration){
    // add duration to each items
    for (int i = 0; i < items.size(); i++){
        items[i].addTime(duration);
        // check timeout
        if(items[i].getTime() >= 10000000){
            if(items[i].getType() == 0){
                growthCount -= 1;
            }
            else
            {
                poisonCount -= 1;
            }
            updateMap(items[i].getY(), items[i].getX(), 0);
            items.erase(items.begin() + i);
            
            i -= 1;
        }
    }

}

void Board::createItem(){
    // 일정 확률로 생성
    
    int percent = 60;
    srand(static_cast<unsigned int>(time(0)));
    int randomValue = rand() % 100;
    int itemType = rand() % 2;

    int count = 0;
    if (itemType == 0)
    {
        // growth
        count = growthCount;
    }
    else{
        // poison
        count = poisonCount;
    }
    // 객체 설정

    if (randomValue <= percent && count < 3)
    {
        while(true){
            int randY = rand() % height;
            int randX = rand() % width;
            if (findvalue(randY, randX) == 0)
            {
                // create
                Item item(randY, randX, itemType);
                items.push_back(item);

                if (itemType == 0)
                {
                    updateMap(randY, randX, 5);
                    growthCount++;
                }
                else if(itemType == 1){
                    updateMap(randY, randX, 6);
                    poisonCount++;
                }
                break;
            }
        }
    }
}

