#include <iostream>
using namespace std;


int main()
{
	// 4,֧�ֻ�ȡC���Ԫ���ݲ���������Array�л�ȡһ��ָ�룬ָ���ڵ�����Ϊ������Ԫ���ݡ�
	// example
	Array a(4);
	for (int i = 0; i < 4; i++) a[i] = i;
	// a: [0, 1, 2, 3]
	int* b = a.get_content(); // ��������ȡ�������ʵ��
	for (int i = 0; i < 4; i++) cout << b[i] << ' ';
	// output: 0 1 2 3
}