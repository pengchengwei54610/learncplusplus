#include <iostream>

using namespace std;

class Time
{
	//错误1：成员函数需public，否则外部无法访问
public:

	void set_time(void);
	void show_time(void);
	//错误2：数据成员需为private保持封装
private:

	int hour;
	int minute;
	int sec;
};

Time t;

int main()
{
	//错误3：外部调用成员函数需要加类名
	//set_time();
	//show_time();

	t.set_time();
	t.show_time();

	return 0;
}

//错误4：外部定义成员函数需要给出类的作用域限定符,且返回类型不匹配
//int set_time(void)
void Time::set_time(void)

{
	//增加1：输入提示
	cout << "请输入时，分，秒" << endl;

	cin >> t.hour;
	cin >> t.minute;
	cin >> t.sec;


}

//错误5：外部定义成员函数需要给出类的作用域限定符,且返回类型不匹配
//int show_time(void)
void Time::show_time(void)

{
	//增加2：输出提示
	cout << "你输入的时间是";

	cout << t.hour << ":" << t.minute << ":" << t.sec << endl;

	//增加3：退出提示
	cout << "程序退出" << endl;
}