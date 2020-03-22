#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;
#define Status bool 
#define success 1
#define fail 0
struct student
{
	int no;                //ѧ��
	char name[20];         //����
	int score;             //�ɼ�
	struct student* next;  //��һ���
};
struct score_num
{
	int excellent;
	int good;
	int medium;
	int pass;
	int failed;
};
//��ȡ�ļ�������ѧ����Ϣ����
Status read(struct student** head)
{
	int student_num;
	int count1 = 0;
	fstream infile("D:\\student.txt", ios::in);
	if (!infile)
	{
		cout << "���ļ�ʧ��" << endl;
		return fail;
	}
	infile >> student_num;

	struct student* p, * newnode;
	while (count1 < student_num)
	{
		newnode = new(nothrow)student;
		if (newnode == NULL)
		{
			cout << "No memory" << endl;
			return fail;
		}
		count1++;
		infile >> newnode->no >> newnode->name >> newnode->score;
		newnode->next = NULL;
		if ((*head) == NULL)
		{
			(*head) = newnode;
			continue;
		}
		p = *head;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = newnode;
	}
	infile.close();
	return success;
}
//����ѧ������
int count_list(struct student* head)
{
	int count1 = 0;
	student* temp = head;
	while (temp != NULL)
	{
		count1++;
		temp = temp->next;
	}
	return count1;
}

//����ѧ���ɼ�Ϊ��һ�ؼ��ֽ�������ѧ��ѧ��Ϊ�ڶ��ؼ�����������
void sort(struct student** head)
{
	int list_length = count_list(*head);
	int tempno, tempscore;
	char tempname[20];
	int count1, count2;
	student* temp;
	for (count1 = 1; count1 < list_length; count1++)
	{
		for (temp = *head, count2 = 0; count2 < list_length - count1; temp = temp->next, count2++)
		{
			if ((temp->score) < ((temp->next)->score))
			{
				tempno = temp->no;
				tempscore = temp->score;
				strcpy(tempname, temp->name);
				temp->no = temp->next->no;
				temp->score = temp->next->score;
				strcpy(temp->name, temp->next->name);
				temp->next->no = tempno;
				temp->next->score = tempscore;
				strcpy(temp->next->name, tempname);
			}
		}
	}
	for (count1 = 1; count1 < list_length; count1++)
	{
		for (temp = *head, count2 = 0; count2 < list_length - count1; temp = temp->next, count2++)
		{
			if ((temp->score) == ((temp->next)->score))
			{
				if ((temp->no) > ((temp->next)->no))
				{
					tempno = temp->no;
					tempscore = temp->score;
					strcpy(tempname, temp->name);
					temp->no = temp->next->no;
					temp->score = temp->next->score;
					strcpy(temp->name, temp->next->name);
					temp->next->no = tempno;
					temp->next->score = tempscore;
					strcpy(temp->next->name, tempname);
				}
			}

		}
	}
}

//��ʾ����ѧ������
void disp(struct student* head)
{
	struct student* temp;
	temp = head;
	while (temp != NULL)
	{
		cout << "ѧ�ţ�" << temp->no << " ������" << temp->name << " �ɼ���" << temp->score << endl;
		temp = temp->next;
	}
}
void init_scoresum(score_num& s1)
{
	s1.good = 0;
	s1.excellent = 0;
	s1.failed = 0;
	s1.medium = 0;
	s1.pass = 0;
}

//�������score_num�ṹ�����
Status add_sum(student* head, score_num& s1)
{
	s1.excellent = 0;
	s1.failed = 0;
	s1.good = 0;
	s1.medium = 0;
	s1.pass = 0;
	student* temp;
	temp = head;
	while (temp != NULL)
	{
		if (temp->score < 60)
			s1.failed++;
		else if (temp->score < 70)
			s1.pass++;
		else if (temp->score < 80)
			s1.medium++;
		else if (temp->score < 90)
			s1.good++;
		else if (temp->score <= 100)
			s1.excellent++;
		else
		{
			cout << "�ɼ�����" << endl;
			return fail;
		}
		temp = temp->next;
	}
	return success;
}
//����ֶν��
void output_scoreresult(score_num s1)
{
	cout << "ͳ����Ϣ���£�" << endl;
	cout << "�ţ� " << s1.excellent << "��  " << "���� " << s1.good << "��  " << "�У� " << s1.medium << "��  " << "���� " << s1.pass << "��  " << "������ " << s1.failed << "��  " << endl;
}
//ѧ���ɼ��ֶβ����ÿ�ζ�Ӧ����
void count(student* head)
{
	score_num s1;
	add_sum(head, s1);
	output_scoreresult(s1);
}

//С���ܽ����ж�
bool isContinue() {
	cout << "�Ƿ����?(y/n): \n";
	char tmp;
	cin >> tmp;
	if (tmp == 'Y' || tmp == 'y')return true;
	return false;
}
//����ѧ�ŷ���Ѱ��ѧ����ָ��
student* searchID(student* head, int query)
{
	student* temp = head;
	while (temp != NULL)
	{
		if (temp->no == query)
		{
			return temp;
		}
		else
			temp = temp->next;
	}
	return NULL;
}
//����ѧ��Ѱ��ѧ��
void searchbyID(student* head)
{
	int query;
	student* temp;
	while (1)
	{
		cout << "��������Ҫ���ҵ�ѧ��" << endl;
		cin >> query;
		temp = head;
		while (temp != NULL)
		{
			if (temp->no == query)
			{
				cout << "ѧ�ţ�" << temp->no << " ������" << temp->name << " �ɼ���" << temp->score << endl;
				break;
			}
			else
				temp = temp->next;
		}
		if (temp == NULL)
			cout << "������" << endl;
		if (isContinue() == true)
			continue;
		else
			return;
	}
}
//����ѧ�����ѧ����Ϣ
void addbyID(student** head)
{
	int newno, newscore;
	char newname[20];
	while (1)
	{
		cout << "������Ҫ����ѧ����ѧ��:" << endl;
		cin >> newno;
		if (searchID(*head, newno) != NULL)
		{
			cout << "�Ѵ���" << endl;
		}
		else
		{
			cout << "������Ҫ�����ѧ�������ͳɼ�" << endl;
			cin >> newname >> newscore;
			student* temp = *head;
			student* newnode;
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			newnode = new(nothrow)student;
			if (newnode == NULL)
			{
				cout << "No memory" << endl;
				return;
			}
			else
			{
				strcpy(newnode->name, newname);
				newnode->no = newno;
				newnode->score = newscore;
				newnode->next = temp->next;
				temp->next = newnode;
			}
		}
		if (isContinue() == true)
			continue;
		else
			return;
	}
}

//����ѧ��ɾ��ѧ����Ϣ
void delbyID(student** head)
{
	int query;
	student* pretemp;
	student* temp;
	while (1)
	{
		pretemp = *head;
		temp = *head;
		cout << "��������Ҫɾ����ѧ��ѧ��" << endl;
		cin >> query;
		if (searchID(*head, query) == NULL)
		{
			cout << "������" << endl;
		}
		else
		{
			while (temp != NULL)
			{
				if (temp->no == query)
				{
					if (temp == *head)
					{
						*head = temp->next;
						delete temp;
						break;
					}
					else
					{
						pretemp->next = temp->next;
						delete temp;
						break;
					}
				}
				else
				{
					pretemp = temp;
					temp = temp->next;
				}
			}
		}
		if (isContinue() == true)
			continue;
		else
			return;
	}
}

//����ѧ�Ÿı�ѧ���ɼ�
void modibyID(student** head)
{
	int student_no, newscore;
	student* temp;
	while (1)
	{
		temp = *head;
		cout << "��������Ҫ�ı��ѧ��ѧ��" << endl;
		cin >> student_no;
		if (searchID(*head, student_no) != NULL)
		{
			cout << "�������³ɼ�" << endl;
			cin >> newscore;
			while (temp != NULL)
			{
				if (temp->no == student_no)
				{
					temp->score = newscore;
					break;
				}
				else
					temp = temp->next;
			}
		}
		else
		{
			cout << "������" << endl;
		}
		if (isContinue() == true)
			continue;
		else
			return;
	}
}

//�ͷ�����Ŀռ�
void quit(struct student* head)
{
	struct student* p, * q;
	p = head;
	while (p != NULL)
	{
		q = p->next;
		delete p;
		p = q;
	}
}

//��ʾ���ܲ˵�
void menu()
{
	int i;
	cout << endl;
	for (i = 0; i < 57; i++)
	{
		cout << '*';
	}
	cout << endl;
	cout << "*\t1 ��ʾ��¼\t2 ͳ�Ƽ�¼\t3 �����¼\t*\n";
	cout << "*\t4 ���Ҽ�¼\t5 ɾ����¼\t6 �޸ļ�¼\t*\n";
	cout << "*\t7 ��Ӽ�¼\t0 �˳�ϵͳ\t\t\t*\n";
	for (i = 0; i < 57; i++)
	{
		cout << '*';
	}
	cout << endl;
}
int main()
{
	int choice;
	char ch;
	struct student* head = NULL;
	if (read(&head) == fail)
		return 0;
	menu();
	while (1)
	{
		//		system("CLS");
		cout << "ѡ��˵���(0~7)��";
		cin >> choice;
		if (choice == 0)       //ѡ���˳�
		{
			cout << "\n ȷ���˳���?(y/n)" << endl;
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
			{
				quit(head);       //�������
				break;
			}
			else
				continue;
		}
		switch (choice)
		{
		case 1: disp(head); break;        //�������
		case 2: count(head); break;       //�������
		case 3: sort(&head); break;        //�������
		case 4: searchbyID(head); break;  //�������
		case 5: delbyID(&head); break;     //�������
		case 6: modibyID(&head); break;    //�������
		case 7: addbyID(&head); break;     //�������
		default:
			cout << "\n �����������������" << endl;
		}
	}
	return 0;
}
