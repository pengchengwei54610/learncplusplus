#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "declare.h"
#include <fstream>
#include <cstdio>
#include <conio.h>
#include <time.h>
#include <string>


//定义游戏边界大小与蛇的初始长度
const int X = 80;
const int Y = 40;
const int length = 3;
//定义蛇的初始移动方向
int direction = right;
//初始坐标下的地图情况 ‘f’表示为食物‘0'为可走‘1’表示障碍
char situation[Y][X] = { 0 };


//检查是否出界
int check(int x, int y) {
	if (x < 0 || x >= X)
		return 0;
	else if (y < 0 || y >= Y)
		return 0;
	return 1;
}

//改变方向判断（仅判断上下左右）
int changedire() {
	int direction_2 = _getch();
	if (direction_2 + direction == left + right)
		return 0;
	else if (direction_2 == right || direction_2 == left || direction_2 == up || direction_2 == down) {
		direction = direction_2;
		return 1;
	}
	return 0;
}


//输入字符数组，找到所需的分数
int findmaxscore_find(char s[]) {
	int length = strlen(s);
	int i = 0;
	int count = 0;
	int num = 0;
	for (i = 0; i < length; i++) {
		if (s[i] == ':')
			count++;
		if (count == 3) {
			num = atoi(&s[i + 1]);
			break;
		}
	}
	return num;
}


//功能：从文件中找到对应游戏版本的最高分
//参数：选择的游戏版本
//返回值：对应版本最高分（还没有该版本游戏记录时会显示0分）
int findmaxscore(int choice)
{
	//打开文件
	ifstream infile;
	infile.open("record.txt", ios::in);
	if (infile.is_open() == 0)
	{
		return 0;
	}
	const int length = strlen("版本:入门版");
	char s[13];//没办法直接拿length去初始化  反正13就是他的长度+尾零
	char gets[100] = { 0 };//每一行读入存入此字符数组
	//确定版本
	if (choice == 1)
		strcpy(s, "版本:入门版");
	else if (choice == 2)
		strcpy(s, "版本:进阶版");
	else if (choice == 3)
		strcpy(s, "版本:高级版");
	else
		;

	int num = 0;
	int max = 0;
	while (!infile.eof()) {
		infile.getline(gets, 100);
		if (strncmp(gets, s, length) == 0) {//当一行的开头符合对应版本开头，才继续操作
			num = findmaxscore_find(gets);
			if (num >= max)
				max = num;
		}
	}
	infile.close();
	return max;
}


//结构体Node
struct Node
{
	int x;
	int y;
	struct Node* next;
};

//蛇对象
class snake
{
private:
	struct Node* head;//蛇的头即是链表的尾指针，方便添加
	struct Node* tail;//蛇的尾即是链表的头指针，方便删除
	int foodnum;
	int maxscore;
	int now_length;
	//删除蛇尾，原蛇尾的前一个作为新的蛇尾
	void deletetail() {
		struct Node* p = tail;
		tail = tail->next;//蛇尾的前一个是新的蛇尾
		delete p;
	}
	//删除蛇尾，原蛇尾的前一个作为新的蛇尾，返回被删除的坐标
	void deletetail(int& x, int& y) {
		struct Node* p = tail;
		x = tail->x, y = tail->y;//获得坐标
		tail = tail->next;//蛇尾的前一个是新的蛇尾
		delete p;
	}
	//吃到东西的时候
	int addhead(int x, int y)
	{
		struct Node* p = NULL;

		p = new(nothrow) Node;
		if (p == NULL)
			return NULL;

		head->next = p;
		head = p;
		p->next = NULL;
		p->x = x;
		p->y = y;
		return 1;
	}

	//显示长度，得分，最高得分
	void information(int choice, int second) {
		gotoxy(0, Y + 2);
		maxscore = findmaxscore(choice);
		cout << "当前蛇的长度:" << now_length << "  当前得分:" << score << "  历史最高分:" << maxscore << " 游戏时间(s)：" << second << endl;
	}

	//释放蛇身链表(对于蛇来说除了游戏结束时其他情况重新开始均只能清空蛇身链表而不能直接析构对象）
	void freesnake(struct Node* tail)
	{
		struct Node* p = tail, * q = NULL;
		while (p) {
			q = p->next;
			delete p;
			p = q;
		}
	}

	void block() {
		setcolor(COLOR_BLACK, COLOR_HBLUE);
		int x, y;
		for (y = 0; y < Y; y++) {
			for (x = 0; x < X; x++) {
				if (situation[y][x] == '1') {
					gotoxy(x + 1, y + 1);
					putchar('#');
				}
				else if (situation[y][x] == 'd') {
					gotoxy(x + 1, y + 1);
					putchar('f');
				}
			}
		}
		setcolor(COLOR_BLACK, COLOR_WHITE);
	}

public:
	int score;
	snake() {
		tail = head = NULL;
		foodnum = 0;
		score = 0;
		maxscore = 0;
		now_length = length;
	}

	//显示食物
	void food() {
		srand((unsigned int)time(0));//取随机数时间种子
		foodnum = rand() % 5 + 1;
		int x = 0, y = 0;
		int i = foodnum;
		for (; i > 0; i--) {
			x = rand() % X;
			y = rand() % Y;
			situation[y][x] = 'f';
			gotoxy(x + 1, y + 1);
			putchar('f');
		}
	}

	//链表初始化：用长度初始化蛇
	int initialize(int length, int direction)
	{
		int i;
		int x0 = 0, y0 = 0;
		struct Node* p = NULL, * q = NULL;
		for (i = 0; i < length; i++) {
			if (i > 0)
				q = p;

			p = new(nothrow) Node;
			if (p == NULL)
			{
				cerr << "内存申请失败";
				exit(0);
			}
			if (i == 0)
				tail = p;
			else
				q->next = p;
			if (direction == right) {
				p->x = x0++;
				p->y = y0;
			}
			else if (direction == down) {
				p->x = x0;
				p->y = y0++;
			}
			head = p;//最后一个节点即是链表尾，蛇头
			p->next = NULL;
		}
		return 1;//初始化成功
	}

	//显示初始化的蛇
	void draw_initialize() {
		struct Node* p = tail;
		for (p = tail; p != NULL; p = p->next) {
			gotoxy((p->x) + 1, (p->y) + 1);
			putchar('*');
		}
	}
	int death1(int choice) {
		char c = '0';
		if (choice == 1 || choice == 2)
			c = '1';
		else
			c = 'd';
		if (check(head->x, head->y) == 0) {
			struct Node* p = tail;
			for (p = tail; p != head; p = p->next) {
				situation[p->y][p->x] = c;
			}
			return 1;
		}
		struct Node* p = tail;
		for (p = tail; p != head; p = p->next) {
			if (p->x == head->x && p->y == head->y) {
				struct Node* q = tail;
				for (q = tail; q != head; q = q->next) {
					situation[q->y][q->x] = c;
				}
				return 1;
			}
		}
		return 0;
	}
	int death2(int choice) {
		char c = '0';
		if (choice == 2)
			c = '1';
		else if (choice == 3)
			c = 'd';
		if (situation[head->y][head->x] == '1') {
			struct Node* p = tail;
			for (p = tail; p != head; p = p->next) {
				situation[p->y][p->x] = c;
			}
			return 1;
		}
		if (check(head->x, head->y) == 0) {
			struct Node* p = tail;
			for (p = tail; p != head; p = p->next) {
				situation[p->y][p->x] = c;
			}
			return 1;
		}
		struct Node* p = tail;
		for (p = tail; p != head; p = p->next) {
			if (p->x == head->x && p->y == head->y) {
				struct Node* q = tail;
				for (q = tail; q != head; q = q->next) {
					situation[q->y][q->x] = c;
				}
				return 1;
			}
		}
		return 0;
	}

	//死亡后选择重生移动方向
	int death_dire() {
		gotoxy(0, Y + 4);
		setcolor(COLOR_BLACK, COLOR_HBLUE);
		cout << "已死亡，即将重生在左上角，请按方向键决定重生初始运动方向(不可选择向左和上)" << endl;
		setcolor(COLOR_BLACK, COLOR_WHITE);
		int direction2 = 0;
		while (1) {
			direction2 = _getch();
			if (direction2 == right || direction2 == down)
				break;
		}
		return direction2;
	}

	//移动函数（游戏主逻辑函数）
	int move(int choice) {
		initialize(length, direction);
		int k = 1;//单次判断数
		int times = 0;//高级版次数
		int time_count = 0, second_show = 0;
		while (1) {
			information(choice, second_show);
			Sleep(100);
			time_count++;
			second_show = time_count / 10;
			//判断是否改变方向
			if (_kbhit())
				changedire();
			switch (direction) {
			case right:
				addhead(head->x + 1, head->y);
				break;
			case left:
				addhead(head->x - 1, head->y);
				break;
			case up:
				addhead(head->x, head->y - 1);
				break;
			case down:
				addhead(head->x, head->y + 1);
				break;
			}
			if (choice == 1 && death1(1) == 1)
				return 0;
			else if (choice == 2) {
				if (death1(2) == 1 && k) {
					k = 0;
					block();
					gotoxy(0, Y + 3);
					cout << "最后一次机会" << endl;
					freesnake(tail);
					direction = death_dire();
					initialize(length, direction);
					draw_initialize();
					continue;
				}
				else if (!k && death2(2) == 1) {
					return 0;
				}
			}
			else if (choice == 3) {
				if (death1(3) == 1 && k) {
					k = 0;
					block();
					times++;
					gotoxy(0, Y + 3);
					cout << "还剩" << (5 - times) << "次机会" << endl;
					freesnake(tail);
					direction = death_dire();
					initialize(length, direction);
					draw_initialize();
					continue;
				}
				else if (!k && death2(3) == 1) {
					block();
					times++;
					if (times == 5)
						return 0;
					gotoxy(0, Y + 3);
					cout << "还剩" << (5 - times) << "次机会" << endl;
					freesnake(tail);
					direction = death_dire();
					initialize(length, direction);
					draw_initialize();
					continue;
				}
			}

			int x, y;

			if (situation[head->y][head->x] != 'f' && situation[head->y][head->x] != 'd') {
				//删除尾巴				
				deletetail(x, y);
				gotoxy((head->x) + 1, (head->y) + 1);
				putchar('*');
				gotoxy(x + 1, y + 1);
				putchar(' ');
			}
			else {
				if (situation[head->y][head->x] == 'f') {
					foodnum--;
					score += 2;
				}
				else
					score += 1;

				situation[head->y][head->x] = '0';
				gotoxy((head->x) + 1, (head->y) + 1);
				putchar('*');

				now_length++;
			}
			if (foodnum <= 0) {
				food();
			}

		}

	}

};

//屏幕对象
class screen {
private:
	int choice;
public:
	screen()
	{
		choice = 0;
	}
	void display() {
		setcolor(COLOR_BLACK, COLOR_HBLUE);
		int i, j = 0;
		gotoxy(0, 0);
		//显示边界
		for (i = 0; i < X + 2; i++) {
			cout << '-';
		}
		gotoxy(0, Y + 1);
		for (i = 0; i < X + 2; i++) {
			cout << '-';
		}

		for (i = 0; i < Y; i++) {
			gotoxy(0, 1 + i);
			cout << '|';
		}

		for (i = 0; i < Y; i++) {
			gotoxy(X + 1, 1 + i);
			cout << '|';
		}
		setcolor(COLOR_BLACK, COLOR_WHITE);
	}

	//显示菜单
	void menu() {
		cout << endl;
		cout << "--------------贪吃蛇游戏---------------" << endl;
		cout << "1.入门版" << endl;
		cout << "2.进阶版" << endl;
		cout << "3.高级版" << endl;
		cout << "0.退出" << endl;
		cout << "---------------------------------------" << endl;
		cout << "输入序号（1-3）进入游戏,输入 0 退出游戏" << endl;
	}

};


int main()
{
	system("mode con cols=100 lines=60");//若调整整体边框大小的话，将cols值调整为X+20,lines值调整为Y+20即可
	screen t1;
	t1.menu();//显示菜单
	int choice;
	while (1)
	{
		cin >> choice;
		if (cin.fail())
			cout << "请输入正确的序号（1,2,3）" << endl;
		else if (choice < 0 || choice>3)
			cout << "请输入正确范围的序号（1,2,3）" << endl;
		else
			break;
		//清空输入缓冲区
		cin.clear();
		cin.ignore(1024, '\n');
	}
	//输入选项后对应反馈
	//退出游戏
	if (choice == 0)
		return 0;
	//进入游戏，要求输入玩家名
	string name;//玩家名
	cout << "请输入你的玩家名" << endl;
	cin >> name;
	setcursor(CURSOR_INVISIBLE);//关闭光标
	cls();//清屏
	t1.display();//显示初始界面
	snake s1;
	s1.food();
	s1.initialize(length, direction);
	s1.draw_initialize();
	s1.move(choice);
	gotoxy(0, Y + 3);
	//清空先前的游戏提示
	cout << "游戏结束                                                              " << endl << "                                                                                     ";
	//文件读取写入 读出在蛇类
	fstream file;
	file.open("record.txt", ios::in | ios::out | ios::app);
	if (!file) {
		cout << "读取记录文件出现错误" << endl;
		return -1;
	}
	else {
		if (choice == 1)
			file << "版本:入门版  ";
		else if (choice == 2)
			file << "版本:进阶版  ";
		else
			file << "版本:高级版  ";
		file << "玩家名:" << name;
		file << "  得分:" << s1.score << endl;
	}
	file.close();//关闭文件句柄
	return 0;
}