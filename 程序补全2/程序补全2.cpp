#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;
#define name_max_length 30
#define address_max_length 30
// on P337
class Student
{
protected:
	int num;
	char* name;
	char sex;
public:
	void get_value()
	{
		cout << "请输入学生学号、姓名和性别" << endl;
		cin >> num >> name >> sex;
	}

	void display()
	{
		cout << " 姓名: " << name << endl;
		cout << " 学号: " << num << endl;
		cout << " 性别: " << sex << endl;
	}
	Student(int num1 = 0, char* name1 = NULL, char sex1 = 'f')
	{
		num = num1;
		name = new(nothrow)char[name_max_length];
		if (name == 0)
		{
			cerr << "内存申请失败" << endl;
			exit(0);
		}
		if (name1 != NULL)
		{
			strcpy(name1, name);
		}
		sex = sex1;
	}
	~Student()
	{
		delete name;
	}
};

// on P338
class Student1 : private Student
{
private:
	int age;
	char* addr;
public:
	void get_value_1()
	{
		get_value();
		cout << "请输入学生的年龄和地址" << endl;
		cin >> age >> addr;
	}

	void display_1()
	{
		display();
		cout << " 年龄: " << age << endl;
		cout << " 地址: " << addr << endl;
	}
	Student1(int age1 = 0, char* address = NULL)
	{
		age = age1;
		addr = new(nothrow)char[address_max_length];
		if (addr == NULL)
		{
			cerr << "内存申请失败" << endl;
			exit(0);
		}
		if (address != NULL)
		{
			strcpy(addr, address);
		}
	}
	~Student1()
	{
		delete addr;
	}
};
// on P339
int main()
{
	Student1 stud;
	stud.get_value_1();
	stud.display_1();
	return 0;
}