#include <iostream>

using namespace std;

class Time
{
	//����1����Ա������public�������ⲿ�޷�����
public:

	void set_time(void);
	void show_time(void);
	//����2�����ݳ�Ա��Ϊprivate���ַ�װ
private:

	int hour;
	int minute;
	int sec;
};

Time t;

int main()
{
	//����3���ⲿ���ó�Ա������Ҫ������
	//set_time();
	//show_time();

	t.set_time();
	t.show_time();

	return 0;
}

//����4���ⲿ�����Ա������Ҫ��������������޶���,�ҷ������Ͳ�ƥ��
//int set_time(void)
void Time::set_time(void)

{
	//����1��������ʾ
	cout << "������ʱ���֣���" << endl;

	cin >> t.hour;
	cin >> t.minute;
	cin >> t.sec;


}

//����5���ⲿ�����Ա������Ҫ��������������޶���,�ҷ������Ͳ�ƥ��
//int show_time(void)
void Time::show_time(void)

{
	//����2�������ʾ
	cout << "�������ʱ����";

	cout << t.hour << ":" << t.minute << ":" << t.sec << endl;

	//����3���˳���ʾ
	cout << "�����˳�" << endl;
}