#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
using namespace std;
#define Status bool 
#define success 1
#define fail 0
struct student
{
	int no;                //学号
	char name[20];         //姓名
	int score;             //成绩
	struct student* next;  //下一结点
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
		cout << "打开文件失败" << endl;
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
		cout << "学号：" << temp->no << " 姓名：" << temp->name << " 成绩：" << temp->score << endl;
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
			cout << "成绩错误" << endl;
			return fail;
		}
		temp = temp->next;
	}
	return success;
}
void output_scoreresult(score_num s1)
{
	cout << "统计信息如下：" << endl;
	cout << "优： " << s1.excellent << "人  " << "良： " << s1.good << "人  " << "中： " << s1.medium << "人  " << "及格： " << s1.pass << "人  " << "不及格： " << s1.failed << "人  " << endl;
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
	score_num s1;
	struct student* head = NULL;
	read(&head);
	init_scoresum(s1);
	add_sum(head, s1);
	output_scoreresult(s1);
	destroy_list(head);
	return 0;
}
