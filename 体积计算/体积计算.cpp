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
	cout << "��������Ҫ����ĳ���������:" << endl;
	int n;
	cin >> n;
	for (int count1 = 0; count1 < n; count1++)
	{
		cout << "�������" << count1 + 1 << "��������ĳ������ߣ�" << endl;
		temp.input_para();
		cout << "��" << count1 + 1 << "������������Ϊ��";
		temp.output_volume();
		cout << endl;
	}
	cout << "�������" << endl;
	return 0;
}