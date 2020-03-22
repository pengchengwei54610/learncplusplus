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
void bubblesort(struct student** head)
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
void show_all(struct student* head)
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
Status add_sum(student* head, score_num& s1)
{
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
void output_scoreresult(score_num s1)
{
	cout << "ͳ����Ϣ���£�" << endl;
	cout << "�ţ� " << s1.excellent << "��  " << "���� " << s1.good << "��  " << "�У� " << s1.medium << "��  " << "���� " << s1.pass << "��  " << "������ " << s1.failed << "��  " << endl;
}
bool isContinue() {
	cout << "�Ƿ����?(y/n): \n";
	char tmp;
	cin >> tmp;
	if (tmp == 'Y' || tmp == 'y')return true;
	return false;
}
Status searchID(student* head, int query)
{
	student* temp = head;
	while (temp != NULL)
	{
		if (temp->no == query)
		{
			cout << "ѧ�ţ�" << temp->no << " ������" << temp->name << " �ɼ���" << temp->score << endl;
			return success;
		}
		else
			temp = temp->next;
	}
	return fail;
}
void destroy_list(struct student* head)
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
int main()
{
	//	score_num s1;
	struct student* head = NULL;
	if (read(&head) == fail)
		return 0;
	while (1)
	{
		int query;
		cin >> query;
		if (searchID(head, query) == fail)
			cout << "������" << endl;
		if (!isContinue())
			break;
	}
	//	bubblesort(&head);
//	cout << "�������ϢΪ��" << endl;
	//	show_all(head);
	destroy_list(head);
	return 0;
}
