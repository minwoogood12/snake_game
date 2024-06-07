#pragma once
#include <ncurses.h>
#include <vector>
#include "Item.hpp"

// 실제 크기를 의미한다. width랑 height랑 다르니까.
// width가 height의 2배정도를 가져야만 동등해진다.
#define ADJUST_VAL 2

using namespace std;

class Board
{
public:
    Board(int height, int width);
    vector<vector<int>> map;
    void drawMap();
    void updateMap(int y, int x, int value);
    void removeSnakes();
    int getHeight() const { return height; }
    int getWidth() const { return width; }
    int findvalue(int y, int x);
    void createItem();
    void updateItem(int duration);
    void makeMapBorder();

private:
    
    int height, width;
    int growthCount = 0;
    int poisonCount = 0;
    WINDOW *board_win;

    void drawCell(int y, int x, int value);
    

    vector<Item> items;
};
