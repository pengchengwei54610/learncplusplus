#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<iostream>
#include<iomanip>
using namespace std;
class Book_Sale
{
private:
	char* isbn;          // 指向书籍编号的指针
						 // 存放书籍编号的空间需动态申请
						 //书籍编号由5段13位数字组成，如978-7-121-15535-2
	int sold;            // 销售量
	double sellingprice; // 原始价格
	double saleprice;    // 实售价格
	double discount;     // 折扣
	double total;        // 销售总额
public:
	/*可以接受istream&并从中读取书籍销售信息的构造函数Book_Sale (istream &)，析构函数以及其他必要的成员函数*/
	Book_Sale(istream&);
	~Book_Sale();
	void set(int isbn_4, int sold, double price, double discount);
	void show();
	int flag = 0;//标志位标识是否已被初始化
};
Book_Sale::Book_Sale(istream& temp)
{
	isbn = new(nothrow)char[18];
	if (isbn == NULL)
	{
		cerr << "内存申请失败";
		exit(-1);
	}
	int a;
	temp >> a;
	if (a == -1)
	{
		sold = 0;
		sellingprice = 0;
		saleprice = 0;
		discount = 0;
		total = 0;
		return;
	}
	flag = 1;
	strcpy(isbn, "978-7-121-");
	sprintf(isbn + 10, "%d", a);
	isbn[15] = '-';
	a = (10 - ((isbn[0] - '0') + 3 * (isbn[1] - '0') + (isbn[2] - '0') + 3 * (isbn[4] - '0') + (isbn[6] - '0') + 3 * (isbn[7] - '0') + (isbn[8] - '0') + 3 * (isbn[10] - '0') + (isbn[11] - '0') + 3 * (isbn[12] - '0') + (isbn[13] - '0') + 3 * (isbn[14] - '0')) % 10);
	if (a == 10)
		a = 0;
	isbn[16] = '0' + a;
	isbn[17] = 0;
	temp >> sold >> sellingprice >> discount;
	saleprice = sellingprice * discount;
	total = saleprice * sold;
}
void Book_Sale::set(int isbn_41, int sold1, double price, double discount1)
{
	int a;
	sprintf(isbn + 10, "%d", isbn_41);
	isbn[15] = '-';
	a = (10 - ((isbn[0] - '0') + 3 * (isbn[1] - '0') + (isbn[2] - '0') + 3 * (isbn[4] - '0') + (isbn[6] - '0') + 3 * (isbn[7] - '0') + (isbn[8] - '0') + 3 * (isbn[10] - '0') + (isbn[11] - '0') + 3 * (isbn[12] - '0') + (isbn[13] - '0') + 3 * (isbn[14] - '0')) % 10);
	if (a == 10)
		a = 0;
	isbn[16] = '0' + a;
	isbn[17] = 0;
	sold = sold1;
	sellingprice = price;
	discount = discount1;
	saleprice = sellingprice * discount;
	total = saleprice * sold;
}
Book_Sale::~Book_Sale()
{
	delete isbn;
}

void Book_Sale::show()
{
	if (flag == 1)
	{
		cout << setiosflags(ios::fixed);
		cout << "该书的ISBN号为：" << isbn << endl;
		cout << "销量为：" << setprecision(0) << sold << " 原价为：" << setprecision(4) << sellingprice << "元 折扣为：" << discount << " 现价为：" << saleprice << "元 总销售额为：" << total << "元" << endl;
	}
}
int main()
{
	istream& temp(cin);
	int isbn_4;
	int sold;
	double price;
	double discount;
	cout << "请依次输入书籍的isbn第8-12位，该书的销售量，原价以及该书的折扣，以-1结束" << endl;
	Book_Sale book_info(temp);
	book_info.show();
	if (book_info.flag == 0)
	{
		cout << "未输入书籍信息，程序退出" << endl;
		return 0;
	}
	else
	{
		while (1)
		{
			cin >> isbn_4;
			if (isbn_4 == -1)
				break;
			else
			{
				cin >> sold >> price >> discount;
			}
			book_info.set(isbn_4, sold, price, discount);
			book_info.show();
		}
	}
	return 0;
}