#include<iostream>
#include<iomanip>
using namespace std;
#define width 12
#define row 2
#define column 3
class Matrix
{
private:
	long a[2][3];
public:
	Matrix operator+(Matrix& b);
	friend istream& operator >>(istream& in, Matrix& a);
	friend ostream& operator <<(ostream& out, Matrix& a);
};
Matrix Matrix:: operator+(Matrix& b1)
{
	Matrix c;
	for (int count1 = 0; count1 < row; count1++)
		for (int count2 = 0; count2 < column; count2++)
			c.a[count1][count2] = a[count1][count2] + b1.a[count1][count2];
	return c;
}
istream& operator>>(istream& in, Matrix& a1)
{
	for (int count1 = 0; count1 < row; count1++)
		for (int count2 = 0; count2 < column; count2++)
			in >> a1.a[count1][count2];
	return in;
}
ostream& operator <<(ostream& out, Matrix& a1)
{
	for (int count1 = 0; count1 < row; count1++)
	{
		for (int count2 = 0; count2 < column; count2++)
			out << setw(width) << a1.a[count1][count2] << ' ';
		out << endl;
	}
	return out;
}
int main()
{
	Matrix a, b, c;         // �̶�2��3��
	cout << "���������a:" << endl;
	cin >> a;  // �Ӽ��̶�ȡ����a������
	cout << "���������b:" << endl;
	cin >> b;  // �Ӽ��̶�ȡ����b������
	c = a + b;
	cout << "����c=a+bΪ��" << endl;
	cout << c;
	return 0;
}