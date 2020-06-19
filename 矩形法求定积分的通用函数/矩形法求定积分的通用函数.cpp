#include <iostream>

using namespace std;

/**********************************************
*
*    TO-DO:
*        �벹ȫ������Ĵ��룬��ֻ�ύ���������Ĵ��롣
*
***********************************************/
#define default_lower_limit 0.0
#define default_limit 1.0
#define default_cal_times 10000
#include<cmath>
class integral
{
protected:
	double points_limit;
	double points_lower_limit;
public:
	friend istream& operator>>(istream& in, integral& a);
	virtual double value() = 0;
	integral(double points_limit1 = default_limit, double points_lower_limit1 = default_lower_limit)
	{
		points_limit = points_limit1;
		points_lower_limit = points_lower_limit1;
	}
};
istream& operator>>(istream& in, integral& a)
{
	in >> a.points_lower_limit >> a.points_limit;
	return in;
}
class integral_sin :public integral
{
public:
	double value()
	{
		double temp1 = 0;
		int count1 = 0;
		double temp2;
		temp2 = (points_limit - points_lower_limit) / default_cal_times;
		for (; count1 <= default_cal_times; count1++)
		{
			temp1 += sin(points_lower_limit + temp2 * count1) * temp2;
		}
		return temp1;
	}
};
class integral_cos :public integral
{
public:
	double value()
	{
		double temp1 = 0;
		int count1 = 0;
		double temp2;
		temp2 = (points_limit - points_lower_limit) / default_cal_times;
		for (; count1 <= default_cal_times; count1++)
		{
			temp1 += cos(points_lower_limit + temp2 * count1) * temp2;
		}
		return temp1;
	}
};
class integral_exp :public integral
{
public:
	double value()
	{
		double temp1 = 0;
		int count1 = 0;
		double temp2;
		temp2 = (points_limit - points_lower_limit) / default_cal_times;
		for (; count1 <= default_cal_times; count1++)
		{
			temp1 += exp(points_lower_limit + temp2 * count1) * temp2;
		}
		return temp1;
	}
};
/**********************************************
*
*    TO-DO END
*
***********************************************/

int main()
{
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;
	integral* p;

	cout << "�����������ޣ�";
	cin >> s1;
	p = &s1;
	cout << "sinxdx�ļ�����Ϊ��" << (p->value()) << endl;

	cout << "�����������ޣ�";
	cin >> s2;
	p = &s2;
	cout << "cosxdx�ļ�����Ϊ��" << (p->value()) << endl;

	cout << "�����������ޣ�";
	cin >> s3;
	p = &s3;
	cout << "expxdx�ļ�����Ϊ��" << (p->value()) << endl;

	return 0;
}