#include<iostream>
#include<math.h>
using namespace std;
int count_length(double temp1)
{
	int length = 5;
	double temp2;
	if (temp1 < 0)
	{
		length++;
		temp2 = int(0 - temp1);
	}
	else
	{
		temp2 = int(temp1);
	}
	while (temp2 / 10 >= 1)
	{
		temp2 /= 10;
		length++;
	}
	return length;
}
int main()
{
	double info1[1000];
	double temp3, temp4, temp5;
	int temp1;
	int max_length = 0;
	int count1 = 0, count2 = 0;
	cout << "请输入一些浮点数，以q结束:" << endl;
	while (1)
	{
		if ((cin >> info1[count1]))
		{
			if ((temp1 = count_length(info1[count1])) > max_length)
			{
				max_length = temp1;
			}
			count1++;
		}
		else
			break;
	}
	while (count2 < count1)
	{
		cout.setf(ios::fixed);
		cout.setf(ios::right);
		cout.precision(3);
		cout.width(max_length);
		temp4 = fabs(info1[count2] - long(info1[count2]));
		temp5 = temp4 * 1000;
		if (1 - (temp5 - long(temp5)) < 1e-5)
		{
			if (info1[count2] > 0)
				temp3 = long(info1[count2]) + (long(temp5 + 1)) / 1000.0;
			else
				temp3 = long(info1[count2]) - (long(temp5 + 1)) / 1000.0;
		}
		else
			if (info1[count2] > 0)
				temp3 = long(info1[count2]) + (int(temp4 * 1000)) / 1000.0;
			else
				temp3 = long(info1[count2]) - (int(temp4 * 1000)) / 1000.0;
		cout << temp3 << endl;
		count2++;
	}
	return 0;
}