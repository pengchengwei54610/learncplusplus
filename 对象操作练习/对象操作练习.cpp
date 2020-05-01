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
��������
101 78.5
101 80.5

������
������ʼ��������ݽ��г�ʼ�������ѧ�źͳɼ���������fun������ͨ����Ա���������޸ģ����������ĺ��ѧ�źͳɼ�
*/