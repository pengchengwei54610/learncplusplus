#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>

using namespace std;

inline void wait_for_press()
{
	cout << endl << "按任意键继续..." << endl;
	_getch();
}

#include <cstring>
#define isbn_length 17
#include<iomanip>
class Book_Sale
{
protected:
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
	Book_Sale(int isbn1 = 0, int sold1 = 0, double sellingprice1 = 0, double discount1 = 0)
	{
		isbn = new(nothrow)char[isbn_length + 1];
		if (isbn == NULL)
		{
			cerr << "内存申请失败";
			exit(0);
		}

		sold = sold1;
		sellingprice = sellingprice1;
		saleprice = sellingprice1 * discount1;
		discount = discount1;
		total = saleprice * sold;
		strcpy(isbn, "978-7-121-");
		sprintf(isbn + 10, "%05d", isbn1);
		isbn[15] = '-';
		int k1;
		k1 = (10 - ((isbn[0] - '0') + 3 * (isbn[1] - '0') + (isbn[2] - '0') + 3 * (isbn[4] - '0') + (isbn[6] - '0') + 3 * (isbn[7] - '0') + (isbn[8] - '0') + 3 * (isbn[10] - '0') + (isbn[11] - '0') + 3 * (isbn[12] - '0') + (isbn[13] - '0') + 3 * (isbn[14] - '0')) % 10);
		if (k1 == 10)
			k1 = 0;
		isbn[16] = '0' + k1;
		isbn[17] = 0;
	};
	Book_Sale(const Book_Sale& temp)
	{
		isbn = new(nothrow)char[isbn_length + 1];
		if (isbn == NULL)
		{
			cerr << "内存申请失败";
			exit(0);
		}
		strcpy(isbn, temp.isbn);
		sold = temp.sold;
		sellingprice = temp.sellingprice;
		saleprice = temp.saleprice;
		discount = temp.discount;
		total = temp.total;
	}
	~Book_Sale();
	void set(int isbn_4, int sold, double price, double discount);
	void display();
	Book_Sale& operator =(const Book_Sale temp)
	{
		isbn = new(nothrow)char[isbn_length + 1];
		if (isbn == NULL)
		{
			cerr << "内存申请失败";
			exit(0);
		}
		strcpy(isbn, temp.isbn);
		sold = temp.sold;
		sellingprice = temp.sellingprice;
		saleprice = temp.saleprice;
		discount = temp.discount;
		total = temp.total;
		return *this;
	};
	friend istream& operator>>(istream& in, Book_Sale& a);
	friend ostream& operator<<(ostream& out, Book_Sale& a);
	Book_Sale& operator+=(int sale_inc);
	Book_Sale& operator-=(int sale_dec);
	bool operator>(const Book_Sale a);
	bool operator>=(const Book_Sale a);
	bool operator==(const Book_Sale a);
	bool operator<(const Book_Sale a);
	bool operator<=(const Book_Sale a);
	bool operator!=(const Book_Sale a);
};
void Book_Sale::set(int isbn_41, int sold1, double price1, double discount1 = 1)
{
	int a;
	if (isbn_41 != -1)
	{
		isbn[10] = 0;
		sprintf(isbn + 10, "%05d", isbn_41);
		isbn[15] = '-';
		a = (10 - ((isbn[0] - '0') + 3 * (isbn[1] - '0') + (isbn[2] - '0') + 3 * (isbn[4] - '0') + (isbn[6] - '0') + 3 * (isbn[7] - '0') + (isbn[8] - '0') + 3 * (isbn[10] - '0') + (isbn[11] - '0') + 3 * (isbn[12] - '0') + (isbn[13] - '0') + 3 * (isbn[14] - '0')) % 10);
		if (a == 10)
			a = 0;
		isbn[16] = '0' + a;
		isbn[17] = 0;
	}
	if (sold1 != -1)
	{
		sold = sold1;
	}
	if (price1 != -1)
	{
		sellingprice = price1;
	}
	if (discount1 != -1)
	{
		discount = discount1;
	}
	saleprice = sellingprice * discount;
	total = saleprice * sold;
	return;
}
Book_Sale::~Book_Sale()
{
	delete isbn;
}
void Book_Sale::display()
{
	cout << setiosflags(ios::fixed);
	cout << "该书的ISBN号为：" << isbn << ",销量为：" << setprecision(0) << sold << "本，原价为：" << setprecision(3) << sellingprice << "元，折扣为：" << discount << "，现价为：" << saleprice << "元，总销售额为：" << total << "元" << endl;
}
istream& operator>>(istream& in, Book_Sale& a)
{
	int k;
	int isbn_41;
	in >> isbn_41;
	a.isbn[10] = 0;
	sprintf((a.isbn + 10), "%05d", isbn_41);
	a.isbn[15] = '-';
	k = (10 - ((a.isbn[0] - '0') + 3 * (a.isbn[1] - '0') + (a.isbn[2] - '0') + 3 * (a.isbn[4] - '0') + (a.isbn[6] - '0') + 3 * (a.isbn[7] - '0') + (a.isbn[8] - '0') + 3 * (a.isbn[10] - '0') + (a.isbn[11] - '0') + 3 * (a.isbn[12] - '0') + (a.isbn[13] - '0') + 3 * (a.isbn[14] - '0')) % 10);
	if (k == 10)
		k = 0;
	a.isbn[16] = '0' + k;
	a.isbn[17] = 0;
	in >> a.sold >> a.sellingprice >> a.discount;
	a.saleprice = a.sellingprice * a.discount;
	a.total = a.saleprice * a.sold;
	return in;
}
ostream& operator<<(ostream& out, Book_Sale& a)
{
	out << setiosflags(ios::fixed);
	out << "该书的ISBN号为：" << a.isbn << ",销量为：" << setprecision(0) << a.sold << "本，原价为：" << setprecision(3) << a.sellingprice << "元，折扣为：" << a.discount << "，现价为：" << a.saleprice << "元，总销售额为：" << a.total << "元" << endl;
	return out;
}
Book_Sale& Book_Sale::operator+=(int sale_inc)
{
	sold += sale_inc;
	total = sold * saleprice;
	return *this;
}
Book_Sale& Book_Sale::operator-=(int sale_inc)
{
	sold -= sale_inc;
	total = sold * saleprice;
	return *this;
}
bool Book_Sale::operator>(const Book_Sale a)
{
	return total > a.total;
};
bool Book_Sale::operator>=(const Book_Sale a)
{
	return total >= a.total;
};
bool Book_Sale::operator==(const Book_Sale a)
{
	return total == a.total;
};
bool Book_Sale::operator<(const Book_Sale a)
{
	return total < a.total;
};
bool Book_Sale::operator<=(const Book_Sale a)
{
	return total <= a.total;
};
bool Book_Sale::operator!=(const Book_Sale a)
{
	return total != a.total;
};
class Book_Sale_Limit :public Book_Sale
{
private:
	int limit;
public:
	Book_Sale_Limit(int isbn1 = 0, int sold1 = 0, double sellingprice1 = 0, double discount1 = 0, int limit1 = 0) :Book_Sale(isbn1, sold1, sellingprice1, discount1)
	{
		limit = limit1;
		if (sold > limit)
		{
			total = saleprice * limit + sellingprice * sold - sellingprice * limit;
		}
	};
	Book_Sale_Limit(const Book_Sale_Limit& temp)
	{
		isbn = new(nothrow)char[isbn_length + 1];
		if (isbn == NULL)
		{
			cerr << "内存申请失败";
			exit(0);
		}
		strcpy(isbn, temp.isbn);
		sold = temp.sold;
		sellingprice = temp.sellingprice;
		saleprice = temp.saleprice;
		discount = temp.discount;
		total = temp.total;
		limit = temp.limit;
	}

	void set(int isbn_4, int sold, double price, double discount, int limit)
	{
		Book_Sale::set(isbn_4, sold, price, discount);
		Book_Sale_Limit::limit = limit;
		if (sold > limit)
		{
			total = saleprice * limit + sellingprice * sold - sellingprice * limit;
		}
	}
	void display()
	{
		cout << setiosflags(ios::fixed);
		cout << "该书的ISBN号为：" << isbn << ",销量为：" << setprecision(0) << sold << "本，原价为：" << setprecision(3) << sellingprice << "元，折扣为：" << discount << "，现价为：" << saleprice << "元，折扣限制为：" << limit << "本，总销售额为：" << total << "元" << endl;
	}
	Book_Sale_Limit& operator =(const Book_Sale_Limit temp)
	{
		isbn = new(nothrow)char[isbn_length + 1];
		if (isbn == NULL)
		{
			cerr << "内存申请失败";
			exit(0);
		}
		strcpy(isbn, temp.isbn);
		sold = temp.sold;
		sellingprice = temp.sellingprice;
		saleprice = temp.saleprice;
		discount = temp.discount;
		total = temp.total;
		limit = temp.limit;
		return *this;
	};
	friend istream& operator>>(istream& in, Book_Sale_Limit& a);
	friend ostream& operator<<(ostream& out, Book_Sale_Limit& a);
	Book_Sale& operator+=(int sale_inc)
	{
		sold += sale_inc;
		total = saleprice * limit + sellingprice * sold - sellingprice * limit;
		return *this;
	}
	Book_Sale& operator-=(int sale_dec)
	{

		sold -= sale_dec;
		total = saleprice * limit + sellingprice * sold - sellingprice * limit;
		return *this;
	}
	bool operator>(const Book_Sale_Limit a)
	{
		return total > a.total;
	}
	bool operator>=(const Book_Sale_Limit a)
	{
		return total >= a.total;
	}
	bool operator==(const Book_Sale_Limit a)
	{
		return total == a.total;
	}
	bool operator<(const Book_Sale_Limit a)
	{
		return total < a.total;
	}
	bool operator<=(const Book_Sale_Limit a)
	{
		return total <= a.total;
	}
	bool operator!=(const Book_Sale_Limit a)
	{
		return total != a.total;
	}
};
istream& operator>>(istream& in, Book_Sale_Limit& a)
{
	int k;
	int isbn_41;
	in >> isbn_41;
	if (isbn_41 > 99999 || isbn_41 < 0)
		return in;
	a.isbn[10] = 0;
	sprintf((a.isbn + 10), "%05d", isbn_41);
	a.isbn[15] = '-';
	k = (10 - ((a.isbn[0] - '0') + 3 * (a.isbn[1] - '0') + (a.isbn[2] - '0') + 3 * (a.isbn[4] - '0') + (a.isbn[6] - '0') + 3 * (a.isbn[7] - '0') + (a.isbn[8] - '0') + 3 * (a.isbn[10] - '0') + (a.isbn[11] - '0') + 3 * (a.isbn[12] - '0') + (a.isbn[13] - '0') + 3 * (a.isbn[14] - '0')) % 10);
	if (k == 10)
		k = 0;
	a.isbn[16] = '0' + k;
	a.isbn[17] = 0;
	in >> a.sold >> a.sellingprice >> a.discount >> a.limit;
	a.saleprice = a.sellingprice * a.discount;
	a.total = a.saleprice * a.limit + a.sellingprice * a.sold - a.sellingprice * a.limit;
	return in;
}
ostream& operator<<(ostream& out, Book_Sale_Limit& a)
{
	out << setiosflags(ios::fixed);
	out << "该书的ISBN号为：" << a.isbn << ",销量为：" << setprecision(0) << a.sold << "本，原价为：" << setprecision(3) << a.sellingprice << "元，折扣为：" << a.discount << "，现价为：" << a.saleprice << "元，折扣限制为：" << a.limit << "本，总销售额为：" << a.total << "元" << endl;
	return out;
}
int main()
{
	cout << "测试Book_Sale类" << endl;
	{
		Book_Sale b1(95995, 3418, 100, 0.9);
		Book_Sale b2 = b1;
		Book_Sale b3;
		b3 = b1;

		cout << "测试初始化，display和cin重载" << endl;

		cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:307620元\n实际为：";
		b1.display();
		cout << "b2应该是同上，实际为：";
		b2.display();
		cout << "b3应该是同上，实际为：";
		b3.display();

		Book_Sale b4;
		cout << "请输入某书籍销售信息：" << endl;
		cin >> b4;
		cout << "b4应该是您刚输入的信息，实际为：";
		b4.display();

		wait_for_press();
	}

	{
		Book_Sale b1, b2, b3(95995, 3418, 100, 1);

		cout << "测试set" << endl;

		b1.set(95995, 3418, 100, 0.9);
		b2.set(95995, 3418, 100);
		b3.set(-1, 3500, -1, 0.8);

		cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:307620元\n实际为：";
		b1.display();
		cout << "b2应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:1，现价为:100元，总销售额为:341800元\n实际为：";
		b2.display();
		cout << "b3应该是该书的ISBN号为:978-7-121-95995-0，销量为:3500本，原价为:100元，折扣为:0.8，现价为:80元，总销售额为:280000元\n实际为：";
		b3.display();

		wait_for_press();
	}

	{
		Book_Sale b1(95995, 3418, 100, 0.9);

		cout << "测试重载+=/-=" << endl;

		b1 += 10;
		cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3428本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:308520元\n实际为：";
		b1.display();

		b1 -= 10;
		cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:307620元\n实际为：";
		b1.display();


		wait_for_press();
	}

	{
		Book_Sale b1(95994, 3000, 100, 0.8);
		Book_Sale b2(95996, 4800, 100, 0.5);
		Book_Sale b3(95998, 2000, 100, 0.9);

		cout << "测试比较运算符" << endl;

		cout << "比较结果应为1，实际为：" << (b1 > b3) << endl;
		cout << "比较结果应为1，实际为：" << (b2 >= b3) << endl;
		cout << "比较结果应为0，实际为：" << (b1 < b3) << endl;
		cout << "比较结果应为0，实际为：" << (b2 <= b3) << endl;
		cout << "比较结果应为1，实际为：" << (b1 == b2) << endl;
		cout << "比较结果应为0，实际为：" << (b1 != b1) << endl;

		wait_for_press();
	}
	cout << "测试Book_Sale_Limit类" << endl;
	{
		Book_Sale_Limit b1(95995, 3418, 100, 0.9, 3000);
		Book_Sale_Limit b2 = b1;
		Book_Sale_Limit b3;
		b3 = b1;

		cout << "测试初始化，display,cin,=重载" << endl;

		cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，折扣限制为:3000本，总销售额为:311800元\n实际为：";
		b1.display();
		cout << "b2应该是同上，实际为：";
		b2.display();
		cout << "b3应该是同上，实际为：";
		b3.display();


		Book_Sale_Limit b4;
		cout << "请输入某书籍销售信息：" << endl;
		cin >> b4;
		cout << "b4应该是您刚输入的信息，实际为：";
		b4.display();

		wait_for_press();
	}

	{
		Book_Sale_Limit b1;

		cout << "测试set" << endl;

		b1.set(95995, 3418, 100, 0.9, 3000);

		cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，折扣限制为:3000本，总销售额为:311800元\n实际为：";
		b1.display();


		wait_for_press();
	}

	{
		Book_Sale_Limit b1(95995, 3418, 100, 0.9, 3000);

		cout << "测试重载+=/-=" << endl;

		b1 += 10;
		cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3428本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:312800元\n实际为：";
		b1.display();

		b1 -= 10;
		cout << "b1应该是该书的ISBN号为:978-7-121-95995-0，销量为:3418本，原价为:100元，折扣为:0.9，现价为:90元，总销售额为:311800元\n实际为：";
		b1.display();


		wait_for_press();
	}

	{
		Book_Sale_Limit b1(95994, 3000, 100, 0.8, 2500);
		Book_Sale_Limit b2(95996, 5000, 100, 0.5, 5000);
		Book_Sale_Limit b3(95998, 2000, 100, 0.9, 1000);

		cout << "测试比较运算符" << endl;

		cout << "比较结果应为1，实际为：" << (b1 > b3) << endl;
		cout << "比较结果应为1，实际为：" << (b2 >= b3) << endl;
		cout << "比较结果应为0，实际为：" << (b1 < b3) << endl;
		cout << "比较结果应为0，实际为：" << (b2 <= b3) << endl;
		cout << "比较结果应为1，实际为：" << (b1 == b2) << endl;
		cout << "比较结果应为0，实际为：" << (b1 != b1) << endl;

		wait_for_press();
	}
	return 0;
}