#include <stdio.h>
#include <Windows.h>
#include <Conio.h>
#include "main.h"

int main(){
	int runtime;						//�жϳ����������
	//����cmd���ڱ���
	SetConsoleTitle("������--CLang version");
	while(1){
		Init();
		runtime = RunGame();	
		if (runtime == 1) system("pause");			//�жϳ����Ƿ�����
	}
	return 0;
}

int RunGame(){
	while(1){
		int g_runtime;						//�жϳ����������
		system("cls");
		DrawChessboard();
		g_runtime = g_Control(&g_cursorX, &g_cursorY);
		printf("%d\n",g_runtime);	
		if (g_runtime == 1) return 1;
		
	}
	return 0;
}

void Init(){
	memset(g_chessboard, 0, sizeof(g_chessboard));	

	g_currentGamer = 1;								//��������

	//����ʼ��
	g_cursorX = Chessboard / 2;
	g_cursorY = Chessboard / 2;

	g_count = 0;									//��ʼ����Ϸ�غ���
}

void DrawChessboard(){
	for (int i = 0; i < Chessboard; i++){
		for (int j = 0; j < Chessboard; j++){
			if (i == g_cursorY && j == g_cursorX) printf(" ��" );
			else if (g_chessboard[j][i] == 1) printf(" ��");
			else if (g_chessboard[j][i] == 2) printf(" ��");
			else if (i == 0 && j == 0) printf(" ��");
			else if (i == 0 && j == Chessboard -1) printf(" �� ");
			else if (i == Chessboard - 1 && j == 0) printf(" ��");
			else if (i == Chessboard - 1 && j == Chessboard - 1) printf(" �� ");
			else if (i == 0) printf(" ��");
			else if (i == Chessboard -1) printf(" ��");
			else if (j == 0) printf(" ��");
			else if (j == Chessboard -1) printf(" �� ");
			else printf(" ��");
		}
		printf("\n");
	}
}

int g_Control(int* X, int* Y){
	int keycode;						//��ֵ
	keycode = getch();
	switch (keycode){
		case 75:						//����
			*X = *X - 1;
			break;
		case 77:						//����
			*X = *X + 1;
			break;
		case 72:						//����
			*Y = *Y - 1;
			break;
		case 80:						//����
			*Y = *Y + 1;
			break;
		case 27:
			return 1;
		case 3:
			return 1;
		case 32:
			if (PutDown()){
				//TODO:�ж��Ƿ�ʤ��
				//���µ�ǰ���
				g_currentGamer = (g_currentGamer == 1) ? 2 : 1;//������Ŀ����������µ�ǰ���
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