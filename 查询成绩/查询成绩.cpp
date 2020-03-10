#include<iostream>
using namespace std;
#define student_num 10
struct student {
	int no;
	char name[20];
	float score[3];
};
bool input_info(student student_info[])
{
	int count1 = 0;
	int count2, count3;
	while (count1 < student_num)
	{
		count2 = 0;
		count3 = 0;
		cin >> student_info[count1].no >> student_info[count1].name >> student_info[count1].score[0] >> student_info[count1].score[1] >> student_info[count1].score[2];
		if (student_info[count1].no < 0 || student_info[count1].no>2147483647)
			return 0;
		while (student_info[count1].name[count2] != 0)
		{
			if ((student_info[count1].name[count2] >= 33 && student_info[count1].name[count2] <= 47) || student_info[count1].name[count2] >= 123 || (student_info[count1].name[count2] >= 58 && student_info[count1].name[count2] <= 64))
			{
				return 0;
			}
			count2++;
		}
		while (count3 < 3)
		{
			if (student_info[count1].score[count3] < 0 || student_info[count1].score[count3]>150)
				return 0;
			count3++;
		}
		count1++;
	}
	return 1;
}
void output_class_average(student student_info[])
{
	int count1 = 0;
	int count2;
	float class_sumscore[3] = { 0,0,0 };
	cout << "本班3门课的平均成绩分别为：";
	while (count1 < 3)
	{
		count2 = 0;
		while (count2 < student_num)
		{
			class_sumscore[count1] += student_info[count2].score[count1];
			count2++;
		}
		count1++;
	}
	for (count1 = 0; count1 < 3; count1++)
	{
		cout << class_sumscore[count1] / student_num << ' ';
	}
	cout << endl;
}
void output_beststudent(student student_info[])
{
	float student_score[student_num] = { 0 };
	float best_averagescore;
	int flag = 0;
	int count1 = 0;
	while (count1 < student_num)
	{
		student_score[count1] = student_info[count1].score[0] + student_info[count1].score[1] + student_info[count1].score[2];
		if (flag != count1)
		{
			if (student_score[flag] < student_score[count1])
			{
				flag = count1;
			}
		}
		count1++;
	}
	best_averagescore = (student_info[flag].score[0] + student_info[flag].score[1] + student_info[flag].score[2]) / 3;
	cout << "平均分最高的学生：" << endl;
	for (count1 = 0; count1 < student_num; count1++)
	{
		if (student_score[count1] == student_score[flag])
			cout << "学号：" << student_info[count1].no << ' ' << "姓名：" << student_info[count1].name << ' ' << "3门课成绩：" << student_info[count1].score[0] << ' ' << student_info[count1].score[1] << ' ' << student_info[count1].score[2] << ' ' << "平均分：" << best_averagescore << endl;
	}
}
int main()
{
	student student_info[student_num];
	if (input_info(student_info) == 0)
	{
		cout << "输入有误！" << endl;
		return 0;
	}
	output_class_average(student_info);
	output_beststudent(student_info);
	return 0;
}