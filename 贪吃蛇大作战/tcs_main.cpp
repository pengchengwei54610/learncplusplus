#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include "declare.h"
#include <fstream>
#include <cstdio>
#include <conio.h>
#include <time.h>
#include <string>


//������Ϸ�߽��С���ߵĳ�ʼ����
const int X = 80;
const int Y = 40;
const int length = 3;
//�����ߵĳ�ʼ�ƶ�����
int direction = right;
//��ʼ�����µĵ�ͼ��� ��f����ʾΪʳ�0'Ϊ���ߡ�1����ʾ�ϰ�
char situation[Y][X] = { 0 };


//����Ƿ����
int check(int x, int y) {
	if (x < 0 || x >= X)
		return 0;
	else if (y < 0 || y >= Y)
		return 0;
	return 1;
}

//�ı䷽���жϣ����ж��������ң�
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


//�����ַ����飬�ҵ�����ķ���
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


//���ܣ����ļ����ҵ���Ӧ��Ϸ�汾����߷�
//������ѡ�����Ϸ�汾
//����ֵ����Ӧ�汾��߷֣���û�иð汾��Ϸ��¼ʱ����ʾ0�֣�
int findmaxscore(int choice)
{
	//���ļ�
	ifstream infile;
	infile.open("record.txt", ios::in);
	if (infile.is_open() == 0)
	{
		return 0;
	}
	const int length = strlen("�汾:���Ű�");
	char s[13];//û�취ֱ����lengthȥ��ʼ��  ����13�������ĳ���+β��
	char gets[100] = { 0 };//ÿһ�ж��������ַ�����
	//ȷ���汾
	if (choice == 1)
		strcpy(s, "�汾:���Ű�");
	else if (choice == 2)
		strcpy(s, "�汾:���װ�");
	else if (choice == 3)
		strcpy(s, "�汾:�߼���");
	else
		;

	int num = 0;
	int max = 0;
	while (!infile.eof()) {
		infile.getline(gets, 100);
		if (strncmp(gets, s, length) == 0) {//��һ�еĿ�ͷ���϶�Ӧ�汾��ͷ���ż�������
			num = findmaxscore_find(gets);
			if (num >= max)
				max = num;
		}
	}
	infile.close();
	return max;
}


//�ṹ��Node
struct Node
{
	int x;
	int y;
	struct Node* next;
};

//�߶���
class snake
{
private:
	struct Node* head;//�ߵ�ͷ���������βָ�룬�������
	struct Node* tail;//�ߵ�β���������ͷָ�룬����ɾ��
	int foodnum;
	int maxscore;
	int now_length;
	//ɾ����β��ԭ��β��ǰһ����Ϊ�µ���β
	void deletetail() {
		struct Node* p = tail;
		tail = tail->next;//��β��ǰһ�����µ���β
		delete p;
	}
	//ɾ����β��ԭ��β��ǰһ����Ϊ�µ���β�����ر�ɾ��������
	void deletetail(int& x, int& y) {
		struct Node* p = tail;
		x = tail->x, y = tail->y;//�������
		tail = tail->next;//��β��ǰһ�����µ���β
		delete p;
	}
	//�Ե�������ʱ��
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

	//��ʾ���ȣ��÷֣���ߵ÷�
	void information(int choice, int second) {
		gotoxy(0, Y + 2);
		maxscore = findmaxscore(choice);
		cout << "��ǰ�ߵĳ���:" << now_length << "  ��ǰ�÷�:" << score << "  ��ʷ��߷�:" << maxscore << " ��Ϸʱ��(s)��" << second << endl;
	}

	//�ͷ���������(��������˵������Ϸ����ʱ����������¿�ʼ��ֻ������������������ֱ����������
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

	//��ʾʳ��
	void food() {
		srand((unsigned int)time(0));//ȡ�����ʱ������
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

	//�����ʼ�����ó��ȳ�ʼ����
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
				cerr << "�ڴ�����ʧ��";
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
			head = p;//���һ���ڵ㼴������β����ͷ
			p->next = NULL;
		}
		return 1;//��ʼ���ɹ�
	}

	//��ʾ��ʼ������
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

	//������ѡ�������ƶ�����
	int death_dire() {
		gotoxy(0, Y + 4);
		setcolor(COLOR_BLACK, COLOR_HBLUE);
		cout << "���������������������Ͻǣ��밴���������������ʼ�˶�����(����ѡ���������)" << endl;
		setcolor(COLOR_BLACK, COLOR_WHITE);
		int direction2 = 0;
		while (1) {
			direction2 = _getch();
			if (direction2 == right || direction2 == down)
				break;
		}
		return direction2;
	}

	//�ƶ���������Ϸ���߼�������
	int move(int choice) {
		initialize(length, direction);
		int k = 1;//�����ж���
		int times = 0;//�߼������
		int time_count = 0, second_show = 0;
		while (1) {
			information(choice, second_show);
			Sleep(100);
			time_count++;
			second_show = time_count / 10;
			//�ж��Ƿ�ı䷽��
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
					cout << "���һ�λ���" << endl;
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
					cout << "��ʣ" << (5 - times) << "�λ���" << endl;
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
					cout << "��ʣ" << (5 - times) << "�λ���" << endl;
					freesnake(tail);
					direction = death_dire();
					initialize(length, direction);
					draw_initialize();
					continue;
				}
			}

			int x, y;

			if (situation[head->y][head->x] != 'f' && situation[head->y][head->x] != 'd') {
				//ɾ��β��				
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

//��Ļ����
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
		//��ʾ�߽�
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

	//��ʾ�˵�
	void menu() {
		cout << endl;
		cout << "--------------̰������Ϸ---------------" << endl;
		cout << "1.���Ű�" << endl;
		cout << "2.���װ�" << endl;
		cout << "3.�߼���" << endl;
		cout << "0.�˳�" << endl;
		cout << "---------------------------------------" << endl;
		cout << "������ţ�1-3��������Ϸ,���� 0 �˳���Ϸ" << endl;
	}

};


int main()
{
	system("mode con cols=100 lines=60");//����������߿��С�Ļ�����colsֵ����ΪX+20,linesֵ����ΪY+20����
	screen t1;
	t1.menu();//��ʾ�˵�
	int choice;
	while (1)
	{
		cin >> choice;
		if (cin.fail())
			cout << "��������ȷ����ţ�1,2,3��" << endl;
		else if (choice < 0 || choice>3)
			cout << "��������ȷ��Χ����ţ�1,2,3��" << endl;
		else
			break;
		//������뻺����
		cin.clear();
		cin.ignore(1024, '\n');
	}
	//����ѡ����Ӧ����
	//�˳���Ϸ
	if (choice == 0)
		return 0;
	//������Ϸ��Ҫ�����������
	string name;//�����
	cout << "��������������" << endl;
	cin >> name;
	setcursor(CURSOR_INVISIBLE);//�رչ��
	cls();//����
	t1.display();//��ʾ��ʼ����
	snake s1;
	s1.food();
	s1.initialize(length, direction);
	s1.draw_initialize();
	s1.move(choice);
	gotoxy(0, Y + 3);
	//�����ǰ����Ϸ��ʾ
	cout << "��Ϸ����                                                              " << endl << "                                                                                     ";
	//�ļ���ȡд�� ����������
	fstream file;
	file.open("record.txt", ios::in | ios::out | ios::app);
	if (!file) {
		cout << "��ȡ��¼�ļ����ִ���" << endl;
		return -1;
	}
	else {
		if (choice == 1)
			file << "�汾:���Ű�  ";
		else if (choice == 2)
			file << "�汾:���װ�  ";
		else
			file << "�汾:�߼���  ";
		file << "�����:" << name;
		file << "  �÷�:" << s1.score << endl;
	}
	file.close();//�ر��ļ����
	return 0;
}