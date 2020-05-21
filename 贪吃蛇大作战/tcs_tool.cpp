//显示工具函数集
//取自渣哥大作业工具函数
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <tchar.h>
#include "declare.h"
using namespace std;

/* 静态全局，只在本源程序文件中有效（为防止同名，静态全局一般建议加__做为变量名开始） */
static const HANDLE __hout = GetStdHandle(STD_OUTPUT_HANDLE);		//取标准输出设备对应的句柄
static const HANDLE __hin = GetStdHandle(STD_INPUT_HANDLE);			//取标准输入设备对应的句柄

/***************************************************************************
  函数名称：
  功    能：完成与system("cls")一样的功能，但效率高
  输入参数：
  返 回 值：
  说    明：清除整个屏幕缓冲区，不仅仅是可见窗口区域(使用当前颜色)
***************************************************************************/
void cls(void)
{
	COORD coord = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO binfo; /* to get buffer info */
	DWORD num;

	/* 取当前缓冲区信息 */
	GetConsoleScreenBufferInfo(__hout, &binfo);
	/* 填充字符 */
	FillConsoleOutputCharacter(__hout, (TCHAR)' ', binfo.dwSize.X * binfo.dwSize.Y, coord, &num);
	/* 填充属性 */
	FillConsoleOutputAttribute(__hout, binfo.wAttributes, binfo.dwSize.X * binfo.dwSize.Y, coord, &num);

	/* 光标回到(0,0) */
	SetConsoleCursorPosition(__hout, coord);
	return;
}

/***************************************************************************
  函数名称：
  功    能：设置指定的颜色
  输入参数：const int bg_color ：背景色（0-15）
			const int fg_color ：前景色（0-15）
  返 回 值：
  说    明：颜色的取值由背景色+前景色组成，各16种
			fg_color：0-7    黑   蓝   绿   青   红   粉   黄   白
					  8-15 亮黑 亮蓝 亮绿 亮青 亮红 亮粉 亮黄 亮白
			bg_color：0-7    黑   蓝   绿   青   红   粉   黄   白
					  8-15 亮黑 亮蓝 亮绿 亮青 亮红 亮粉 亮黄 亮白
			最终的颜色为 背景色*16+前景色
***************************************************************************/
void setcolor(const int bg_color, const int fg_color)
{
	SetConsoleTextAttribute(__hout, bg_color * 16 + fg_color);
}

/***************************************************************************
  函数名称：
  功    能：将光标移动到指定位置
  输入参数：const int X       ：X轴坐标（列）
			const int Y       ：Y轴坐标（行）
  返 回 值：
  说    明：屏幕左上角坐标为(0,0)，在cmd窗口的大小未被调整的情况下，Win10为：
			横向x轴，对应列(0-119)
			纵向y轴，对应行(0-29)
***************************************************************************/
void gotoxy(const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(__hout, coord);
}


/***************************************************************************
  函数名称：
  功    能：取当前光标所在位置的坐标值
  输入参数：int &x            ：取得的X轴坐标（列）
			int &y            ：取得的Y轴坐标（行）
  返 回 值：
  说    明：形参中的&表示引用，第六章会讲到，引用形参的值可以返回给实参
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
  函数名称：
  功    能：设置光标状态（显示/不显示/全高/半高/横线等）
  输入参数：const int option：要设置的光标状态
  返 回 值：
  说    明：
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
	default: //缺省显示光标，横线
		cursor_info.bVisible = 1;
		cursor_info.dwSize = 25;
		break;
	}
	SetConsoleCursorInfo(__hout, &cursor_info);
}
