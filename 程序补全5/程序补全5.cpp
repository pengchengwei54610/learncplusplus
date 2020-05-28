#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;
#define name_max_length 30
#define address_max_length 30
#define phone_max_length 30
#define title_max_length 30
#define post_max_length 30
class Teacher
{
protected:
	char* name;
	int age;
	char sex;
	char* addr;
	char* phone;
	char* title;
public:
	Teacher(char* name1 = NULL, int age1 = 0, char sex1 = 'f', char* addr1 = NULL, char* phone1 = NULL, char* title1 = NULL);
	~Teacher();
	void display();
};
Teacher::Teacher(char* name1, int age1, char sex1, char* addr1, char* phone1, char* title1)
{
	name = new(nothrow)char[name_max_length];
	if (name == NULL)
	{
		cerr << "�ڴ�����ʧ��";
		exit(0);
	}
	addr = new(nothrow)char[address_max_length];
	if (addr == NULL)
	{
		cerr << "�ڴ�����ʧ��";
		exit(0);
	}
	phone = new(nothrow)char[phone_max_length];
	if (phone == NULL)
	{
		cerr << "�ڴ�����ʧ��";
		exit(0);
	}
	title = new(nothrow)char[title_max_length];
	if (title == NULL)
	{
		cerr << "�ڴ�����ʧ��";
		exit(0);
	}

	if (name1 != NULL)
	{
		strcpy(name, name1);
	}
	if (addr1 != NULL)
	{
		strcpy(addr, addr1);
	}
	if (phone1 != NULL)
	{
		strcpy(phone, phone1);
	}
	if (title1 != NULL)
	{
		strcpy(title, title1);
	}
	age = age1;
	sex = sex1;
}
Teacher::~Teacher()
{
	delete name;
	delete addr;
	delete phone;
	delete title;

}
void Teacher::display()
{
	cout << " ����: " << name << endl;
	cout << " ����: " << age << endl;
	cout << " �Ա�: " << sex << endl;
	cout << " ��ַ: " << addr << endl;
	cout << " �绰: " << phone << endl;
	cout << " ְ��: " << title << endl;
}
class Cadre
{
protected:
	char* name;
	int age;
	char sex;
	char* addr;
	char* phone;
	char* post;
public:
	Cadre(char* name1 = NULL, int age1 = 0, char sex1 = 'f', char* addr1 = NULL, char* phone1 = NULL, char* post1 = NULL);
	~Cadre();
	void display();
};
Cadre::Cadre(char* name1, int age1, char sex1, char* addr1, char* phone1, char* post1)
{
	name = new(nothrow)char[name_max_length];
	if (name == NULL)
	{
		cerr << "�ڴ�����ʧ��";
		exit(0);
	}
	addr = new(nothrow)char[address_max_length];
	if (addr == NULL)
	{
		cerr << "�ڴ�����ʧ��";
		exit(0);
	}
	phone = new(nothrow)char[phone_max_length];
	if (phone == NULL)
	{
		cerr << "�ڴ�����ʧ��";
		exit(0);
	}
	post = new(nothrow)char[post_max_length];
	if (post == NULL)
	{
		cerr << "�ڴ�����ʧ��";
		exit(0);
	}

	if (name1 != NULL)
	{
		strcpy(name, name1);
	}
	if (addr1 != NULL)
	{
		strcpy(addr, addr1);
	}
	if (phone1 != NULL)
	{
		strcpy(phone, phone1);
	}
	if (post1 != NULL)
	{
		strcpy(post, post1);
	}
	age = age1;
	sex = sex1;
}
Cadre::~Cadre()
{
	delete name;
	delete addr;
	delete phone;
	delete post;

}
void Cadre::display()
{
	cout << " ����: " << name << endl;
	cout << " ����: " << age << endl;
	cout << " �Ա�: " << sex << endl;
	cout << " ��ַ: " << addr << endl;
	cout << " �绰: " << phone << endl;
	cout << " ְ��: " << post << endl;
}
class Teacher_Cadre :protected Teacher, protected Cadre
{
private:
	int wages;
public:
	Teacher_Cadre(char* name1, int age1, char sex1, char* addr1, char* phone1, char* title1, char* post1, int wages);
	void show();
};
Teacher_Cadre::Teacher_Cadre(char* name1 = NULL, int age1 = 0, char sex1 = 'f', char* addr1 = NULL, char* phone1 = NULL, char* title1 = NULL, char* post1 = NULL, int wages1 = 0) :Teacher(name1, age1, sex1, addr1, phone1, title1), Cadre(name1, age1, sex1, addr1, phone1, post1)
{
	wages = wages1;
};
void Teacher_Cadre::show()
{
	Teacher::display();
	cout << " ְ��: " << post << endl;
	cout << " нˮ: " << wages << endl;
}
int main()
{
	int type;
	cout << "��������Ա���ͣ�0Ϊ��ʦ��1Ϊ�ɲ���2Ϊ��ʦ��ɲ���" << endl;
	cin >> type;
	if (type == 0)
	{
		char name[name_max_length];
		int age;
		char sex;
		char addr[address_max_length];
		char phone[phone_max_length];
		char title[title_max_length];
		cout << "���������������䡢�Ա𡢵�ַ���绰��ְ��" << endl;
		cin >> name >> age >> sex >> addr >> phone >> title;
		Teacher t1(name, age, sex, addr, phone, title);
		cout << "��ʦ��Ϣ����" << endl;
		t1.display();
	}
	else if (type == 1)
	{
		char name[name_max_length];
		int age;
		char sex;
		char addr[address_max_length];
		char phone[phone_max_length];
		char post[post_max_length];
		cout << "���������������䡢�Ա𡢵�ַ���绰��ְ��" << endl;
		cin >> name >> age >> sex >> addr >> phone >> post;
		Cadre c1(name, age, sex, addr, phone, post);
		cout << "�ɲ���Ϣ����" << endl;
		c1.display();
	}
	else if (type == 2)
	{
		char name[name_max_length];
		int age;
		char sex;
		char addr[address_max_length];
		char phone[phone_max_length];
		char title[title_max_length];
		char post[post_max_length];
		int wages;
		cout << "���������������䡢�Ա𡢵�ַ���绰��ְ�ơ�ְ���нˮ" << endl;
		cin >> name >> age >> sex >> addr >> phone >> title >> post >> wages;
		Teacher_Cadre tc1(name, age, sex, addr, phone, title, post, wages);
		cout << "��ʦ��ɲ���Ϣ����" << endl;
		tc1.show();
	}
	else
		cout << "�������ʹ���" << endl;
	return 0;
}