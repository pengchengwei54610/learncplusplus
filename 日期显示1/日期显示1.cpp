#include <iostream>

using namespace std;
class Date; // ��Date�����ǰ��������
void display(Date& d);

class Time  // ����Time��
{
public:
	Time(int, int, int);    // �������캯��
	friend void display(Date&, Time&);   // display�ǳ�Ա�������β���Date����������
private:
	int hour;
	int minute;
	int sec;
};

class Date   // ����Date��
{
public:
	Date(int, int, int);                // �������캯��
	friend void display(Date&, Time&);  // ����Time�е�display����Ϊ�������Ԫ��Ա����
private:
	int month;
	int day;
	int year;
};
void display(Date& d, Time& t)             // display������������ꡢ�¡��պ�ʱ���֡���
{
	// ����Date������е�˽������
	cout << d.month << "/" << d.day << "/" << d.year << endl;
	// ���ñ�������е�˽������
	cout << t.hour << ":" << t.minute << ":" << t.sec << endl;
}
Time::Time(int h, int m, int s)         // ������Time�Ĺ��캯��
{
	hour = h;
	minute = m;
	sec = s;
}



Date::Date(int m, int d, int y)         // ������Date�Ĺ��캯��
{
	month = m;
	day = d;
	year = y;
}

int main()
{
	Time t1(10, 13, 56);     // ����Time�����t1
	Date d1(12, 25, 2004);   // ����Date�����d1
	display(d1, t1);          // ����t1�е�display������ʵ����Date�����d1
	return 0;
}