#include<iostream>
using namespace std;
struct date {
	int year;
	int month;
	int day;
};
bool leap_judge(date date1)
{
	if (date1.year % 100 == 0)
		if (date1.year % 400 == 0)
			return 1;
		else
			return 0;
	else if (date1.year % 4 == 0)
		return 1;
	else
		return 0;
}
bool rightful_judge(date date1)
{
	bool if_leap;
	if_leap = leap_judge(date1);
	if (date1.month == 1)
		if (date1.day >= 1 && date1.day <= 31)
			return 1;
		else
			return 0;
	else if (date1.month == 2)
		if (date1.day >= 1 && date1.day <= 28 + if_leap)
			return 1;
		else
			return 0;
	else if (date1.month == 3)
		if (date1.day >= 1 && date1.day <= 31)
			return 1;
		else
			return 0;
	else if (date1.month == 4)
		if (date1.day >= 1 && date1.day <= 30)
			return 1;
		else
			return 0;
	else if (date1.month == 5)
		if (date1.day >= 1 && date1.day <= 31)
			return 1;
		else
			return 0;
	else if (date1.month == 6)
		if (date1.day >= 1 && date1.day <= 30)
			return 1;
		else
			return 0;
	else if (date1.month == 7)
		if (date1.day >= 1 && date1.day <= 31)
			return 1;
		else
			return 0;
	else if (date1.month == 8)
		if (date1.day >= 1 && date1.day <= 31)
			return 1;
		else
			return 0;
	else if (date1.month == 9)
		if (date1.day >= 1 && date1.day <= 30)
			return 1;
		else
			return 0;
	else if (date1.month == 10)
		if (date1.day >= 1 && date1.day <= 31)
			return 1;
		else
			return 0;
	else if (date1.month == 11)
		if (date1.day >= 1 && date1.day <= 30)
			return 1;
		else
			return 0;
	else if (date1.month == 12)
		if (date1.day >= 1 && date1.day <= 31)
			return 1;
		else
			return 0;
	else
		return 0;
}
int days1(date date1)
{
	bool if_rightful;
	if_rightful = rightful_judge(date1);
	if (if_rightful == 0)
		return 0;
	bool if_leap;
	if_leap = leap_judge(date1);
	if (date1.month == 1)
		return date1.day;
	else if (date1.month == 2)
		return (31 + date1.day);
	else if (date1.month == 3)
		return (59 + if_leap + date1.day);
	else if (date1.month == 4)
		return (90 + if_leap + date1.day);
	else if (date1.month == 5)
		return (120 + if_leap + date1.day);
	else if (date1.month == 6)
		return (151 + if_leap + date1.day);
	else if (date1.month == 7)
		return (181 + if_leap + date1.day);
	else if (date1.month == 8)
		return (212 + if_leap + date1.day);
	else if (date1.month == 9)
		return (243 + if_leap + date1.day);
	else if (date1.month == 10)
		return (273 + if_leap + date1.day);
	else if (date1.month == 11)
		return (304 + if_leap + date1.day);
	else if (date1.month == 12)
		return (334 + if_leap + date1.day);
	else
		return 0;
}
int days2(date* date1)
{
	bool if_rightful;
	if_rightful = rightful_judge(*date1);
	if (if_rightful == 0)
		return 0;
	bool if_leap;
	if_leap = leap_judge(*date1);
	if (date1->month == 1)
		return date1->day;
	else if (date1->month == 2)
		return (31 + date1->day);
	else if (date1->month == 3)
		return (59 + if_leap + date1->day);
	else if (date1->month == 4)
		return (90 + if_leap + date1->day);
	else if (date1->month == 5)
		return (120 + if_leap + date1->day);
	else if (date1->month == 6)
		return (151 + if_leap + date1->day);
	else if (date1->month == 7)
		return (181 + if_leap + date1->day);
	else if (date1->month == 8)
		return (212 + if_leap + date1->day);
	else if (date1->month == 9)
		return (243 + if_leap + date1->day);
	else if (date1->month == 10)
		return (273 + if_leap + date1->day);
	else if (date1->month == 11)
		return (304 + if_leap + date1->day);
	else if (date1->month == 12)
		return (334 + if_leap + date1->day);
	else
		return 0;
}
int days3(date& date1)
{
	bool if_rightful;
	if_rightful = rightful_judge(date1);
	if (if_rightful == 0)
		return 0;
	bool if_leap;
	if_leap = leap_judge(date1);
	if (date1.month == 1)
		return date1.day;
	else if (date1.month == 2)
		return (31 + date1.day);
	else if (date1.month == 3)
		return (59 + if_leap + date1.day);
	else if (date1.month == 4)
		return (90 + if_leap + date1.day);
	else if (date1.month == 5)
		return (120 + if_leap + date1.day);
	else if (date1.month == 6)
		return (151 + if_leap + date1.day);
	else if (date1.month == 7)
		return (181 + if_leap + date1.day);
	else if (date1.month == 8)
		return (212 + if_leap + date1.day);
	else if (date1.month == 9)
		return (243 + if_leap + date1.day);
	else if (date1.month == 10)
		return (273 + if_leap + date1.day);
	else if (date1.month == 11)
		return (304 + if_leap + date1.day);
	else if (date1.month == 12)
		return (334 + if_leap + date1.day);
	else
		return 0;
}
int main()
{
	date date1;
	char trans_type;
	int result = 0;
	cout << "请输入一个日期:" << endl;
	cin >> date1.year >> date1.month >> date1.day;
	cout << "请输入参数方式" << endl;
	cin >> trans_type;
	if (trans_type == 'a')
	{
		result = days1(date1);
	}
	else if (trans_type == 'b')
	{
		result = days2(&date1);
	}
	else if (trans_type == 'c')
	{
		result = days3(date1);
	}
	if (result == 0)
	{
		cout << "illegal" << endl;
	}
	else
		cout << date1.year << "年" << date1.month << "月" << date1.day << "日是" << date1.year << "的第" << result << "天" << endl;

	return 0;
}
