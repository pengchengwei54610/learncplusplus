#include <iostream>
using namespace std;
#define max_array_axis 16
class Array {
public:
	template<typename ...Args>
	Array(Args... args) {
		// 获取参数包大小并转换为size_t数组
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
			cerr << "内存申请失败" << endl;
		}
		index = 0;
		axisNum = num;
		nowAxis = 0;

	}
	template<typename ...Args>
	Array at(Args... args) {
		// 获取参数包大小并转换为size_t数组
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
		// 获取参数包大小并转换为size_t数组
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
		// 在这里修改子矩阵的nowAxis的值以及其他有必要的值，以返回一个子矩阵     
		if (nowAxis == axisNum)
		{
			cerr << "已到数组最小元素" << endl;
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
			cerr << "内存申请失败" << endl;
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
	int* data;//底层存储数据
	int index;//指向底层的指针
	int shape[16];//每一维度的信息
	int axisNum;//总维度数
	int nowAxis;//当前所在维度
};

int main()
{
	// 1，至少能初始化三个维度的数组，即该类至少需要支持三维索引（可通过重载[]或使用成员函数实现）。
	//example
	Array a(3, 3); // the shape with 3x3
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			a[i][j] = i * j;
			// or
			a.at(i, j).set(i * j);
			cout << a[i][j];
		}
	//// 2，具备基本的矩阵操作功能，至少拥有：矩阵加减法，矩阵点乘点除的操作（具体算法可参看上学期之大作业1）。
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
	//逐元素相加
	//c: [2, 4
	//    6, 8]
	//d: [3, 4
	//    5, 6]
	//*/
	//c = a - b;
	//d = a - 2;
	///*
	//逐元素相减
	//c: [0, 0
	//    0, 0]
	//d: [-1, 0
	//     1, 2]
	//*/
	//c = a * b;
	//d = a * 2;
	///*
	//逐元素相乘
	//c: [1, 4
	//    9, 16]
	//d: [2, 4
	//    6, 8]
	//*/
	//c = a / b;
	//d = a / 2;
	///*
	//逐元素相除
	//c: [1, 1
	//    1, 1]
	//d: [0.5, 1
	//    1.5, 2]
	//注意：这个仅供参考，具体结果可能和你内部成员实现关联。
	//*/
	//// 3，支持reshape操作，即从一个一维矩阵reshape成二维或三维矩阵。
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
	//// 4,支持获取C风格元数据操作，即从Array中获取一个指针，指针内的数据为你矩阵的元数据。
	//// example
	//Array a(4);
	//for (int i = 0; i < 4; i++) a[i] = i;
	//// a: [0, 1, 2, 3]
	//int* b = a.get_content(); // 数据类型取决于你的实现
	//for (int i = 0; i < 4; i++) cout << b[i] << ' ';
	//// output: 0 1 2 3
}