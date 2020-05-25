#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

/**********************************************
*
*    TO-DO:
*        �벹ȫ������Ĵ��룬��ֻ�ύ���������Ĵ��롣
*
***********************************************/
#include<cstring>
class Teacher;
class Student {
private:
	int id;
	int age;
	int gender;
	char name[16];
public:
	void show_info()
	{
		cout << "ѧ��ѧ�ţ�" << id << " ѧ�����䣺" << age << " ѧ���Ա�" << (gender ? "��" : "Ů") << " ѧ��������" << name << endl;
	}
	Student(int id1, int age1, int gender1, char name1[16])
	{
		id = id1;
		age = age1;
		gender = gender1;
		strcpy(name, name1);
	}
	friend Teacher;
};

class Teacher {
private:
	int id;
	int age;
	int gender;
	char name[16];
public:
	void show_info()
	{
		cout << "��ʦ�ţ�" << id << " ��ʦ���䣺" << age << " ��ʦ�Ա�" << (gender ? "��" : "Ů") << " ��ʦ������" << name << endl;
	}
	Teacher()
	{
		id = 0;
		age = 0;
		gender = 0;
		name[0] = 0;
	}
	Teacher(Student temp)
	{
		id = temp.id;
		age = temp.age;
		gender = temp.gender;
		strcpy(name, temp.name);
	}
};



/**********************************************
*
*    TO-DO END
*
***********************************************/

int main() {
	int id, age, gender;
	char name[16];

	cin >> id >> age >> gender >> name;
	Student stu(id, age, gender, name);
	stu.show_info();

	Teacher teac;
	teac = (Teacher)stu;
	teac.show_info();
	return 0;
}