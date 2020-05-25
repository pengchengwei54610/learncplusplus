#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>

using namespace std;

inline void wait_for_press()
{
	cout << endl << "�����������..." << endl;
	_getch();
}

/**********************************************
*
*    TO-DO:
*        �벹ȫ������Ĵ��룬��ֻ�ύ���������Ĵ��롣
*
***********************************************/
#include<time.h>
//����ÿ���µ�����
int days(int year, int month)
{
	bool is_leap;
	if (year % 100 == 0)
		if (year % 400 == 0)
			is_leap = 1;
		else
			is_leap = 0;
	else if (year % 4 == 0)
		is_leap = 1;
	else
		is_leap = 0;
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		return 31;
	else if (month == 2)
		return(28 + is_leap);
	else
		return 30;
}
class Date
{
private:
	int year;
	int month;
	int day;
	bool is_leap;
public:
	void checkLeap();            // �ú������ڼ������
	Date()//�޲���ʱ��ϵͳ��ǰʱ���ʼ��
	{
		time_t temp;
		time(&temp);
		tm* temp1 = localtime(&temp);
		year = 1900 + temp1->tm_year;
		month = temp1->tm_mon + 1;
		day = temp1->tm_mday;
		checkLeap();
	}
	Date(int year1, int month1, int day1)
	{
		year = year1;
		month = month1;
		day = day1;
		checkLeap();
	}
	void set(int year1, int month1 = 1, int day1 = 1)
	{
		if (year1 == 0)
			;
		else
			year = year1;
		if (month1 == 0)
			;
		else
			month = month1;
		if (day1 == 0)
			;
		else
			day = day1;
	}
	Date(int num);
	friend istream& operator >>(istream& in, Date& a);
	friend ostream& operator <<(ostream& out, Date& a);
	operator int();
	Date operator +(int a);
	Date operator -(int a);
	Date& operator++();//ǰ׺++
	Date& operator--();//ǰ׺--
	Date operator++(int);//��׺++
	Date operator--(int);//��׺--
	bool operator>(Date a);
	bool operator>=(Date a);
	bool operator==(Date a);
	bool operator<(Date a);
	bool operator<=(Date a);
	bool operator!=(Date a);
};
istream& operator>>(istream& in, Date& a)
{
	in >> a.year >> a.month >> a.day;
	return in;
}
ostream& operator<<(ostream& out, Date& a)
{
	out << a.year << "��" << a.month << "��" << a.day << "��";
	return out;
}
void Date::checkLeap()
{
	if (year % 100 == 0)
		if (year % 400 == 0)
			is_leap = 1;
		else
			is_leap = 0;
	else if (year % 4 == 0)
		is_leap = 1;
	else
		is_leap = 0;
	return;
}
Date::Date(int num)
{
	year = 1900;
	month = 1;
	day = 1;
	day += (num - 1);
	while (day > days(year, month))
	{
		day -= days(year, month);
		if (month == 12)
		{
			month = 1;
			year++;
		}
		else
		{
			month++;
		}
	}
	checkLeap();
	return;
}
Date::operator int()
{
	int count1 = 0;
	int year1 = 1900;
	int month1 = 1;
	for (; year1 < year; year1++)
	{
		for (int count2 = 1; count2 <= 12; count2++)
		{
			count1 += days(year1, count2);
		}
	}
	for (; month1 < month; month1++)
	{
		count1 += days(year1, month1);
	}
	count1 += day;
	return count1;
}
Date Date::operator +(int a)
{
	Date c;
	c.year = year;
	c.month = month;
	c.day = day;
	c.day += a;
	if (a >= 0)
	{
		while (c.day > days(c.year, c.month))
		{
			c.day -= days(c.year, c.month);
			if (c.month == 12)
			{
				c.month = 1;
				c.year++;
			}
			else
			{
				c.month++;
			}
		}
	}
	else
	{
		while (c.day <= 0)
		{
			if (c.month == 1)
			{
				c.month = 12;
				c.year--;
			}
			else
			{
				c.month--;
			}
			c.day += days(c.year, c.month);
		}
	}
	return c;
}
Date Date::operator -(int a)
{
	Date c;
	c.year = year;
	c.month = month;
	c.day = day;
	c.day -= a;
	if (a >= 0)
	{
		while (c.day > days(c.year, c.month))
		{
			c.day -= days(c.year, c.month);
			c.year++;
			if (c.month == 12)
			{
				c.month = 1;
			}
			else
			{
				c.month++;
			}
		}
	}
	else
	{
		while (c.day <= 0)
		{
			if (c.month == 1)
			{
				c.month = 12;
				c.year--;
			}
			else
			{
				c.month--;
			}
			c.day += days(c.year, c.month);
		}
	}
	return c;
};
Date& Date::operator++()
{
	day++;
	if (day > days(year, month))
	{
		day = 1;
		if (month != 12)
		{
			month++;
		}
		else
		{
			month = 1;
			year++;
		}
	}
	return *this;
}
Date& Date::operator--()
{
	day--;
	if (day == 0)
	{
		if (month != 1)
		{
			month--;
			day = days(year, month);
		}
		else
		{
			month = 12;
			year--;
			day = 31;
		}
	}
	return *this;
}
Date Date::operator++(int)
{
	Date c1(*this);
	day++;
	if (day > days(year, month))
	{
		day = 1;
		if (month != 12)
		{
			month++;
		}
		else
		{
			month = 1;
			year++;
		}
	}
	return c1;
}
Date Date::operator--(int)
{
	Date c1(*this);
	day--;
	if (day == 0)
	{
		if (month != 1)
		{
			month--;
			day = days(year, month);
		}
		else
		{
			month = 12;
			year--;
			day = 31;
		}
	}
	return c1;
}
bool Date::operator>(Date a)
{
	if (year >= a.year)
	{
		if (year > a.year)
			return 1;
		else if (month >= a.month)
		{
			if (month > a.month)
				return 1;
			else
				return (day > a.day);
		}
		else
			return 0;
	}
	else
		return 1;
}
bool Date::operator<(Date a)
{
	if (year >= a.year)
	{
		if (year > a.year)
			return 0;
		else if (month >= a.month)
		{
			if (month > a.month)
				return 0;
			else
				return (day < a.day);
		}
		else
			return 1;
	}
	else
		return 0;
}
bool Date::operator>=(Date a)
{
	if (year >= a.year)
	{
		if (year > a.year)
			return 1;
		else if (month >= a.month)
		{
			if (month > a.month)
				return 1;
			else
				return (day >= a.day);
		}
		else
			return 0;
	}
	else
		return 1;
}
bool Date::operator<=(Date a)
{
	if (year >= a.year)
	{
		if (year > a.year)
			return 0;
		else if (month >= a.month)
		{
			if (month > a.month)
				return 0;
			else
				return (day <= a.day);
		}
		else
			return 1;
	}
	else
		return 0;
}
bool Date::operator==(Date a)
{
	if (year == a.year && month == a.month && day == a.day)
		return 1;
	else
		return 0;
}
bool Date::operator!=(Date a)
{
	if (year == a.year && month == a.month && day == a.day)
		return 0;
	else
		return 1;
}
/**********************************************
*
*    TO-DO END
*
***********************************************/

int main()
{
	{
		Date d1;
		Date d2(1907, 5, 20);

		cout << "���Գ�ʼ����cout����" << endl;

		cout << "d1Ӧ���ǽ��죬 ʵ��Ϊ��" << d1 << endl;
		cout << "d2Ӧ����1907��5��20�գ�ʵ��Ϊ��" << d2 << endl;

		wait_for_press();
	}

	{
		Date d1, d2, d3, d4;

		cout << "����set��cin����" << endl;
		d1.set(1907, 5, 20);
		d2.set(1907, 5);
		d3.set(1907);

		cout << "d1Ӧ����1907��5��20�գ�ʵ��Ϊ��" << d1 << endl;
		cout << "d2Ӧ����1907��5��1�գ� ʵ��Ϊ��" << d2 << endl;
		cout << "d3Ӧ����1907��1��1�գ� ʵ��Ϊ��" << d3 << endl;

		cout << "������ĳ����" << endl;
		cin >> d4;
		d4.set(0, 0, 0);
		cout << "d4Ӧ����������������ڣ�ʵ��Ϊ��" << d4 << endl;

		wait_for_press();
	}

	{
		Date d1(10);
		Date d2(250);
		Date d3(1314);
		Date d4(13145);

		cout << "����ת�����캯��" << endl;

		cout << "d1Ӧ����1900��1��10�գ�  ʵ��Ϊ��" << d1 << endl;
		cout << "d2Ӧ����1900��9��7�գ�ʵ��Ϊ��" << d2 << endl;
		cout << "d3Ӧ����1903��8��7�գ�  ʵ��Ϊ��" << d3 << endl;
		cout << "d4Ӧ����1935��12��28�գ�ʵ��Ϊ��" << d4 << endl;

		Date d5, d6;
		d5 = 30041;
		cout << "d5Ӧ����1982��4��1�գ� ʵ��Ϊ��" << d5 << endl;

		d6 = 42301;
		cout << "d6Ӧ����2015��10��25�գ� ʵ��Ϊ��" << d6 << endl;

		wait_for_press();
	}

	{
		Date d1(1900, 1, 1);
		Date d2(1907, 5, 20);
		Date d3(1982, 4, 1);
		Date d4(2015, 10, 25);

		cout << "��������ת������" << endl;

		cout << "d1Ӧ����1��     ʵ��Ϊ��" << int(d1) << endl;
		cout << "d2Ӧ����2696�� ʵ��Ϊ��" << int(d2) << endl;
		cout << "d3Ӧ����30041�� ʵ��Ϊ��" << int(d3) << endl;
		cout << "d4Ӧ����42301�� ʵ��Ϊ��" << int(d4) << endl;

		wait_for_press();
	}

	{
		Date d1(1907, 5, 20);
		Date d2;

		cout << "��������+/-" << endl;

		d2 = d1 + 520;
		cout << "d2Ӧ����1908��10��21�գ�    ʵ��Ϊ��" << d2 << endl;

		d2 = 520 + d1;
		cout << "d2Ӧ����1908��10��21�գ�    ʵ��Ϊ��" << d2 << endl;

		d2 = d1 - 3;
		cout << "d2Ӧ����1907��5��17�գ�   ʵ��Ϊ��" << d2 << endl;

		d1.set(2016, 5, 20);
		d2.set(2015, 5, 20);
		cout << "d1-d2Ӧ����366��ʵ��Ϊ��" << d1 - d2 << endl;

		d1.set(2018, 5, 20);
		d2.set(2017, 5, 20);
		cout << "d1-d2Ӧ����365��ʵ��Ϊ��" << d1 - d2 << endl;

		wait_for_press();
	}

	{
		Date d1, d2;

		cout << "��������++/--" << endl;

		d1.set(1907, 5, 20);
		d2 = d1++;
		cout << "d1Ӧ����1907��5��21�գ�  ʵ��Ϊ��" << d1 << endl;
		cout << "d2Ӧ����1907��5��20�գ�  ʵ��Ϊ��" << d2 << endl;

		d1.set(1907, 5, 20);
		d2 = ++d1;
		cout << "d1Ӧ����1907��5��21�գ�  ʵ��Ϊ��" << d1 << endl;
		cout << "d2Ӧ����1907��5��21�գ�  ʵ��Ϊ��" << d2 << endl;

		d1.set(1907, 1, 1);
		d2 = d1--;
		cout << "d1Ӧ����1906��12��31�գ� ʵ��Ϊ��" << d1 << endl;
		cout << "d2Ӧ����1907��1��1�գ�  ʵ��Ϊ��" << d2 << endl;

		d1.set(1907, 1, 1);
		d2 = --d1;
		cout << "d1Ӧ����1906��12��31�գ� ʵ��Ϊ��" << d1 << endl;
		cout << "d2Ӧ����1906��12��31�գ� ʵ��Ϊ��" << d2 << endl;

		d1.set(2016, 2, 28);
		d2 = d1++;
		cout << "d1Ӧ����2016��2��29�գ� ʵ��Ϊ��" << d1 << endl;
		cout << "d2Ӧ����2016��2��28�գ� ʵ��Ϊ��" << d2 << endl;

		d1.set(2018, 3, 1);
		d2 = d1--;
		cout << "d1Ӧ����2018��2��28�գ� ʵ��Ϊ��" << d1 << endl;
		cout << "d2Ӧ����2018��3��1�գ�  ʵ��Ϊ��" << d2 << endl;

		wait_for_press();
	}


	{
		Date d1(1907, 5, 20);
		Date d2(1907, 5, 20);
		Date d3(1907, 1, 1);

		cout << "���ԱȽ������" << endl;

		cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (d1 > d3) << endl;
		cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (d2 >= d3) << endl;
		cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (d1 < d3) << endl;
		cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (d2 <= d3) << endl;
		cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (d1 == d2) << endl;
		cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (d1 != d1) << endl;

		wait_for_press();
	}

	return 0;
}