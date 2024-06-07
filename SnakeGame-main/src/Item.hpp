#pragma once
#include <unistd.h>

class Item{
public:
    Item(int y, int x, int type){
        this->type = type;
        this->y = y;
        this->x = x;
    }
    int getTime() { return time; }
    void addTime(int duration) { time += duration; }
    int getX() { return x; }
    int getY() { return y; }
    int getType() { return type; }

private:
    int time = 0;
    // 0이면 growth, 1이면 poison
    int type = 0;
    int x, y;
};
