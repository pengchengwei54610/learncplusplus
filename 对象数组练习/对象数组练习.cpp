#include<iostream>
using namespace std;
#define student_num 5
class student
{
private:
	int no;
	int score;
public:
	void show_score()
	{
		cout << score;
	}
	void show_no()
	{
		cout << no;
	}
	void input_info()
	{
		cin >> no >> score;
	}
};
int main()
{
	student temp[student_num];
	student* temp1 = temp;
	for (int count1 = 0; count1 < student_num; count1++)
	{
		cout << "请输入第" << count1 + 1 << "个学生的学号和成绩：" << endl;
		(temp1 + count1)->input_info();
	}
	for (int count1 = 0; count1 < student_num; count1 += 2)
	{
		cout << "第" << count1 + 1 << "个学生的学号是";
		(temp1 + count1)->show_no();
		cout << ",成绩为";
		(temp1 + count1)->show_score();
		cout << endl;
	}
	cout << "程序结束" << endl;
	return 0;
}