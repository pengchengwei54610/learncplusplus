#include <iostream>

using namespace std;

class Date
{
public:
	Date(int = 1, int = 1, int = 2005);

	//错误1：与带默认参数的三参构造函数冲突，引起二义性
	/*Date(int, int);
	Date(int);
	Date();*/

	void display();

private:
	int month;
	int day;
	int year;
};

Date::Date(int m, int d, int y) : month(m), day(d), year(y) {}

//错误2：与带默认参数的三参构造函数冲突，引起二义性
//Date::Date(int m, int d) : month(m), day(d)
//{
//	year = 2005;
//}
//
//Date::Date(int m) : month(m)
//{
//	day = 1;
//	year = 2005;
//}
//
//Date::Date()
//{
//	month = 1;
//	day = 1;
//	year = 2005;
//}

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