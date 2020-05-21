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
	void readFromKeyboard()
	{
		for (int count1 = 0; count1 < row; count1++)
			for (int count2 = 0; count2 < column; count2++)
				cin >> a[count1][count2];
	}
	friend Matrix operator+(Matrix& a, Matrix& b);
	void display()
	{
		for (int count1 = 0; count1 < row; count1++)
		{
			for (int count2 = 0; count2 < column; count2++)
				cout << setw(width) << a[count1][count2] << ' ';
			cout << endl;
		}
	}
};
Matrix operator+(Matrix& a1, Matrix& b1)
{
	Matrix c;
	for (int count1 = 0; count1 < row; count1++)
		for (int count2 = 0; count2 < column; count2++)
			c.a[count1][count2] = a1.a[count1][count2] + b1.a[count1][count2];
	return c;
}
int main()
{
	Matrix a, b, c;         // 固定2行3列
	cout << "请输入矩阵a:" << endl;
	a.readFromKeyboard();  // 从键盘读取矩阵a的数据
	cout << "请输入矩阵b:" << endl;
	b.readFromKeyboard();  // 从键盘读取矩阵b的数据
	c = a + b;
	c.display();
	return 0;
}