#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "main.h"

int main(){
	int runtime;						//�жϳ����������
	//����cmd���ڱ���
	SetConsoleTitle("������--CLang version");
	while(1){
		Init();
		runtime = RunGame();	
		if (runtime == 1) {
			printf("�������!\n");
			system("pause");
			break;
		}			//�жϳ����Ƿ�����
	}
	return 0;
}

int RunGame(){
	while(1){
		int g_runtime;						//�жϳ����������
		int runtimeCode;						//�жϳ����Ƿ���������
		system("cls");
		system("color 80");
		DrawChessboard();
		g_runtime = g_Control(&g_cursorX, &g_cursorY);
		switch (g_runtime){
			case 1:
				return 1;
			case 3:
				if (g_currentGamer == 1){
					printf("��Ϸ����,����ʤ��!\n");
					printf("���¿�ʼ---R\n�˳���Ϸ---ESC\n\n");
					Sleep(1000);
					runtimeCode = gameEnd();
					switch (runtimeCode){
						case 0:
							return 0;
						case 1:
							return 1;
					}
				}else{
					printf("��Ϸ����,����ʤ��!\n");
					printf("���¿�ʼ---R\n�˳���Ϸ---ESC\n\n");
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

	g_currentGamer = 1;								//��������

	//����ʼ��
	g_cursorX = Chessboard / 2;
	g_cursorY = Chessboard / 2;

	g_count = 0;									//��ʼ����Ϸ�غ���
	g_Winner = 0;									//��ʼ��Ӯ��
}

void DrawChessboard(){
	for (int i = 0; i < Chessboard; i++){
		for (int j = 0; j < Chessboard; j++){
			if (i == g_cursorY && j == g_cursorX) printf("�� ");
			else if (g_chessboard[j][i] == 1) printf("��");
			else if (g_chessboard[j][i] == 2) printf("��");
			else if (i == 0 && j == 0) printf("�� ");
			else if (i == 0 && j == Chessboard -1) printf("��");
			else if (i == Chessboard - 1 && j == 0) printf("�� ");
			else if (i == Chessboard - 1 && j == Chessboard - 1) printf("��");
			else if (i == 0) printf("�� ");
			else if (i == Chessboard -1) printf("�� ");
			else if (j == 0) printf("�� ");
			else if (j == Chessboard -1) printf("��");
			else printf("�� ");
		}
		printf("\n");
	}
	printf("\n        ESC---�˳�����\n");
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
				g_Winner = Check();
				if (g_Winner == 1 || g_Winner == 2) return 3;	//���� int 3 ���������ѭ��
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

int Check(){
	int nHorizontal = 1;						//ˮƽ����
	int nVertical = 1;							//��ֱ����
	int nRightCant = 1;							//��б��
	int nLeftCant = 1;							//��б��

	//��ֱ����
	//�����ж�
	for (int i = 1; i < 5; i++){
		if (g_cursorY + i < Chessboard && g_chessboard[g_cursorX][g_cursorY + i] == g_currentGamer)
			nVertical++;
		else 
			break;
	}
	//�����ж�
	for (int i = 1; i < 5; i++){
		if (g_cursorY - i > 0 && g_chessboard[g_cursorX][g_cursorY - i] == g_currentGamer)
			nVertical++;
		else 
			break;
	}
	if (nVertical >= 5) return g_currentGamer;

	//----------------------------------------------

	//ˮƽ����
	//�����ж�
	for (int i = 1; i < 5; i++){
		if (g_cursorX + i < Chessboard && g_chessboard[g_cursorX + i][g_cursorY] == g_currentGamer)
			nHorizontal++;
		else 
			break;
	}
	//�����ж�
	for (int i = 1; i < 5; i++){
		if (g_cursorX - i > 0 && g_chessboard[g_cursorX - i][g_cursorY] == g_currentGamer)
			nHorizontal++;
		else 
			break;
	}
	if (nHorizontal >= 5) return g_currentGamer;

	//----------------------------------------------

	//��б��
	//�����ж�
	for (int i = 1; i < 5; i++){
		if (g_cursorX + i < Chessboard && g_cursorY - i > 0 && g_chessboard[g_cursorX + i][g_cursorY - i] == g_currentGamer)
			nRightCant++;
		else 
			break;
	}
	//�����ж�
	for (int i = 1; i < 5; i++){
		if (g_cursorX - i > 0 && g_cursorY + i < Chessboard && g_chessboard[g_cursorX - i][g_cursorY + i] == g_currentGamer)
			nRightCant++;
		else 
			break;
	}
	if (nRightCant >= 5) return g_currentGamer;

	//----------------------------------------------

	//��б��
	//�����ж�
	for (int i = 1; i < 5; i++){
		if (g_cursorX - i > 0 && g_cursorY - i > 0 && g_chessboard[g_cursorX - i][g_cursorY - i] == g_currentGamer)
			nLeftCant++;
		else 
			break;
	}
	//�����ж�
	for (int i = 1; i < 5; i++){
		if (g_cursorX + i < Chessboard && g_cursorY + i < Chessboard && g_chessboard[g_cursorX + i][g_cursorY + i] == g_currentGamer)
			nLeftCant++;
		else 
			break;
	}
	if (nLeftCant >= 5) return g_currentGamer;

	return 0;
}

int gameEnd(){                                  //��Ϸ���������Ϊ����
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