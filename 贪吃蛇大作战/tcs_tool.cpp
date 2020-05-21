//��ʾ���ߺ�����
//ȡ���������ҵ���ߺ���
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <tchar.h>
#include "declare.h"
using namespace std;

/* ��̬ȫ�֣�ֻ�ڱ�Դ�����ļ�����Ч��Ϊ��ֹͬ������̬ȫ��һ�㽨���__��Ϊ��������ʼ�� */
static const HANDLE __hout = GetStdHandle(STD_OUTPUT_HANDLE);		//ȡ��׼����豸��Ӧ�ľ��
static const HANDLE __hin = GetStdHandle(STD_INPUT_HANDLE);			//ȡ��׼�����豸��Ӧ�ľ��

/***************************************************************************
  �������ƣ�
  ��    �ܣ������system("cls")һ���Ĺ��ܣ���Ч�ʸ�
  ���������
  �� �� ֵ��
  ˵    �������������Ļ���������������ǿɼ���������(ʹ�õ�ǰ��ɫ)
***************************************************************************/
void cls(void)
{
	COORD coord = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO binfo; /* to get buffer info */
	DWORD num;

	/* ȡ��ǰ��������Ϣ */
	GetConsoleScreenBufferInfo(__hout, &binfo);
	/* ����ַ� */
	FillConsoleOutputCharacter(__hout, (TCHAR)' ', binfo.dwSize.X * binfo.dwSize.Y, coord, &num);
	/* ������� */
	FillConsoleOutputAttribute(__hout, binfo.wAttributes, binfo.dwSize.X * binfo.dwSize.Y, coord, &num);

	/* ���ص�(0,0) */
	SetConsoleCursorPosition(__hout, coord);
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ָ������ɫ
  ���������const int bg_color ������ɫ��0-15��
			const int fg_color ��ǰ��ɫ��0-15��
  �� �� ֵ��
  ˵    ������ɫ��ȡֵ�ɱ���ɫ+ǰ��ɫ��ɣ���16��
			fg_color��0-7    ��   ��   ��   ��   ��   ��   ��   ��
					  8-15 ���� ���� ���� ���� ���� ���� ���� ����
			bg_color��0-7    ��   ��   ��   ��   ��   ��   ��   ��
					  8-15 ���� ���� ���� ���� ���� ���� ���� ����
			���յ���ɫΪ ����ɫ*16+ǰ��ɫ
***************************************************************************/
void setcolor(const int bg_color, const int fg_color)
{
	SetConsoleTextAttribute(__hout, bg_color * 16 + fg_color);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�������ƶ���ָ��λ��
  ���������const int X       ��X�����꣨�У�
			const int Y       ��Y�����꣨�У�
  �� �� ֵ��
  ˵    ������Ļ���Ͻ�����Ϊ(0,0)����cmd���ڵĴ�Сδ������������£�Win10Ϊ��
			����x�ᣬ��Ӧ��(0-119)
			����y�ᣬ��Ӧ��(0-29)
***************************************************************************/
void gotoxy(const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(__hout, coord);
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȡ��ǰ�������λ�õ�����ֵ
  ���������int &x            ��ȡ�õ�X�����꣨�У�
			int &y            ��ȡ�õ�Y�����꣨�У�
  �� �� ֵ��
  ˵    �����β��е�&��ʾ���ã������»ὲ���������βε�ֵ���Է��ظ�ʵ��
***************************************************************************/
void getxy(int& x, int& y)
{
	CONSOLE_SCREEN_BUFFER_INFO binfo;
	GetConsoleScreenBufferInfo(__hout, &binfo);

	x = binfo.dwCursorPosition.X;
	y = binfo.dwCursorPosition.Y;

	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ù��״̬����ʾ/����ʾ/ȫ��/���/���ߵȣ�
  ���������const int option��Ҫ���õĹ��״̬
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void setcursor(const int options)
{
	CONSOLE_CURSOR_INFO cursor_info;

	switch (options) {
	case CURSOR_VISIBLE_FULL:
		cursor_info.bVisible = 1;
		cursor_info.dwSize = 100;
		break;
	case CURSOR_VISIBLE_HALF:
		cursor_info.bVisible = 1;
		cursor_info.dwSize = 50;
		break;
	case CURSOR_INVISIBLE:
		cursor_info.bVisible = 0;
		cursor_info.dwSize = 1;
		break;
	case CURSOR_VISIBLE_NORMAL:
	default: //ȱʡ��ʾ��꣬����
		cursor_info.bVisible = 1;
		cursor_info.dwSize = 25;
		break;
	}
	SetConsoleCursorInfo(__hout, &cursor_info);
}
