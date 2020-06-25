#include <iostream>
using namespace std;


int main()
{
	// 4,支持获取C风格元数据操作，即从Array中获取一个指针，指针内的数据为你矩阵的元数据。
	// example
	Array a(4);
	for (int i = 0; i < 4; i++) a[i] = i;
	// a: [0, 1, 2, 3]
	int* b = a.get_content(); // 数据类型取决于你的实现
	for (int i = 0; i < 4; i++) cout << b[i] << ' ';
	// output: 0 1 2 3
}