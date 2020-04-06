#include<iostream>
using namespace std;
istream& f(istream& in)
{
	int flagbits;
	flagbits = in.rdstate();
	/* 复读整数，并拒绝错误输入 */
	int temp;
	while (((in >> temp, in.eof()) != 1 && temp != -1))
	{
		if (in.bad())
		{
			cout << "产生系统级别错误" << endl;
			break;//系统级别错误无法恢复
		}
		else if (in.fail())
		{
			cout << "产生非致命错误，请重新输入" << endl;
			in.clear();
			while (in.peek() != '\n' && in.peek() != ' ')
				in.ignore(1);
			continue;
		}
		cout << "你说了:" << temp << endl;
	}
	in.setstate(flagbits);
	return in;
}
int main()
{
	cout << "请输入一些整数，以-1或Ctrl+Z结束。" << endl;
	f(cin);
	return 0;
}