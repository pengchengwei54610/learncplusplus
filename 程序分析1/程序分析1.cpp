#include <iostream>

using namespace std;

class Date
{
public:
	Date(int, int, int);
	Date(int, int);
	Date(int);
	Date();
	void display();

private:
	int month;
	int day;
	int year;
};

Date::Date(int m, int d, int y) : month(m), day(d), year(y) {}

Date::Date(int m, int d) : month(m), day(d)
{
	year = 2005;
}

Date::Date(int m) : month(m)
{
	day = 1;
	year = 2005;
}

Date::Date()
{
	month = 1;
	day = 1;
	year = 2005;
}

void Date::display()
{
	cout << month << "/" << day << "/" << year << endl;
}

int main()
{
	Date d1(10, 13, 2005);
	Date d2(12, 30);
	Date d3(10);
	Date d4;

	d1.display();
	d2.display();
	d3.display();
	d4.display();

	return 0;
}
/*
输出结果：
10/13/2005
12/30/2005
10/1/2005
1/1/2005

分析：
d1对象调用三参构造函数Date(int, int, int);
d2对象调用两参构造函数Date(int, int);
d3对象调用一参构造函数Date(int);
d4对象调用无参构造函数Date();
display成员函数依次输出月/日/年
*/