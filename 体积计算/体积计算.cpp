#include<iostream>
using namespace std;
class rectangle
{
private:
	unsigned int length;
	unsigned int width;
	unsigned int height;
public:
	void input_para()
	{
		cin >> length >> width >> height;
	}
	long long cal_volume()
	{
		return ((long long)(length)*width * height);
	}
	void output_volume()
	{
		cout << cal_volume();
	}
};

int main()
{
	rectangle temp;
	cout << "请输入需要计算的长方体数量:" << endl;
	int n;
	cin >> n;
	for (int count1 = 0; count1 < n; count1++)
	{
		cout << "请输入第" << count1 + 1 << "个长方体的长、宽、高：" << endl;
		temp.input_para();
		cout << "第" << count1 + 1 << "个长方体的体积为：";
		temp.output_volume();
		cout << endl;
	}
	cout << "程序结束" << endl;
	return 0;
}