#include<iostream>
#include<fstream>
using namespace std;
#define Status bool
#define success 1
#define fail 0
#define max_rows 1000
int main()
{
	char temp1;
	ifstream file1("foo.bar", ios::in);
	if (!file1.is_open())
	{
		cout << "打开文件失败" << endl;
		return 0;
	}
	int count1 = 0, count2 = 0, count3 = 0;
	int data1[max_rows] = { 0 };
	while (file1.eof() != 1)
	{
		for (temp1 = file1.get(); temp1 != '\n' && temp1 != EOF; count2++)
			temp1 = file1.get();
		count2++;
		data1[count1 + 2] = count2;
		count1++;
	}
	file1.close();
	ofstream file2;
	file2.open("foo.bar", ios::out | ios::app);
	if (!file2.is_open())
	{
		cout << "打开文件失败" << endl;
		return 0;
	}
	data1[0] = count1;
	file2 << endl;
	while (count3 < count1 + 2)
	{
		file2 << data1[count3] << ' ';
		count3++;
	}
	file2.close();
	return 0;
}