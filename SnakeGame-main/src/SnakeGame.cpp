#include "SnakeGame.hpp"
#include "Snake.hpp"
#include <unistd.h>
#include "Input.h"
#include "Board.hpp"

#include <iostream>

using namespace std;

SnakeGame::SnakeGame() : board(0, 0), snake((pair<int, int>){0, 0}), score(score)
{
    initscr();

    isRunning = true;
    // gameDelay 설x정
    gameDelay = 500000;

    // 게이트 나오는 시간
    gateTime = 50000000;
    gateTimeCount = 0;

    // 전체 판의 크기
    int board_width = 21;
    int board_height = 21;

    // Board를 생성하고 그림.
    board = Board(board_height, board_width);

    score = Score(board);

    // 플레이어(뱀) 생성
    snake = Snake(pair<int, int>{board_height / 2, board_width / 2});

    gate = Gate();

    snake.draw(board);

    // 맵 그리기
    board.drawMap();
}

// 게임 시작
void SnakeGame::startGame()
{
    noecho();
    // 커서 감추기
    curs_set(0);
    // keypad 활성화
    keypad(stdscr, TRUE);
    // 비동기 활성
    nodelay(stdscr, TRUE);

    while (isRunning)
    {
        update();
        usleep(gameDelay);
    }
    endwin();
}

void SnakeGame::update()
{
    gateTimeCount += gameDelay;
    if(gateTimeCount >= gateTime && !isGateMade){
        gate.makeGate(board);
        isGateMade = true;
    }
    // 아이템 생성, 죽었는지 확인, 플레이어 움직임 등등
    board.createItem();
    snake.move(getInput(), board, gate, score);
    
    board.updateItem(gameDelay);
    snake.draw(board);
    gate.addTime(gameDelay);
    gate.checkGate(board);

    // 스코어 메시지 출력
    score.showScore();
    // 게임 성공!
    if(score.isMisisonFinished()){
        mvprintw(16, board.getHeight() * ADJUST_VAL + 2, "Mission Completed");
        endGame();
    }

    if(snake.isDead()){
        showFailMessage();
    }
    if (isRunning)
    {
        board.drawMap();
    }
}



void SnakeGame::showFailMessage()
{
    // 실패 여부를 확인하고 실패 메시지를 출력
    if (snake.isDead())
    {
        // 게임 오버 메시지 출력
        mvprintw(0, board.getWidth() * ADJUST_VAL + 2, "FAIL!");
        endGame();

        // 화면 갱신
        refresh();        
    }
}

void SnakeGame::endGame(){
    mvprintw(1, board.getWidth() * ADJUST_VAL + 2, "REGAME : press 'r' button.");
    mvprintw(2, board.getWidth() * ADJUST_VAL + 2, "EXIT : press 'x' button.");

    // r 키 입력 대기
    char input;
    while (true)
    {
        input = getch();
        if (input == 'r')
        {
            // 게임 다시 시작
            resetGame();
            break;
        }
        else if (input == 'x')
        {
            // 게임 종료
            isRunning = false;
            break;
        }
    }
}

void SnakeGame::resetGame()
{
    mvprintw(16, board.getHeight() * ADJUST_VAL + 2, "                 ");
    // 뱀 초기 위치 설정
    int board_width = 21;
    int board_height = 21;
    score = Score(board);
    snake = Snake(pair<int, int>{board_height / 2, board_width / 2});

    isGateMade = false;
    // 게임 오버 메시지 지우기
    mvprintw(0, board.getWidth() * ADJUST_VAL + 2, "        ");
    mvprintw(1, board.getWidth() * ADJUST_VAL + 2, "                               ");
    mvprintw(2, board.getWidth() * ADJUST_VAL + 2, "                               ");

    // 게임 상태 초기화
    isRunning = true;
    // 보드 초기화
    board = Board(board_height, board_width);
}