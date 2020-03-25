#include <iostream>
#include <iomanip>
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include<windows.h>
#pragma comment(lib,"winmm.lib")
/*��ɫ����
BLACK			0			��
BLUE			0xAA0000	��
GREEN			0x00AA00	��
CYAN			0xAAAA00	��
RED				0x0000AA	��
MAGENTA			0xAA00AA	��
BROWN			0x0055AA	��
LIGHTGRAY		0xAAAAAA	ǳ��
DARKGRAY		0x555555	���
LIGHTBLUE		0xFF5555	����
LIGHTGREEN		0x55FF55	����
LIGHTCYAN		0xFFFF55	����
LIGHTRED		0x5555FF	����
LIGHTMAGENTA	0xFF55FF	����
YELLOW			0x55FFFF	��
WHITE			0xFFFFFF	��
*/
using namespace std;
////////////////////////////////////////////////
/*��Ҫ�����޸Ĳ���*/
#define window_init_length 640//���в����ı�ֻ��ı���һ���
#define clockedge_color BLUE
#define clock_center_point_color GREEN
#define tick_color WHITE
#define background_color BLACK
#define second_hand_color YELLOW
#define minute_hand_color CYAN
#define hour_hand_color BLUE
////////////////////////////////////////////////

////////////////////////////////////////////////
/*��ѡ�����޸Ĳ���*/
#define window_init_width int(window_init_length/1.5)
#define init_radius int(window_init_length/4)
#define point_radius int(window_init_length/250)
#define tick_length int(window_init_length/200)
#define second_hand_length int(init_radius/1.2)
#define minute_hand_length int(init_radius/1.5)
#define hour_hand_length int(init_radius/2.0)
#define text_height int(window_init_length/40)
#define text_width int(window_init_length/40)
////////////////////////////////////////////////

#define pi 3.1415926
using namespace std;
void draw_tick()
{
	setlinecolor(tick_color);
	const int x1 = window_init_length / 2, y1 = window_init_width / 2;
	int count1 = 0;
	while (count1 < 60)
	{
		if (count1 % 5 == 0)
			line(x1 + int(init_radius * sin(count1 * pi / 30)), y1 - int(init_radius * cos(count1 * pi / 30)), x1 + int((init_radius - 5 * tick_length) * sin(count1 * pi / 30)), y1 - int((init_radius - 5 * tick_length) * cos(count1 * pi / 30)));
		else
			line(x1 + int(init_radius * sin(count1 * pi / 30)), y1 - int(init_radius * cos(count1 * pi / 30)), x1 + int((init_radius - tick_length) * sin(count1 * pi / 30)), y1 - int((init_radius - tick_length) * cos(count1 * pi / 30)));
		count1++;
	}
}
void draw_numbers()
{
	settextstyle(text_height, text_width, _T("Courier"));
	const int x1 = window_init_length / 2, y1 = window_init_width / 2;
	settextcolor(WHITE);
	char char1 = '1';
	outtextxy(x1 - text_width, int(y1 - init_radius + text_height), char1);
	char1 = '2';
	outtextxy(x1, int(y1 - init_radius + text_height), char1);
	char1 = '3';
	outtextxy(x1 + init_radius - 2 * text_width, y1 - int(0.5 * text_height), char1);
	char1 = '6';
	outtextxy(x1 - int(0.5 * text_width), int(y1 + init_radius - 2 * text_height), char1);
	char1 = '9';
	outtextxy(x1 - init_radius + text_width, y1 - int(0.5 * text_height), char1);
}
void init()
{
	setlinecolor(background_color);
	for (int y = 0; y < window_init_width; y++)
	{
		line(0, y, window_init_length, y);
	}
	const int x1 = window_init_length / 2, y1 = window_init_width / 2;
	setlinecolor(clockedge_color);//������ɫ�Ȳ������������ó�ʼ����ͼ����֮ǰ
	circle(window_init_length / 2, window_init_width / 2, init_radius);//ͼ�η�ʽ��ʼ��
	setfillcolor(clock_center_point_color);
	setlinecolor(clock_center_point_color);
	fillcircle(x1, y1, point_radius);
	draw_tick();
	draw_numbers();
}
void draw_new_hand(tm time1)
{
	const int x1 = window_init_length / 2, y1 = window_init_width / 2;
	setlinecolor(RGB(time1.tm_sec * 2 + 120, time1.tm_min * 2 + 120, time1.tm_hour * 5 + 120));
	line(x1, y1, x1 + int(second_hand_length * sin(time1.tm_sec * pi / 30)), y1 - int(second_hand_length * cos(time1.tm_sec * pi / 30)));
	setlinecolor(minute_hand_color);
	line(x1, y1, x1 + int(minute_hand_length * sin(time1.tm_sec * pi / 1800 + time1.tm_min * pi / 30)), y1 - int(minute_hand_length * cos(time1.tm_sec * pi / 1800 + time1.tm_min * pi / 30)));
	setlinecolor(hour_hand_color);
	line(x1, y1, x1 + int(hour_hand_length * sin(time1.tm_sec * pi / 21600 + time1.tm_min * pi / 360 + time1.tm_hour * pi / 6)), y1 - int(hour_hand_length * cos(time1.tm_sec * pi / 21600 + time1.tm_min * pi / 360 + time1.tm_hour * pi / 6)));
	return;
}
void draw_clock(tm time1)
{
	const int x1 = window_init_length / 2, y1 = window_init_width / 2;
	setlinestyle(PS_DASH);
	setlinecolor(background_color);
	if (time1.tm_sec != 0)
		line(x1, y1, x1 + int(second_hand_length * sin((double(time1.tm_sec) - 1) * pi / 30)), y1 - int(second_hand_length * cos((double(time1.tm_sec) - 1) * pi / 30)));
	else
		line(x1, y1, x1 + int(second_hand_length * sin(59 * pi / 30)), y1 - int(second_hand_length * cos(59 * pi / 30)));
	////////////////////////////////
	if (time1.tm_sec != 0)
		line(x1, y1, x1 + int(minute_hand_length * sin((double(time1.tm_sec) - 1) * pi / 1800 + time1.tm_min * pi / 30)), y1 - int(minute_hand_length * cos((double(time1.tm_sec) - 1) * pi / 1800 + time1.tm_min * pi / 30)));
	else
		if (time1.tm_min != 0)
			line(x1, y1, x1 + int(minute_hand_length * sin(59 * pi / 1800 + (double(time1.tm_min) - 1) * pi / 30)), y1 - int(minute_hand_length * cos(59 * pi / 1800 + (double(time1.tm_min) - 1) * pi / 30)));
		else
			line(x1, y1, x1 + int(minute_hand_length * sin(59 * pi / 1800 + 59 * pi / 30)), y1 - int(minute_hand_length * cos(59 * pi / 1800 + 59 * pi / 30)));
	///////////////////////////////
	if (time1.tm_sec != 0)
		line(x1, y1, x1 + int(hour_hand_length * sin((double(time1.tm_sec) - 1) * pi / 21600 + time1.tm_min * pi / 360 + time1.tm_hour * pi / 6)), y1 - int(hour_hand_length * cos((double(time1.tm_sec) - 1) * pi / 21600 + time1.tm_min * pi / 360 + time1.tm_hour * pi / 6)));
	else
		if (time1.tm_min != 0)
			line(x1, y1, x1 + int(hour_hand_length * sin(59 * pi / 21600 + (double(time1.tm_min) - 1) * pi / 360 + time1.tm_hour * pi / 6)), y1 - int(hour_hand_length * cos(59 * pi / 21600 + (double(time1.tm_min) - 1) * pi / 360 + time1.tm_hour * pi / 6)));
		else
			if (time1.tm_hour != 0)
				line(x1, y1, x1 + int(hour_hand_length * sin(59 * pi / 21600 + 59 * pi / 360 + (double(time1.tm_hour) - 1) * pi / 6)), y1 - int(hour_hand_length * cos(59 * pi / 21600 + 59 * pi / 360 + (double(time1.tm_hour) - 1) * pi / 6)));
			else
				line(x1, y1, x1 + int(hour_hand_length * sin(59 * pi / 21600 + 59 * pi / 360 + 11 * pi / 6)), y1 - int(hour_hand_length * cos(59 * pi / 21600 + 59 * pi / 360 + 11 * pi / 6)));
	draw_new_hand(time1);
	return;
}
int main()
{
	PlaySound(TEXT("1.wav"), NULL, SND_FILENAME | SND_ASYNC);
	struct tm t;
	int flag1 = 0;
	time_t now;
	initgraph(window_init_length, window_init_width, NOCLOSE | NOMINIMIZE);
	init();                   //�Զ���ͼ�γ�ʼ�����������ڻ���ʱ�ӽ���
	int second1;
	while (!_kbhit())         //�޼��̲���ʱ����ѭ��
	{
		time(&now);
		localtime_s(&t, &now);
		if (flag1 == 0)
		{
			draw_clock(t);
			second1 = t.tm_sec;
			flag1++;
		}
		else
		{
			if (t.tm_sec != second1)
			{
				second1 = t.tm_sec;
				draw_clock(t);
			}
		}
		/*��ͣ��ȡ��ǰʱ�䣬��֮ǰ����ʱ/��/����ʱ��ʱ����ȣ����ж���ʱ��ĵ���*/
		/*�����µ�ʱ�����»���ʱ�룬���룬���룬�����Զ��庯����ɣ�ע��������������*/
	}
	if (_getch() != NULL)
		closegraph();                //�������׼���˳�ʱ�ӳ���
	return 0;
}