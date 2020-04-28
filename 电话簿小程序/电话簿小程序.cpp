#include<iostream>
#include<fstream>
#include<sstream>//不用字符串流时可注释掉
using namespace std;
#define Status bool
#define max_length_per_row 100
void valid(char* files, long long& old)
{
	long long b = atoll(files);
	if (b >= 13000000000 && b <= 19999999999)
	{
		if (b > old)
		{
			old = b;
			return;
		}
		else
		{
			return;
		}
	}
	else
		return;
}
int main(int argc, char* argv[])
{
	stringstream stream;//可以不用字符串流直接输出数字
	string result;
	/*上两行可注释*/
	long long max_phonenumber = 1;
	char temp[max_length_per_row];
	if (argc != 3) {
		cerr << "请给出文件名和前三位号码" << endl;
		return -1;
	}
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "无法打开输入文件" << endl;
		return -1;
	}
	while (in.peek() != EOF)
	{
		in >> temp;
		if (temp[0] == argv[2][0] && temp[1] == argv[2][1] && temp[2] == argv[2][2])
			valid(temp, max_phonenumber);
	}
	//为了使用字符串流强行改的，效率低不如直接输出数字！！
	stream << max_phonenumber;
	stream >> result;
	cout << "查询到的电话号码是：" << result << endl;

	//	cout <<"查询到的电话号码是："<< max_phonenumber << endl;//不用字符串流可直接输出数字
		/* 通过argv[2]查找所有合法信息，并输出所匹配的最大值 */
		/* 需要注意argv均为字符串类型，你可能需要对该参数进行转换 */
	in.close();
	return 0;
}