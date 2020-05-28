#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<cstring>
using namespace std;
#define name_max_length 30
// on P372
class Teacher
{
private:
	int num;
	char* name;
	char sex;
public:
	Teacher(int num1, char* name1, char sex1);
	~Teacher();
	void set_init_info();
	void show_teacher_info();
};
Teacher::Teacher(int num1 = 0, char* name1 = NULL, char sex1 = 'm')
{
	num = num1;
	name = new(nothrow)char[name_max_length];
	if (name == NULL)
	{
		cerr << "�ڴ�����ʧ��" << endl;
		exit(0);
	}
	if (name1 != NULL)
	{
		strcpy(name, name1);
	}
	sex = sex1;
}
Teacher::~Teacher()
{
	delete name;
}
void Teacher::set_init_info()
{
	num = 10000;
	strcpy(name, "����");
	sex = 'm';
}
void Teacher::show_teacher_info()
{
	cout << " ����: " << name << endl;
	cout << " �̹���: " << num << endl;
	cout << " �Ա�: " << sex << endl;
}
class BirthDate
{
private:
	int year;
	int month;
	int day;
public:
	BirthDate(int year1, int month1, int day1);
	void set_birthday();
	void show_birthday();
};
BirthDate::BirthDate(int year1 = 0, int month1 = 0, int day1 = 0)
{
	year = year1;
	month = month1;
	day = day1;
}
void BirthDate::set_birthday()
{
	cout << "����ı�����ڣ�" << endl;
	cin >> year >> month >> day;
}
void BirthDate::show_birthday()
{
	cout << " ����: " << year << '-' << month << '-' << day << endl;
}
class Professor : public Teacher
{
private:
public:
	BirthDate birthday;
	void display();
};
void Professor::display()
{
	show_teacher_info();
	birthday.show_birthday();
}
void fun1(Teacher& t1)
{
	t1.set_init_info();
}
void fun2(BirthDate& b1)
{
	b1.set_birthday();
}
int main()
{
	Professor prof1;
	fun1(prof1);
	fun2(prof1.birthday);
	prof1.display();
	return 0;
}