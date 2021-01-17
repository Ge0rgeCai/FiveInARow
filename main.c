#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "main.h"

int main(){
	int runtime;						//判断程序继续运行
	//设置cmd窗口标题
	SetConsoleTitle("五子棋--CLang version");
	while(1){
		Init();
		runtime = RunGame();	
		if (runtime == 1) {
			printf("程序结束!\n");
			system("pause");
			break;
		}			//判断程序是否运行
	}
	return 0;
}

int RunGame(){
	while(1){
		int g_runtime;						//判断程序继续运行
		int runtimeCode;						//判断程序是否重新运行
		system("cls");
		system("color 80");
		DrawChessboard();
		g_runtime = g_Control(&g_cursorX, &g_cursorY);
		switch (g_runtime){
			case 1:
				return 1;
			case 3:
				if (g_currentGamer == 1){
					printf("游戏结束,黑子胜利!\n");
					printf("重新开始---R\n退出游戏---ESC\n\n");
					Sleep(1000);
					runtimeCode = gameEnd();
					switch (runtimeCode){
						case 0:
							return 0;
						case 1:
							return 1;
					}
				}else{
					printf("游戏结束,白子胜利!\n");
					printf("重新开始---R\n退出游戏---ESC\n\n");
					Sleep(1000);
					runtimeCode = gameEnd();
					switch (runtimeCode){
						case 0:
							return 0;
						case 1:
							return 1;
					}
				}
		}	
		if (g_runtime == 1) return 1;

	}
	return 0;
}

void Init(){
	memset(g_chessboard, 0, sizeof(g_chessboard));	

	g_currentGamer = 1;								//黑子优先

	//光标初始化
	g_cursorX = Chessboard / 2;
	g_cursorY = Chessboard / 2;

	g_count = 0;									//初始化游戏回合数
	g_Winner = 0;									//初始化赢家
}

void DrawChessboard(){
	for (int i = 0; i < Chessboard; i++){
		for (int j = 0; j < Chessboard; j++){
			if (i == g_cursorY && j == g_cursorX) printf("╋ ");
			else if (g_chessboard[j][i] == 1) printf("●");
			else if (g_chessboard[j][i] == 2) printf("○");
			else if (i == 0 && j == 0) printf("┏ ");
			else if (i == 0 && j == Chessboard -1) printf("┓");
			else if (i == Chessboard - 1 && j == 0) printf("┗ ");
			else if (i == Chessboard - 1 && j == Chessboard - 1) printf("┛");
			else if (i == 0) printf("┳ ");
			else if (i == Chessboard -1) printf("┻ ");
			else if (j == 0) printf("┣ ");
			else if (j == Chessboard -1) printf("┫");
			else printf("┼ ");
		}
		printf("\n");
	}
	printf("\n        ESC---退出程序\n");
}

int g_Control(int* X, int* Y){
	int keycode;						//键值
	keycode = getch();
	switch (keycode){
		case 75:						//向左
			*X = *X - 1;
			break;
		case 77:						//向右
			*X = *X + 1;
			break;
		case 72:						//向上
			*Y = *Y - 1;
			break;
		case 80:						//向下
			*Y = *Y + 1;
			break;
		case 27:
			return 1;
		case 3:
			return 1;
		case 32:
			if (PutDown()){
				//TODO:判断是否胜利
				//更新当前玩家
				g_Winner = Check();
				if (g_Winner == 1 || g_Winner == 2) return 3;	//返回 int 3 来跳出外层循环
				g_currentGamer = (g_currentGamer == 1) ? 2 : 1;//利用三目运算符来更新当前玩家
			}
			break;
	}
	if (*X < 0) *X = Chessboard - 1;
	if (*X > Chessboard - 1) *X = 0;
	if (*Y < 0) *Y = Chessboard - 1;
	if (*Y > Chessboard - 1) *Y = 0;
	
	return 0;
}

int PutDown(){
	if (g_chessboard[g_cursorX][g_cursorY] == 0){
		g_chessboard[g_cursorX][g_cursorY] = g_currentGamer; 
		//g_currentGamer++;
		return 1;
	}
	else return 0;
}

int Check(){
	int nHorizontal = 1;						//水平方向
	int nVertical = 1;							//竖直方向
	int nRightCant = 1;							//正斜向
	int nLeftCant = 1;							//反斜向

	//竖直方向
	//向下判断
	for (int i = 1; i < 5; i++){
		if (g_cursorY + i < Chessboard && g_chessboard[g_cursorX][g_cursorY + i] == g_currentGamer)
			nVertical++;
		else 
			break;
	}
	//向下判断
	for (int i = 1; i < 5; i++){
		if (g_cursorY - i > 0 && g_chessboard[g_cursorX][g_cursorY - i] == g_currentGamer)
			nVertical++;
		else 
			break;
	}
	if (nVertical >= 5) return g_currentGamer;

	//----------------------------------------------

	//水平方向
	//向右判断
	for (int i = 1; i < 5; i++){
		if (g_cursorX + i < Chessboard && g_chessboard[g_cursorX + i][g_cursorY] == g_currentGamer)
			nHorizontal++;
		else 
			break;
	}
	//向左判断
	for (int i = 1; i < 5; i++){
		if (g_cursorX - i > 0 && g_chessboard[g_cursorX - i][g_cursorY] == g_currentGamer)
			nHorizontal++;
		else 
			break;
	}
	if (nHorizontal >= 5) return g_currentGamer;

	//----------------------------------------------

	//正斜向
	//向上判断
	for (int i = 1; i < 5; i++){
		if (g_cursorX + i < Chessboard && g_cursorY - i > 0 && g_chessboard[g_cursorX + i][g_cursorY - i] == g_currentGamer)
			nRightCant++;
		else 
			break;
	}
	//向下判断
	for (int i = 1; i < 5; i++){
		if (g_cursorX - i > 0 && g_cursorY + i < Chessboard && g_chessboard[g_cursorX - i][g_cursorY + i] == g_currentGamer)
			nRightCant++;
		else 
			break;
	}
	if (nRightCant >= 5) return g_currentGamer;

	//----------------------------------------------

	//反斜向
	//向上判断
	for (int i = 1; i < 5; i++){
		if (g_cursorX - i > 0 && g_cursorY - i > 0 && g_chessboard[g_cursorX - i][g_cursorY - i] == g_currentGamer)
			nLeftCant++;
		else 
			break;
	}
	//向下判断
	for (int i = 1; i < 5; i++){
		if (g_cursorX + i < Chessboard && g_cursorY + i < Chessboard && g_chessboard[g_cursorX + i][g_cursorY + i] == g_currentGamer)
			nLeftCant++;
		else 
			break;
	}
	if (nLeftCant >= 5) return g_currentGamer;

	return 0;
}

int gameEnd(){                                  //游戏结束后的行为限制
	int keycode;
	while(1){
		keycode = getch();
		switch(keycode){
			case 3:
				return 1;
			case 27:
				return 1;
			case 114:
				return 0;
			case 82:
				return 0;
			default:
				break;
		}
	}
	return 0;
}