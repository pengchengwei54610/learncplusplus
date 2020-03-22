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
//读取文件，简历学生信息链表
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
//计算学生个数
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

//按照学生成绩为第一关键字降序排序，学生学号为第二关键字升序排序
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

//显示所有学生数据
void disp(struct student* head)
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

//分类别向score_num结构体加数
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
			cout << "成绩错误" << endl;
			return fail;
		}
		temp = temp->next;
	}
	return success;
}
//输出分段结果
void output_scoreresult(score_num s1)
{
	cout << "统计信息如下：" << endl;
	cout << "优： " << s1.excellent << "人  " << "良： " << s1.good << "人  " << "中： " << s1.medium << "人  " << "及格： " << s1.pass << "人  " << "不及格： " << s1.failed << "人  " << endl;
}
//学生成绩分段并输出每段对应人数
void count(student* head)
{
	score_num s1;
	add_sum(head, s1);
	output_scoreresult(s1);
}

//小功能结束判断
bool isContinue() {
	cout << "是否继续?(y/n): \n";
	char tmp;
	cin >> tmp;
	if (tmp == 'Y' || tmp == 'y')return true;
	return false;
}
//根据学号返回寻找学生的指针
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
//根据学号寻找学生
void searchbyID(student* head)
{
	int query;
	student* temp;
	while (1)
	{
		cout << "请输入需要查找的学号" << endl;
		cin >> query;
		temp = head;
		while (temp != NULL)
		{
			if (temp->no == query)
			{
				cout << "学号：" << temp->no << " 姓名：" << temp->name << " 成绩：" << temp->score << endl;
				break;
			}
			else
				temp = temp->next;
		}
		if (temp == NULL)
			cout << "不存在" << endl;
		if (isContinue() == true)
			continue;
		else
			return;
	}
}
//根据学号添加学生信息
void addbyID(student** head)
{
	int newno, newscore;
	char newname[20];
	while (1)
	{
		cout << "请输入要插入学生的学号:" << endl;
		cin >> newno;
		if (searchID(*head, newno) != NULL)
		{
			cout << "已存在" << endl;
		}
		else
		{
			cout << "请输入要插入的学生姓名和成绩" << endl;
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

//根据学号删除学生信息
void delbyID(student** head)
{
	int query;
	student* pretemp;
	student* temp;
	while (1)
	{
		pretemp = *head;
		temp = *head;
		cout << "请输入需要删除的学生学号" << endl;
		cin >> query;
		if (searchID(*head, query) == NULL)
		{
			cout << "不存在" << endl;
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

//根据学号改变学生成绩
void modibyID(student** head)
{
	int student_no, newscore;
	student* temp;
	while (1)
	{
		temp = *head;
		cout << "请输入需要改变的学生学号" << endl;
		cin >> student_no;
		if (searchID(*head, student_no) != NULL)
		{
			cout << "请输入新成绩" << endl;
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
			cout << "不存在" << endl;
		}
		if (isContinue() == true)
			continue;
		else
			return;
	}
}

//释放申请的空间
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

//显示功能菜单
void menu()
{
	int i;
	cout << endl;
	for (i = 0; i < 57; i++)
	{
		cout << '*';
	}
	cout << endl;
	cout << "*\t1 显示记录\t2 统计记录\t3 排序记录\t*\n";
	cout << "*\t4 查找记录\t5 删除记录\t6 修改记录\t*\n";
	cout << "*\t7 添加记录\t0 退出系统\t\t\t*\n";
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
		cout << "选择菜单项(0~7)：";
		cin >> choice;
		if (choice == 0)       //选择退出
		{
			cout << "\n 确定退出吗?(y/n)" << endl;
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
			{
				quit(head);       //自行设计
				break;
			}
			else
				continue;
		}
		switch (choice)
		{
		case 1: disp(head); break;        //自行设计
		case 2: count(head); break;       //自行设计
		case 3: sort(&head); break;        //自行设计
		case 4: searchbyID(head); break;  //自行设计
		case 5: delbyID(&head); break;     //自行设计
		case 6: modibyID(&head); break;    //自行设计
		case 7: addbyID(&head); break;     //自行设计
		default:
			cout << "\n 输入错误，请重新输入" << endl;
		}
	}
	return 0;
}
