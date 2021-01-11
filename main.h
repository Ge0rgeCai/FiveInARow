#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <Windows.h>

#define Chessboard 15								//棋盘大小

int g_chessboard[Chessboard][Chessboard];			//棋盘内容

int RunGame();										//游戏开始
int g_currentGamer;									//游戏玩家 黑子为1，白子为2
int g_cursorX, g_cursorY;							//光标位置
int g_count;										//游戏回合数

void Init();										//游戏初始化
void DrawChessboard();								//绘制棋盘
int g_Control(int* X, int* Y);                      //控制光标
int PutDown();                                       //下子

#endif
