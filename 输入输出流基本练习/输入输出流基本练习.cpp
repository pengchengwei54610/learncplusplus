#include<iostream>
using namespace std;
istream& f(istream& in)
{
	int flagbits;
	flagbits = in.rdstate();
	/* �������������ܾ��������� */
	int temp;
	while (((in >> temp, in.eof()) != 1 && temp != -1))
	{
		if (in.bad())
		{
			cout << "����ϵͳ�������" << endl;
			break;//ϵͳ��������޷��ָ�
		}
		else if (in.fail())
		{
			cout << "������������������������" << endl;
			in.clear();
			while (in.peek() != '\n' && in.peek() != ' ')
				in.ignore(1);
			continue;
		}
		cout << "��˵��:" << temp << endl;
	}
	in.setstate(flagbits);
	return in;
}
int main()
{
	cout << "������һЩ��������-1��Ctrl+Z������" << endl;
	f(cin);
	return 0;
}