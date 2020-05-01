#include <iostream>

using namespace std;

class Student
{
public:
	Student(int n, float s) :num(n), score(s) {}
	void change(int n, float s) { num = n; score = s; }
	void display() { cout << num << " " << score << endl; }
private:
	int num;
	float score;
};
void fun(Student& temp, int num, float score)
{
	temp.change(num, score);
	temp.display();
}
int main()
{
	Student stud(101, 78.5);
	stud.display();
	fun(stud, 101, 80.5);
	return 0;
}

/*
输出结果：
101 78.5
101 80.5

分析：
参数初始化表对数据进行初始化，输出学号和成绩后再运行fun函数，通过成员函数进行修改，最后输出更改后的学号和成绩
*/