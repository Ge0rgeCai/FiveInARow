#ifndef _MAIN_H_
#define _MAIN_H_
#include <stdio.h>
#include <Windows.h>

#define Chessboard 15								//���̴�С

int g_chessboard[Chessboard][Chessboard];			//��������

int RunGame();										//��Ϸ��ʼ
int g_currentGamer;									//��Ϸ��� ����Ϊ1������Ϊ2
int g_cursorX, g_cursorY;							//���λ��
int g_count;										//��Ϸ�غ���

void Init();										//��Ϸ��ʼ��
void DrawChessboard();								//��������
int g_Control(int* X, int* Y);                      //���ƹ��
int PutDown();                                      //����
int Check();                                        //�ж���Ϸʤ��
int g_Winner;                                       //Ӯ��
int gameEnd();                                  //��Ϸ���������Ϊ����

#endif
