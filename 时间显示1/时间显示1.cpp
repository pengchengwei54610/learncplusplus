#include <iostream>

using namespace std;

class Time                       // ����Time��
{
private:                          // ���ݳ�ԱΪ���е�
	int hour;
	int minute;
	int sec;
public:
	void set_time()
	{
		cout << "�������趨��ʱ�䣬��ʱ �� ���ʽ����" << endl;
		cin >> hour;              // �������е������������趨��ʱ��
		cin >> minute;
		cin >> sec;
	}
	void show_time()
	{
		cout << "����Ϊ���趨��ʱ��";
		cout << hour << ":" << minute << ":" << sec << endl;
		cout << "�����˳�" << endl;
	}

};

int main()
{
	Time t1;                     // ����t1ΪTime�����	
	t1.set_time();
	t1.show_time();
	return 0;
}