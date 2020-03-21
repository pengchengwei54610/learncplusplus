#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define Status int //c无bool类型
#define success 1
#define fail 0
struct student
{
	int no;                //学号
	char name[20];         //姓名
	int score;             //成绩
	struct student* next;  //下一结点
};
Status insert(FILE* infile, struct student** head)
{
	struct student* p, * newnode;
	newnode = (struct student*)malloc(sizeof(struct student));
	if (newnode == NULL)
	{
		printf("No memory\n");
		return fail;
	}
	fscanf(infile, "%d %s %d", &newnode->no, &newnode->name[0], &newnode->score);
	newnode->next = NULL;
	if ((*head) == NULL)
	{
		(*head) = newnode;
		return success;
	}
	p = *head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = newnode;
	return success;
}
void show_all(struct student* head)
{
	struct student* temp;
	temp = head;
	while (temp != NULL)
	{
		printf("学号：%d 姓名：%s 成绩：%d\n", temp->no, temp->name, temp->score);
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
		free(p);
		p = q;
	}
}
int main()
{
	int count1 = 0;
	struct student* head = NULL;
	int student_num;
	FILE* infile;
	infile = fopen("D:\\student.txt", "r");
	if (infile == NULL)
	{
		printf("打开文件失败\n");
		return -1;
	}
	fscanf(infile, "%d", &student_num);
	printf("所有的学生信息如下：\n");
	while (count1 < student_num)
	{
		if (insert(infile, &head) == fail)
			return 0;
		else
			count1++;
	}
	show_all(head);
	destroy_list(head);
	fclose(infile);
	return 0;
}
