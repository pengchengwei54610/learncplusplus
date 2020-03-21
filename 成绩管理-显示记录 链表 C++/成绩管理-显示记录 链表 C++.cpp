#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
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
Status insert(struct student** head)
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
	struct student* head = NULL;
	cout << "���е�ѧ����Ϣ���£�" << endl;
	insert(&head);
	show_all(head);
	destroy_list(head);
	return 0;
}
