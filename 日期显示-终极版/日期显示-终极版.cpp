#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include<time.h>

using namespace std;

inline void wait_for_press()
{
	cout << endl << "按任意键继续..." << endl;
	_getch();
}

//计算每个月的天数
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
protected:
	int year;
	int month;
	int day;
	bool is_leap;
public:
	int showyear()
	{
		return year;
	}
	int showmonth()
	{
		return month;
	}
	int showday()
	{
		return day;
	}
	void checkLeap();            // 该函数用于检查闰年
	Date()//无参数时用系统当前时间初始化
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
		if (year1 <= 0)
			;
		else
			year = year1;
		if (month1 <= 0)
			;
		else
			month = month1;
		if (day1 <= 0)
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
	Date& operator++();//前缀++
	Date& operator--();//前缀--
	Date operator++(int);//后缀++
	Date operator--(int);//后缀--
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
	out << a.year << "年" << a.month << "月" << a.day << "日";
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
class Time
{
protected:
	long long h, m, s;
public:
	long long showhour()
	{
		return h;
	}
	long long showminute()
	{
		return m;
	}
	long long showsecond()
	{
		return s;
	}
	Time(int h1, int m1, int s1);
	void set(int h1, int m1, int s1);
	void set(int s1);
	friend istream& operator >>(istream& in, Time& a);
	friend ostream& operator <<(ostream& out, Time& a);
	Time operator +(long long a);
	Time operator -(long long a);
	Time operator =(Time a);
	Time operator =(int a);
	Time& operator++();//前缀++
	Time& operator--();//前缀--
	Time operator++(int);//后缀++
	Time operator--(int);//后缀--
	bool operator>(Time a);
	bool operator>=(Time a);
	bool operator==(Time a);
	bool operator<(Time a);
	bool operator<=(Time a);
	bool operator!=(Time a);
};
Time::Time(int h1 = -1, int m1 = -1, int s1 = -1)
{
	if (h1 < 0 && m1 < 0 && s1 < 0)
	{
		h = 0;
		m = 0;
		s = 0;
	}
	else if (h1 >= 0 && m1 < 0 && s1 < 0)
	{
		h = (h1 / 3600) % 24;
		m = (h1 / 60) % 60;
		s = h1 % 60;
	}
	else
	{
		h = h1;
		m = m1;
		s = s1;
	}
}
void Time::set(int s1)
{
	h = (s1 / 3600) % 24;
	m = (s1 / 60) % 60;
	s = s1 % 60;
}
void Time::set(int h1, int m1, int s1)
{

	if (h1 == -1)
		;
	else
		h = h1;
	if (m1 == -1)
		;
	else
		m = m1;
	if (s1 == -1)
		;
	else
		s = s1;
}
istream& operator>>(istream& in, Time& a)
{
	in >> a.h >> a.m >> a.s;
	return in;
}
ostream& operator<<(ostream& out, Time& a)
{
	if (a.h < 10)
		out << 0;
	out << a.h;
	out << ':';
	if (a.m < 10)
		out << 0;
	out << a.m;
	out << ':';
	if (a.s < 10)
		out << 0;
	out << a.s;
	return out;
}
Time Time::operator +(long long a)
{
	Time c;
	c.h = h;
	c.m = m;
	c.s = s;
	c.s += a;
	if (a >= 0)
	{
		while (c.s >= 60)
		{
			c.s -= 60;
			if (c.m == 59)
			{
				if (c.h == 23)
				{
					c.h = 0;
				}
				else
				{
					c.h++;
				}
				c.m = 0;
			}
			else
			{
				c.m++;
			}
		}
	}
	else
	{
		while (c.s <= 0)
		{
			c.s += 60;
			if (c.m == 0)
			{
				if (c.h == 0)
				{
					c.h = 23;
				}
				else
				{
					c.h--;
				}
				c.m = 59;
			}
			else
			{
				c.m--;
			}
		}
	}
	return c;
}
Time Time::operator -(long long a)
{
	Time c;
	c.h = h;
	c.m = m;
	c.s = s;
	c.s -= a;
	if (a >= 0)
	{
		while (c.s <= 0)
		{
			c.s += 60;
			if (c.m == 0)
			{
				if (c.h == 0)
				{
					c.h = 23;
				}
				else
				{
					c.h--;
				}
				c.m = 59;
			}
			else
			{
				c.m--;
			}
		}
	}
	else
	{
		while (c.s >= 60)
		{
			c.s -= 60;
			if (c.m == 59)
			{
				if (c.h == 23)
				{
					c.h = 0;
				}
				else
				{
					c.h++;
				}
				c.m = 0;
			}
			else
			{
				c.m++;
			}
		}
	}
	return c;
};
Time Time::operator =(Time a)
{
	h = a.h;
	m = a.m;
	s = a.s;
	return a;
}
Time& Time::operator++()
{
	s++;
	if (s == 60)
	{
		if (m == 59)
		{
			if (h == 23)
			{
				h = 0;
			}
			else
			{
				h++;
			}
			m = 0;
		}
		else
		{
			m++;
		}
		s = 0;
	}
	return *this;
}
Time& Time::operator--()
{
	s--;
	if (s == -1)
	{
		if (m == 0)
		{
			if (h == 0)
			{
				h = 23;
			}
			else
			{
				h--;
			}
			m = 59;
		}
		else
		{
			m--;
		}
		s = 59;
	}
	return *this;
}
Time Time::operator++(int)
{
	Time c1(*this);
	s++;
	if (s == 60)
	{
		if (m == 59)
		{
			if (h == 23)
			{
				h = 0;
			}
			else
			{
				h++;
			}
			m = 0;
		}
		else
		{
			m++;
		}
		s = 0;
	}
	return c1;
}
Time Time::operator--(int)
{
	Time c1(*this);
	s--;
	if (s == -1)
	{
		if (m == 0)
		{
			if (h == 0)
			{
				h = 23;
			}
			else
			{
				h--;
			}
			m = 59;
		}
		else
		{
			m--;
		}
		s = 59;
	}
	return c1;
}
bool Time::operator>(Time a)
{
	if (h >= a.h)
	{
		if (h > a.h)
			return 1;
		else if (m >= a.m)
		{
			if (m > a.m)
				return 1;
			else
				return (s > a.s);
		}
		else
			return 0;
	}
	else
		return 1;
}
bool Time::operator<(Time a)
{
	if (h >= a.h)
	{
		if (h > a.h)
			return 0;
		else if (m >= a.m)
		{
			if (m > a.m)
				return 0;
			else
				return (s < a.s);
		}
		else
			return 1;
	}
	else
		return 0;
}
bool Time::operator>=(Time a)
{
	if (h >= a.h)
	{
		if (h > a.h)
			return 1;
		else if (m >= a.m)
		{
			if (m > a.m)
				return 1;
			else
				return (s >= a.s);
		}
		else
			return 0;
	}
	else
		return 1;
}
bool Time::operator<=(Time a)
{
	if (h >= a.h)
	{
		if (h > a.h)
			return 0;
		else if (m >= a.m)
		{
			if (m > a.m)
				return 0;
			else
				return (s <= a.s);
		}
		else
			return 1;
	}
	else
		return 0;
}
bool Time::operator==(Time a)
{
	if (h == a.h && m == a.m && s == a.s)
		return 1;
	else
		return 0;
}
bool Time::operator!=(Time a)
{
	if (h == a.h && m == a.m && s == a.s)
		return 0;
	else
		return 1;
}
class DateTime :public Date, public Time
{
public:
	DateTime() :Date(1900, 1, 1), Time(0, 0, 0)
	{

	}
	DateTime(int h1, int m1, int s1) :Date(1900, 1, 1), Time(h1, m1, s1)
	{

	}
	DateTime(int year1, int month1, int day1, int h1, int m1, int s1) :Date(year1, month1, day1), Time(h1, m1, s1)
	{

	}
	DateTime(int s1) :Date(1900, 1, 1), Time(s1)
	{

	}
	void set(int year1, int month1, int day1, int h1, int m1, int s1)
	{
		Date::set(year1, month1, day1);
		Time::set(h1, m1, s1);
	}
	void set(int year1, int month1, int day1)
	{
		Date::set(year1, month1, day1);
	}
	void set(long long s1)
	{
		Date temp1;
		Time temp2;
		temp2 = Time(0, 0, 0) + s1;
		temp1 = Date(1900, 1, 1) + int(s1 / 86400);
		year = temp1.showyear();
		month = temp1.showmonth();
		day = temp1.showday();
		h = temp2.showhour();
		m = temp2.showminute();
		s = temp2.showsecond();

	}
	friend istream& operator >>(istream& in, DateTime& a);
	friend ostream& operator <<(ostream& out, DateTime& a);
	DateTime operator +(long long a);
	DateTime operator -(long long a);
	DateTime operator =(DateTime a);
	DateTime operator =(int a);
	DateTime& operator++();//前缀++
	DateTime& operator--();//前缀--
	DateTime operator++(int);//后缀++
	DateTime operator--(int);//后缀--
	bool operator>(DateTime a);
	bool operator>=(DateTime a);
	bool operator==(DateTime a);
	bool operator<(DateTime a);
	bool operator<=(DateTime a);
	bool operator!=(DateTime a);
};
istream& operator>>(istream& in, DateTime& a)
{
	in >> a.year >> a.month >> a.day >> a.h >> a.m >> a.s;
	return in;
}
ostream& operator<<(ostream& out, DateTime& a)
{
	out << a.year << "年" << a.month << "月" << a.day << "日 ";
	if (a.h < 10)
		out << 0;
	out << a.h;
	out << ':';
	if (a.m < 10)
		out << 0;
	out << a.m;
	out << ':';
	if (a.s < 10)
		out << 0;
	out << a.s;
	return out;
}
DateTime DateTime::operator +(long long a)
{
	DateTime c;
	c.year = year;
	c.month = month;
	c.day = day;
	c.h = h;
	c.m = m;
	c.s = s;
	c.s += a;
	int count1 = 0;
	if (a >= 0)
	{
		while (c.s >= 60)
		{
			c.s -= 60;
			if (c.m == 59)
			{
				if (c.h == 23)
				{
					c.h = 0;
					count1++;
				}
				else
				{
					c.h++;
				}
				c.m = 0;
			}
			else
			{
				c.m++;
			}
		}
	}
	else
	{
		while (c.s <= 0)
		{
			c.s += 60;
			if (c.m == 0)
			{
				if (c.h == 0)
				{
					c.h = 23;
					count1--;
				}
				else
				{
					c.h--;
				}
				c.m = 59;
			}
			else
			{
				c.m--;
			}
		}
	}
	c.day += count1;
	if (count1 >= 0)
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
DateTime DateTime::operator -(long long a)
{
	DateTime c;
	c.year = year;
	c.month = month;
	c.day = day;
	c.h = h;
	c.m = m;
	c.s = s;
	c.s -= a;
	int count1 = 0;
	if (a >= 0)
	{
		while (c.s < 0)
		{
			c.s += 60;
			if (c.m == 0)
			{
				if (c.h == 0)
				{
					c.h = 23;
					count1--;
				}
				else
				{
					c.h--;
				}
				c.m = 59;
			}
			else
			{
				c.m--;
			}
		}
	}
	else
	{
		while (c.s >= 60)
		{
			c.s -= 60;
			if (c.m == 59)
			{
				if (c.h == 23)
				{
					c.h = 0;
					count1--;
				}
				else
				{
					c.h++;
				}
				c.m = 0;
			}
			else
			{
				c.m++;
			}
		}
	}
	c.day += count1;
	if (count1 >= 0)
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
DateTime DateTime::operator =(DateTime a)
{
	year = a.year;
	month = a.month;
	day = a.day;
	h = a.h;
	m = a.m;
	s = a.s;
	return a;
}
DateTime& DateTime::operator++()
{
	s++;
	if (s == 60)
	{
		if (m == 59)
		{
			if (h == 23)
			{
				h = 0;
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
			}
			else
			{
				h++;
			}
			m = 0;
		}
		else
		{
			m++;
		}
		s = 0;
	}
	return *this;
}
DateTime& DateTime::operator--()
{
	s--;
	if (s == -1)
	{
		if (m == 0)
		{
			if (h == 0)
			{
				h = 23;
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
			}
			else
			{
				h--;
			}
			m = 59;
		}
		else
		{
			m--;
		}
		s = 59;
	}
	return *this;
}
DateTime DateTime::operator++(int)
{
	DateTime c1(*this);
	s++;
	if (s == 60)
	{
		if (m == 59)
		{
			if (h == 23)
			{
				h = 0;
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
			}
			else
			{
				h++;
			}
			m = 0;
		}
		else
		{
			m++;
		}
		s = 0;
	}
	return c1;
}
DateTime DateTime::operator--(int)
{
	DateTime c1(*this);
	s--;
	if (s == -1)
	{
		if (m == 0)
		{
			if (h == 0)
			{
				h = 23;
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
			}
			else
			{
				h--;
			}
			m = 59;
		}
		else
		{
			m--;
		}
		s = 59;
	}
	return c1;
}
bool DateTime::operator>(DateTime a)
{
	if (year > a.year)
	{
		return 1;
	}
	else if (year < a.year)
	{
		return 0;
	}
	else
	{
		if (month > a.month)
		{
			return 1;
		}
		else if (month < a.month)
		{
			return 0;
		}
		else
		{
			if (day > a.day)
				return 1;
			else if (day < a.day)
			{
				return 0;
			}
			else
			{
				if (h >= a.h)
				{
					if (h > a.h)
						return 1;
					else if (m >= a.m)
					{
						if (m > a.m)
							return 1;
						else
							return (s > a.s);
					}
					else
						return 0;
				}
				else
					return 1;
			}
		}
	}
}
bool DateTime::operator<(DateTime a)
{
	if (year > a.year)
	{
		return 0;
	}
	else if (year < a.year)
	{
		return 1;
	}
	else
	{
		if (month > a.month)
		{
			return 0;
		}
		else if (month < a.month)
		{
			return 1;
		}
		else
		{
			if (day > a.day)
				return 0;
			else if (day < a.day)
			{
				return 1;
			}
			else
			{
				if (h >= a.h)
				{
					if (h > a.h)
						return 0;
					else if (m >= a.m)
					{
						if (m > a.m)
							return 0;
						else
							return (s < a.s);
					}
					else
						return 1;
				}
				else
					return 0;
			}
		}
	}
}
bool DateTime::operator>=(DateTime a)
{
	if (year > a.year)
	{
		return 1;
	}
	else if (year < a.year)
	{
		return 0;
	}
	else
	{
		if (month > a.month)
		{
			return 1;
		}
		else if (month < a.month)
		{
			return 0;
		}
		else
		{
			if (day > a.day)
				return 1;
			else if (day < a.day)
			{
				return 0;
			}
			else
			{
				if (h >= a.h)
				{
					if (h > a.h)
						return 1;
					else if (m >= a.m)
					{
						if (m > a.m)
							return 1;
						else
							return (s >= a.s);
					}
					else
						return 0;
				}
				else
					return 1;
			}
		}
	}
}
bool DateTime::operator<=(DateTime a)
{
	if (year > a.year)
	{
		return 0;
	}
	else if (year < a.year)
	{
		return 1;
	}
	else
	{
		if (month > a.month)
		{
			return 0;
		}
		else if (month < a.month)
		{
			return 1;
		}
		else
		{
			if (day > a.day)
				return 0;
			else if (day < a.day)
			{
				return 1;
			}
			else
			{
				if (h >= a.h)
				{
					if (h > a.h)
						return 0;
					else if (m >= a.m)
					{
						if (m > a.m)
							return 0;
						else
							return (s <= a.s);
					}
					else
						return 1;
				}
				else
					return 0;
			}
		}
	}
}
bool DateTime::operator==(DateTime a)
{
	if (year == a.year && month == a.month && day == a.day && h == a.h && m == a.m && s == a.s)
		return 1;
	else
		return 0;
}
bool DateTime::operator!=(DateTime a)
{
	if (year == a.year && month == a.month && day == a.day && h == a.h && m == a.m && s == a.s)
		return 0;
	else
		return 1;
}
int main()
{
	cout << "测试Date类" << endl;
	{
		Date d1;

		Date d2(1907, 5, 20);

		cout << "测试初始化和cout重载" << endl;

		cout << "d1应该是今天， 实际为：" << d1 << endl;
		cout << "d2应该是1907年5月20日，实际为：" << d2 << endl;

//		wait_for_press();
	}

	{
		Date d1, d2, d3, d4;

		cout << "测试set和cin重载" << endl;
		d1.set(1907, 5, 20);
		d2.set(1907, 5);
		d3.set(1907);

		cout << "d1应该是1907年5月20日，实际为：" << d1 << endl;
		cout << "d2应该是1907年5月1日， 实际为：" << d2 << endl;
		cout << "d3应该是1907年1月1日， 实际为：" << d3 << endl;

		cout << "请输入某日期" << endl;
		cin >> d4;
		d4.set(0, 0, 0);
		cout << "d4应该是您刚输入的日期，实际为：" << d4 << endl;

//		wait_for_press();
	}

	{
		Date d1(10);
		Date d2(250);
		Date d3(1314);
		Date d4(13145);

		cout << "测试转换构造函数" << endl;

		cout << "d1应该是1900年1月10日，  实际为：" << d1 << endl;
		cout << "d2应该是1900年9月7日，实际为：" << d2 << endl;
		cout << "d3应该是1903年8月7日，  实际为：" << d3 << endl;
		cout << "d4应该是1935年12月28日，实际为：" << d4 << endl;

		Date d5, d6;
		d5 = 30041;
		cout << "d5应该是1982年4月1日， 实际为：" << d5 << endl;

		d6 = 42301;
		cout << "d6应该是2015年10月25日， 实际为：" << d6 << endl;

//		wait_for_press();
	}

	{
		Date d1(1900, 1, 1);
		Date d2(1907, 5, 20);
		Date d3(1982, 4, 1);
		Date d4(2015, 10, 25);

		cout << "测试类型转换函数" << endl;

		cout << "d1应该是1，     实际为：" << int(d1) << endl;
		cout << "d2应该是2696， 实际为：" << int(d2) << endl;
		cout << "d3应该是30041， 实际为：" << int(d3) << endl;
		cout << "d4应该是42301， 实际为：" << int(d4) << endl;

//		wait_for_press();
	}

	{
		Date d1(1907, 5, 20);
		Date d2;

		cout << "测试重载+/-" << endl;

		d2 = d1 + 520;
		cout << "d2应该是1908年10月21日，    实际为：" << d2 << endl;

		d2 = 520 + d1;
		cout << "d2应该是1908年10月21日，    实际为：" << d2 << endl;

		d2 = d1 - 3;
		cout << "d2应该是1907年5月17日，   实际为：" << d2 << endl;

		d1.set(2016, 5, 20);
		d2.set(2015, 5, 20);
		cout << "d1-d2应该是366，实际为：" << d1 - d2 << endl;

		d1.set(2018, 5, 20);
		d2.set(2017, 5, 20);
		cout << "d1-d2应该是365，实际为：" << d1 - d2 << endl;

//		wait_for_press();
	}

	{
		Date d1, d2;

		cout << "测试重载++/--" << endl;

		d1.set(1907, 5, 20);
		d2 = d1++;
		cout << "d1应该是1907年5月21日，  实际为：" << d1 << endl;
		cout << "d2应该是1907年5月20日，  实际为：" << d2 << endl;

		d1.set(1907, 5, 20);
		d2 = ++d1;
		cout << "d1应该是1907年5月21日，  实际为：" << d1 << endl;
		cout << "d2应该是1907年5月21日，  实际为：" << d2 << endl;

		d1.set(1907, 1, 1);
		d2 = d1--;
		cout << "d1应该是1906年12月31日， 实际为：" << d1 << endl;
		cout << "d2应该是1907年1月1日，  实际为：" << d2 << endl;

		d1.set(1907, 1, 1);
		d2 = --d1;
		cout << "d1应该是1906年12月31日， 实际为：" << d1 << endl;
		cout << "d2应该是1906年12月31日， 实际为：" << d2 << endl;

		d1.set(2016, 2, 28);
		d2 = d1++;
		cout << "d1应该是2016年2月29日， 实际为：" << d1 << endl;
		cout << "d2应该是2016年2月28日， 实际为：" << d2 << endl;

		d1.set(2018, 3, 1);
		d2 = d1--;
		cout << "d1应该是2018年2月28日， 实际为：" << d1 << endl;
		cout << "d2应该是2018年3月1日，  实际为：" << d2 << endl;

//		wait_for_press();
	}


	{
		Date d1(1907, 5, 20);
		Date d2(1907, 5, 20);
		Date d3(1907, 1, 1);

		cout << "测试比较运算符" << endl;

		cout << "比较结果应为1，实际为：" << (d1 > d3) << endl;
		cout << "比较结果应为1，实际为：" << (d2 >= d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 < d3) << endl;
		cout << "比较结果应为0，实际为：" << (d2 <= d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 == d2) << endl;
		cout << "比较结果应为0，实际为：" << (d1 != d1) << endl;

//		wait_for_press();
	}

	cout << "测试Time类" << endl;
	{
		Time t1;

		Time t2(1, 2, 3);

		Time t3(123);

		cout << "测试初始化和cout重载" << endl;

		cout << "t1应该是00:00:00， 实际为：" << t1 << endl;
		cout << "t2应该是01:02:03，实际为：" << t2 << endl;
		cout << "t2应该是00:02:03，实际为：" << t3 << endl;

//		wait_for_press();
	}

	{
		Time t1, t2, t3, t4;

		cout << "测试set和cin重载" << endl;
		t1.set(20, 14, 13);
		t2.set(-1, 13, 14);
		t3.set(84813);

		cout << "t1应该是20:14:13，实际为：" << t1 << endl;
		cout << "t2应该是00:13:14， 实际为：" << t2 << endl;
		cout << "t3应该是23:33:33， 实际为：" << t3 << endl;

		cout << "请输入某时间" << endl;
		cin >> t4;
		cout << "d4应该是您刚输入的日期，实际为：" << t4 << endl;

//		wait_for_press();
	}


	{
		Time t1(12, 0, 0);
		Time t2;

		cout << "测试重载+/-/=" << endl;

		t2 = t1 + 520;
		cout << "t2应该是12:08:40，   实际为：" << t2 << endl;

		t2 = t1 - 3;
		cout << "t2应该是11:59:57，   实际为：" << t2 << endl;

		t2 = t1;
		cout << "t2应该是12:00:00，   实际为：" << t2 << endl;

//		wait_for_press();
	}

	{
		Time t1, t2;

		cout << "测试重载++/--" << endl;

		t1.set(12, 0, 0);
		t2 = t1++;
		cout << "t1应该是12:00:01，  实际为：" << t1 << endl;
		cout << "t2应该是12:00:00，  实际为：" << t2 << endl;

		t1.set(12, 0, 0);
		t2 = ++t1;
		cout << "t1应该是12:00:01，  实际为：" << t1 << endl;
		cout << "t2应该是12:00:01，  实际为：" << t2 << endl;

		t1.set(12, 0, 0);
		t2 = t1--;
		cout << "t1应该是11:59:59，  实际为：" << t1 << endl;
		cout << "t2应该是12:00:00，  实际为：" << t2 << endl;

		t1.set(12, 0, 0);
		t2 = --t1;
		cout << "t1应该是11:59:59，  实际为：" << t1 << endl;
		cout << "t2应该是11:59:59，  实际为：" << t2 << endl;

//		wait_for_press();
	}


	{
		Time t1(15, 14, 34);
		Time t2(15, 14, 34);
		Time t3(0, 1, 21);


		cout << "测试比较运算符" << endl;

		cout << "比较结果应为1，实际为：" << (t1 > t3) << endl;
		cout << "比较结果应为1，实际为：" << (t2 >= t3) << endl;
		cout << "比较结果应为0，实际为：" << (t1 < t3) << endl;
		cout << "比较结果应为0，实际为：" << (t2 <= t3) << endl;
		cout << "比较结果应为1，实际为：" << (t1 == t2) << endl;
		cout << "比较结果应为0，实际为：" << (t1 != t1) << endl;

//		wait_for_press();
	}

	cout << "测试DateTime类" << endl;
	{

		DateTime t1;                           // 1900年1月1日 00:00:00
		DateTime t2(1, 2, 3);                  // 1900年1月1日 01:02:03
		DateTime t3(1980, 12, 31, 12, 23, 34); // 1980年12月31日  12:23:34
		DateTime t4(123);                      // 1900年1月1日 00:02:03

		cout << "测试初始化和cout重载" << endl;

		cout << "t1应该是1900年1月1日    00:00:00， 实际为：" << t1 << endl;
		cout << "t2应该是1900年1月1日    01:02:03， 实际为：" << t2 << endl;
		cout << "t3应该是1980年12月31日  12:23:34， 实际为：" << t3 << endl;
		cout << "t4应该是1900年1月1日    00:02:03， 实际为：" << t4 << endl;

//		wait_for_press();
	}

	{
		DateTime t1;

		cout << "测试set和cin重载" << endl;
		t1.set(1980, 12, 31, 20, 14, 13);
		cout << "t1应该是1980年12月31日 20:14:13，实际为：" << t1 << endl;
		t1.set(2000, 2, 29);
		cout << "t1应该是2000年2月29日 20:14:13， 实际为：" << t1 << endl;
		t1.set(-1, -1, -1, -1, 13, 14);
		cout << "t1应该是2000年2月29日 20:13:14， 实际为：" << t1 << endl;
		t1.set(3768726214);
		cout << "t1应该是2019年6月5日 12:23:34， 实际为：" << t1 << endl;

		cout << "请输入某日期与时间" << endl;
		cin >> t1;
		cout << "t1应该是您刚输入的日期，实际为：" << t1 << endl;

//		wait_for_press();
	}



	{
		DateTime t1(1, 2, 3);
		DateTime t2;

		cout << "测试重载+/-/=" << endl;

		t2 = t1 + (long long)(520);
		cout << "t2应该是1900年1月1日 01:10:43，   实际为：" << t2 << endl;

		t2 = t1 - (long long)(3);
		cout << "t2应该是1900年1月1日 01:02:00，   实际为：" << t2 << endl;

		t2 = t1;
		cout << "t2应该是1900年1月1日 01:02:03，   实际为：" << t2 << endl;

//		wait_for_press();
	}

	{
		DateTime t1(1, 2, 3);
		DateTime t2;

		cout << "测试重载++/--" << endl;

		t2 = t1++;
		cout << "t1应该是1900年1月1日 01:02:04，  实际为：" << t1 << endl;
		cout << "t2应该是1900年1月1日 01:02:03，  实际为：" << t2 << endl;

		t1.set(1980, 12, 31, 20, 14, 13);
		t2 = ++t1;
		cout << "t1应该是1980年12月31日 20:14:14，实际为：" << t1 << endl;
		cout << "t2应该是1980年12月31日 20:14:14，实际为：" << t2 << endl;

		t1.set(1980, 12, 31, 20, 14, 13);
		t2 = t1--;
		cout << "t1应该是1980年12月31日 20:14:12，实际为：" << t1 << endl;
		cout << "t2应该是1980年12月31日 20:14:13，实际为：" << t2 << endl;

		t1.set(1980, 12, 31, 20, 14, 13);
		t2 = --t1;
		cout << "t1应该是1980年12月31日 20:14:12，实际为：" << t1 << endl;
		cout << "t2应该是1980年12月31日 20:14:12，实际为：" << t2 << endl;


//		wait_for_press();
	}


	{
		DateTime d1(1980, 12, 31, 12, 23, 34);
		DateTime d2(1980, 12, 31, 12, 23, 34);
		DateTime d3(1980, 1, 1, 12, 23, 34);

		cout << "测试比较运算符" << endl;

		cout << "比较结果应为1，实际为：" << (d1 > d3) << endl;
		cout << "比较结果应为1，实际为：" << (d2 >= d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 < d3) << endl;
		cout << "比较结果应为0，实际为：" << (d2 <= d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 == d2) << endl;
		cout << "比较结果应为0，实际为：" << (d1 != d1) << endl;

//		wait_for_press();
	}
	return 0;
}