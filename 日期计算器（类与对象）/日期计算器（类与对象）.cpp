#include<iostream>
using namespace std;
class dateToDay
{
public:
	dateToDay(int, int, int);    // ͨ�����ι���
	// dateToDay();              // ����ʱ�Ӽ��̶��� ʵ�ַ�ʽ��ѡһ
	void setDate(int, int, int); // ��������
	// void setDate();           // �Ӽ��̶����������� ʵ�ַ�ʽ��ѡһ
	// �Ϸ��Լ��Ӧ���ڹ���/����ʱ���
	void display();              // �����������(�������ڵڼ���)
private:
	bool checkLeap();            // �ú������ڼ������
	bool checkValid();           // �ú������ڼ��Ϸ�
	int computeDay();            // �ú������ڼ�������
	int year;
	int month;
	int day;
};
dateToDay::dateToDay(int tempa, int tempb, int tempc)
{
	year = tempa;
	month = tempb;
	day = tempc;
	if (checkValid() == 0)
	{
		cout << "�������󣡳����˳�" << endl;
		exit(-1);
	}
}
void dateToDay::setDate(int tempa, int tempb, int tempc)
{
	year = tempa;
	month = tempb;
	day = tempc;
	if (checkValid() == 0)
	{
		cout << "�������󣡳����˳�" << endl;
		exit(-1);
	}
}
bool dateToDay::checkLeap()
{
	if (year % 100 == 0)
		if (year % 400 == 0)
			return 1;
		else
			return 0;
	else if (year % 4 == 0)
		return 1;
	else
		return 0;
}
bool dateToDay::checkValid()
{
	bool if_leap;
	if_leap = checkLeap();
	if (month == 1)
		if (day >= 1 && day <= 31)
			return 1;
		else
			return 0;
	else if (month == 2)
		if (day >= 1 && day <= 28 + if_leap)
			return 1;
		else
			return 0;
	else if (month == 3)
		if (day >= 1 && day <= 31)
			return 1;
		else
			return 0;
	else if (month == 4)
		if (day >= 1 && day <= 30)
			return 1;
		else
			return 0;
	else if (month == 5)
		if (day >= 1 && day <= 31)
			return 1;
		else
			return 0;
	else if (month == 6)
		if (day >= 1 && day <= 30)
			return 1;
		else
			return 0;
	else if (month == 7)
		if (day >= 1 && day <= 31)
			return 1;
		else
			return 0;
	else if (month == 8)
		if (day >= 1 && day <= 31)
			return 1;
		else
			return 0;
	else if (month == 9)
		if (day >= 1 && day <= 30)
			return 1;
		else
			return 0;
	else if (month == 10)
		if (day >= 1 && day <= 31)
			return 1;
		else
			return 0;
	else if (month == 11)
		if (day >= 1 && day <= 30)
			return 1;
		else
			return 0;
	else if (month == 12)
		if (day >= 1 && day <= 31)
			return 1;
		else
			return 0;
	else
		return 0;
}
int dateToDay::computeDay()
{
	bool if_rightful;
	if_rightful = checkValid();
	if (if_rightful == 0)
		return 0;
	bool if_leap;
	if_leap = checkLeap();
	if (month == 1)
		return day;
	else if (month == 2)
		return (31 + day);
	else if (month == 3)
		return (59 + if_leap + day);
	else if (month == 4)
		return (90 + if_leap + day);
	else if (month == 5)
		return (120 + if_leap + day);
	else if (month == 6)
		return (151 + if_leap + day);
	else if (month == 7)
		return (181 + if_leap + day);
	else if (month == 8)
		return (212 + if_leap + day);
	else if (month == 9)
		return (243 + if_leap + day);
	else if (month == 10)
		return (273 + if_leap + day);
	else if (month == 11)
		return (304 + if_leap + day);
	else if (month == 12)
		return (334 + if_leap + day);
	else
		return 0;
}
void dateToDay::display()
{
	int days = computeDay();
	if (days == 0)
		cout << "�������󣡳����˳�" << endl;
	else
		cout << year << '-' << month << '-' << day << "��" << year << "��ĵ�" << days << "��" << endl;
}
int main()
{
	int year, month, day;
	cout << "������һ�����ڣ�" << endl;
	cin >> year >> month >> day;
	dateToDay date1(year, month, day);
	date1.display();
	cout << "������һ�����ڣ�" << endl;
	cin >> year >> month >> day;
	date1.setDate(year, month, day);
	date1.display();
	return 0;
}