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
		cout << "�������" << count1 + 1 << "��ѧ����ѧ�źͳɼ���" << endl;
		(temp1 + count1)->input_info();
	}
	for (int count1 = 0; count1 < student_num; count1 += 2)
	{
		cout << "��" << count1 + 1 << "��ѧ����ѧ����";
		(temp1 + count1)->show_no();
		cout << ",�ɼ�Ϊ";
		(temp1 + count1)->show_score();
		cout << endl;
	}
	cout << "�������" << endl;
	return 0;
}