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
Status initial_list(struct student** head)
{
	*head = (student*)malloc(sizeof(student));
	if (*head == NULL)
	{
		cout << "No memory" << endl;
		return fail;
	}
	else
	{
		(*head)->next = NULL;
		return success;
	}
}
Status read(struct student** head)
{
	student* temp1;
	temp1 = *head;
	int student_num;
	int count1 = 0;
	fstream infile("D:\\student.txt", ios::in);
	if (!infile)
	{
		cout << "打开文件失败" << endl;
		return fail;
	}
	infile >> student_num;
	struct student* newnode;
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
		temp1->next = newnode;
		temp1 = temp1->next;
		/*if ((*head) == NULL)
		{
			(*head) = newnode;
			continue;
		}
		p = *head;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = newnode;*/
	}
	infile.close();
	return success;
}
//int count_list(struct student* head)
//{
//	int count1 = 0;
//	student* temp = head;
//	while (temp != NULL)
//	{
//		count1++;
//		temp = temp->next;
//	}
//	return count1;
//}
//void bubblesort(struct student** head)
//{
//	int list_length = count_list(*head);
//	int tempno, tempscore;
//	char tempname[20];
//	int count1, count2;
//	student* temp;
//	for (count1 = 1; count1 < list_length; count1++)
//	{
//		for (temp = *head, count2 = 0; count2 < list_length - count1; temp = temp->next, count2++)
//		{
//			if ((temp->score) < ((temp->next)->score))
//			{
//				tempno = temp->no;
//				tempscore = temp->score;
//				strcpy(tempname, temp->name);
//				temp->no = temp->next->no;
//				temp->score = temp->next->score;
//				strcpy(temp->name, temp->next->name);
//				temp->next->no = tempno;
//				temp->next->score = tempscore;
//				strcpy(temp->next->name, tempname);
//			}
//		}
//	}
//	for (count1 = 1; count1 < list_length; count1++)
//	{
//		for (temp = *head, count2 = 0; count2 < list_length - count1; temp = temp->next, count2++)
//		{
//			if ((temp->score) == ((temp->next)->score))
//			{
//				if ((temp->no) > ((temp->next)->no))
//				{
//					tempno = temp->no;
//					tempscore = temp->score;
//					strcpy(tempname, temp->name);
//					temp->no = temp->next->no;
//					temp->score = temp->next->score;
//					strcpy(temp->name, temp->next->name);
//					temp->next->no = tempno;
//					temp->next->score = tempscore;
//					strcpy(temp->next->name, tempname);
//				}
//			}
//
//		}
//	}
//}
void show_all(struct student* head)
{
	struct student* temp;
	temp = head->next;
	while (temp != NULL)
	{
		cout << "学号：" << temp->no << " 姓名：" << temp->name << " 成绩：" << temp->score << endl;
		temp = temp->next;
	}
}
//void init_scoresum(score_num& s1)
//{
//	s1.good = 0;
//	s1.excellent = 0;
//	s1.failed = 0;
//	s1.medium = 0;
//	s1.pass = 0;
//}
//Status add_sum(student* head, score_num& s1)
//{
//	student* temp;
//	temp = head;
//	while (temp != NULL)
//	{
//		if (temp->score < 60)
//			s1.failed++;
//		else if (temp->score < 70)
//			s1.pass++;
//		else if (temp->score < 80)
//			s1.medium++;
//		else if (temp->score < 90)
//			s1.good++;
//		else if (temp->score <= 100)
//			s1.excellent++;
//		else
//		{
//			cout << "成绩错误" << endl;
//			return fail;
//		}
//		temp = temp->next;
//	}
//	return success;
//}
//void output_scoreresult(score_num s1)
//{
//	cout << "统计信息如下：" << endl;
//	cout << "优： " << s1.excellent << "人  " << "良： " << s1.good << "人  " << "中： " << s1.medium << "人  " << "及格： " << s1.pass << "人  " << "不及格： " << s1.failed << "人  " << endl;
//}
bool isContinue() {
	cout << "是否继续?(y/n): \n";
	char tmp;
	cin >> tmp;
	if (tmp == 'Y' || tmp == 'y')return true;
	return false;
}
student* searchbyID(student* head, int query)
{
	student* temp = head->next;
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
Status deletebyID(student** head, int query)
{
	student* temp = *head;
	student* temp1;
	while (temp->next != NULL)
	{
		if ((temp->next)->no == query)
		{
			temp1 = temp->next->next;
			delete temp->next;
			temp->next = temp1;
			return success;
		}
		else
		{
			temp = temp->next;
		}
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
	struct student* head;
	if (initial_list(&head) == fail)
		return 0;
	if (read(&head) == fail)
		return 0;
	while (1)
	{
		int query;
		cin >> query;
		if (searchbyID(head, query) == NULL)
			cout << "不存在" << endl;
		else
			deletebyID(&head, query);
		if (!isContinue())
			break;
	}
	show_all(head);
	destroy_list(head);
	return 0;
}
