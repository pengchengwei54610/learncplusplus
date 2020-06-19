#include <iostream>
using namespace std;
#define max_array_axis 16
class Array {
public:
	template<typename ...Args>
	Array(Args... args) {
		// ��ȡ��������С��ת��Ϊsize_t����
		auto num = sizeof...(args);
		size_t list[max_array_axis] = { args... };
		int temp1 = 1;
		for (unsigned int i = 0; i < num; i++)
		{
			shape[i] = list[i];
			temp1 *= list[i];
		}
		data = new(nothrow)int[temp1];
		if (data == NULL)
		{
			cerr << "�ڴ�����ʧ��" << endl;
		}
		index = 0;
		axisNum = num;
		nowAxis = 0;

	}
	template<typename ...Args>
	Array at(Args... args) {
		// ��ȡ��������С��ת��Ϊsize_t����
		auto num = sizeof...(args);
		size_t list[] = { args... };
		Array a = *this;
		for (unsigned int count1 = 0; count1 < num; count1++)
		{
			if (count1 != axisNum - 1)
				a.index += index + list[count1] * shape[count1 + 1];
			else
				a.index += index + list[count1];
		}
		return a;
	}
	template<typename ...Args>
	void reshape(Args... args) {
		// ��ȡ��������С��ת��Ϊsize_t����
		auto num = sizeof...(args);
		size_t list[] = { args... };
	}
	int* get_content() {
		return data;
	}
	void set(int value) {
		*(data + index) = value;
	}
	Array operator[](int index) {
		// �������޸��Ӿ����nowAxis��ֵ�Լ������б�Ҫ��ֵ���Է���һ���Ӿ���     
		if (nowAxis == axisNum)
		{
			cerr << "�ѵ�������СԪ��" << endl;
			exit(0);
		}
		else
		{
			Array a;
			a.data = data;
			a.nowAxis = nowAxis;
			if (nowAxis < axisNum - 1)
				a.index = Array::index + index * shape[++a.nowAxis];
			else
				a.index = Array::index + index;
			a.axisNum = axisNum;
			for (int count1 = 0; count1 < a.axisNum; count1++)
			{
				a.shape[count1] = shape[count1];
			}
			return a;
		}
	}
	Array& operator=(int data) {
		this->data[index] = data;
		return *this;
	}
	Array& operator =(const Array temp)
	{
		int temp1 = 1;
		for (unsigned int i = 0; i < temp.axisNum; i++)
		{
			shape[i] = temp.shape[i];
			temp1 *= shape[i];
		}
		data = new(nothrow)int[temp1];
		if (data == NULL)
		{
			cerr << "�ڴ�����ʧ��" << endl;
		}
		for (unsigned int i = 0; i < temp1; i++)
		{
			data[i] = temp.data[i];
		}
		index = temp.index;
		axisNum = temp.axisNum;
		nowAxis = temp.axisNum;
		return *this;
	}
	operator int() {
		return data[index];
	}
	int* data;//�ײ�洢����
	int index;//ָ��ײ��ָ��
	int shape[16];//ÿһά�ȵ���Ϣ
	int axisNum;//��ά����
	int nowAxis;//��ǰ����ά��
};

int main()
{
	// 1�������ܳ�ʼ������ά�ȵ����飬������������Ҫ֧����ά��������ͨ������[]��ʹ�ó�Ա����ʵ�֣���
	//example
	Array a(3, 3); // the shape with 3x3
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			a[i][j] = i * j;
			// or
			a.at(i, j).set(i * j);
			cout << a[i][j];
		}
	//// 2���߱������ľ���������ܣ�����ӵ�У�����Ӽ����������˵���Ĳ����������㷨�ɲο���ѧ��֮����ҵ1����
	//// example
	//Array a(2, 2), b(2, 2), c(2, 2), d(2, 2);
	//int cnt = 1;
	//for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) {
	//    a[i][j] = cnt;
	//    b[i][j] = cnt;
	//    cnt++;
	//}
	///*
	//a: [1, 2     b: [1, 2
	//    3, 4]        3, 4]
	//*/
	//c = a + b;
	//d = a + 2;
	///*
	//��Ԫ�����
	//c: [2, 4
	//    6, 8]
	//d: [3, 4
	//    5, 6]
	//*/
	//c = a - b;
	//d = a - 2;
	///*
	//��Ԫ�����
	//c: [0, 0
	//    0, 0]
	//d: [-1, 0
	//     1, 2]
	//*/
	//c = a * b;
	//d = a * 2;
	///*
	//��Ԫ�����
	//c: [1, 4
	//    9, 16]
	//d: [2, 4
	//    6, 8]
	//*/
	//c = a / b;
	//d = a / 2;
	///*
	//��Ԫ�����
	//c: [1, 1
	//    1, 1]
	//d: [0.5, 1
	//    1.5, 2]
	//ע�⣺��������ο������������ܺ����ڲ���Աʵ�ֹ�����
	//*/
	//// 3��֧��reshape����������һ��һά����reshape�ɶ�ά����ά����
	//// example
	//Array a(16);
	//for (int i = 0; i < 16; i++) a[i] = i;
	//// a: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
	//a.reshape(4, 4);
	///*
	//a: [0,  1,  2,  3
	//    4,  5,  6,  7
	//    8,  9, 10, 11
	//   12, 13, 14, 15]
	//*/
	//// 4,֧�ֻ�ȡC���Ԫ���ݲ���������Array�л�ȡһ��ָ�룬ָ���ڵ�����Ϊ������Ԫ���ݡ�
	//// example
	//Array a(4);
	//for (int i = 0; i < 4; i++) a[i] = i;
	//// a: [0, 1, 2, 3]
	//int* b = a.get_content(); // ��������ȡ�������ʵ��
	//for (int i = 0; i < 4; i++) cout << b[i] << ' ';
	//// output: 0 1 2 3
}