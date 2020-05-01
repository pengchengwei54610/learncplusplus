#include <iostream>

using namespace std;

class Time                       // 声明Time类
{
private:                          // 数据成员为公有的
	int hour;
	int minute;
	int sec;
public:
	void set_time()
	{
		cout << "请输入设定的时间，以时 分 秒格式输入" << endl;
		cin >> hour;              // 以下三行的作用是输入设定的时间
		cin >> minute;
		cin >> sec;
	}
	void show_time()
	{
		cout << "以下为你设定的时间";
		cout << hour << ":" << minute << ":" << sec << endl;
		cout << "程序退出" << endl;
	}

};

int main()
{
	Time t1;                     // 定义t1为Time类对象	
	t1.set_time();
	t1.show_time();
	return 0;
}