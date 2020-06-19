#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>

using namespace std;

inline void wait_for_press()
{
	cout << endl << "�����������..." << endl;
	_getch();
}

#include <cstring>
#define isbn_length 17
#include<iomanip>
class Book_Sale
{
protected:
	char* isbn;          // ָ���鼮��ŵ�ָ��
						 // ����鼮��ŵĿռ��趯̬����
						 //�鼮�����5��13λ������ɣ���978-7-121-15535-2
	int sold;            // ������
	double sellingprice; // ԭʼ�۸�
	double saleprice;    // ʵ�ۼ۸�
	double discount;     // �ۿ�
	double total;        // �����ܶ�
public:
	/*���Խ���istream&�����ж�ȡ�鼮������Ϣ�Ĺ��캯��Book_Sale (istream &)�����������Լ�������Ҫ�ĳ�Ա����*/
	Book_Sale(int isbn1 = 0, int sold1 = 0, double sellingprice1 = 0, double discount1 = 0)
	{
		isbn = new(nothrow)char[isbn_length + 1];
		if (isbn == NULL)
		{
			cerr << "�ڴ�����ʧ��";
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
			cerr << "�ڴ�����ʧ��";
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
			cerr << "�ڴ�����ʧ��";
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
	cout << "�����ISBN��Ϊ��" << isbn << ",����Ϊ��" << setprecision(0) << sold << "����ԭ��Ϊ��" << setprecision(3) << sellingprice << "Ԫ���ۿ�Ϊ��" << discount << "���ּ�Ϊ��" << saleprice << "Ԫ�������۶�Ϊ��" << total << "Ԫ" << endl;
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
	out << "�����ISBN��Ϊ��" << a.isbn << ",����Ϊ��" << setprecision(0) << a.sold << "����ԭ��Ϊ��" << setprecision(3) << a.sellingprice << "Ԫ���ۿ�Ϊ��" << a.discount << "���ּ�Ϊ��" << a.saleprice << "Ԫ�������۶�Ϊ��" << a.total << "Ԫ" << endl;
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
			cerr << "�ڴ�����ʧ��";
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
		cout << "�����ISBN��Ϊ��" << isbn << ",����Ϊ��" << setprecision(0) << sold << "����ԭ��Ϊ��" << setprecision(3) << sellingprice << "Ԫ���ۿ�Ϊ��" << discount << "���ּ�Ϊ��" << saleprice << "Ԫ���ۿ�����Ϊ��" << limit << "���������۶�Ϊ��" << total << "Ԫ" << endl;
	}
	Book_Sale_Limit& operator =(const Book_Sale_Limit temp)
	{
		isbn = new(nothrow)char[isbn_length + 1];
		if (isbn == NULL)
		{
			cerr << "�ڴ�����ʧ��";
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
	out << "�����ISBN��Ϊ��" << a.isbn << ",����Ϊ��" << setprecision(0) << a.sold << "����ԭ��Ϊ��" << setprecision(3) << a.sellingprice << "Ԫ���ۿ�Ϊ��" << a.discount << "���ּ�Ϊ��" << a.saleprice << "Ԫ���ۿ�����Ϊ��" << a.limit << "���������۶�Ϊ��" << a.total << "Ԫ" << endl;
	return out;
}
int main()
{
	cout << "����Book_Sale��" << endl;
	{
		Book_Sale b1(95995, 3418, 100, 0.9);
		Book_Sale b2 = b1;
		Book_Sale b3;
		b3 = b1;

		cout << "���Գ�ʼ����display��cin����" << endl;

		cout << "b1Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:307620Ԫ\nʵ��Ϊ��";
		b1.display();
		cout << "b2Ӧ����ͬ�ϣ�ʵ��Ϊ��";
		b2.display();
		cout << "b3Ӧ����ͬ�ϣ�ʵ��Ϊ��";
		b3.display();

		Book_Sale b4;
		cout << "������ĳ�鼮������Ϣ��" << endl;
		cin >> b4;
		cout << "b4Ӧ���������������Ϣ��ʵ��Ϊ��";
		b4.display();

		wait_for_press();
	}

	{
		Book_Sale b1, b2, b3(95995, 3418, 100, 1);

		cout << "����set" << endl;

		b1.set(95995, 3418, 100, 0.9);
		b2.set(95995, 3418, 100);
		b3.set(-1, 3500, -1, 0.8);

		cout << "b1Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:307620Ԫ\nʵ��Ϊ��";
		b1.display();
		cout << "b2Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:1���ּ�Ϊ:100Ԫ�������۶�Ϊ:341800Ԫ\nʵ��Ϊ��";
		b2.display();
		cout << "b3Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3500����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.8���ּ�Ϊ:80Ԫ�������۶�Ϊ:280000Ԫ\nʵ��Ϊ��";
		b3.display();

		wait_for_press();
	}

	{
		Book_Sale b1(95995, 3418, 100, 0.9);

		cout << "��������+=/-=" << endl;

		b1 += 10;
		cout << "b1Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3428����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:308520Ԫ\nʵ��Ϊ��";
		b1.display();

		b1 -= 10;
		cout << "b1Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:307620Ԫ\nʵ��Ϊ��";
		b1.display();


		wait_for_press();
	}

	{
		Book_Sale b1(95994, 3000, 100, 0.8);
		Book_Sale b2(95996, 4800, 100, 0.5);
		Book_Sale b3(95998, 2000, 100, 0.9);

		cout << "���ԱȽ������" << endl;

		cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (b1 > b3) << endl;
		cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (b2 >= b3) << endl;
		cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b1 < b3) << endl;
		cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b2 <= b3) << endl;
		cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (b1 == b2) << endl;
		cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b1 != b1) << endl;

		wait_for_press();
	}
	cout << "����Book_Sale_Limit��" << endl;
	{
		Book_Sale_Limit b1(95995, 3418, 100, 0.9, 3000);
		Book_Sale_Limit b2 = b1;
		Book_Sale_Limit b3;
		b3 = b1;

		cout << "���Գ�ʼ����display,cin,=����" << endl;

		cout << "b1Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ���ۿ�����Ϊ:3000���������۶�Ϊ:311800Ԫ\nʵ��Ϊ��";
		b1.display();
		cout << "b2Ӧ����ͬ�ϣ�ʵ��Ϊ��";
		b2.display();
		cout << "b3Ӧ����ͬ�ϣ�ʵ��Ϊ��";
		b3.display();


		Book_Sale_Limit b4;
		cout << "������ĳ�鼮������Ϣ��" << endl;
		cin >> b4;
		cout << "b4Ӧ���������������Ϣ��ʵ��Ϊ��";
		b4.display();

		wait_for_press();
	}

	{
		Book_Sale_Limit b1;

		cout << "����set" << endl;

		b1.set(95995, 3418, 100, 0.9, 3000);

		cout << "b1Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ���ۿ�����Ϊ:3000���������۶�Ϊ:311800Ԫ\nʵ��Ϊ��";
		b1.display();


		wait_for_press();
	}

	{
		Book_Sale_Limit b1(95995, 3418, 100, 0.9, 3000);

		cout << "��������+=/-=" << endl;

		b1 += 10;
		cout << "b1Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3428����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:312800Ԫ\nʵ��Ϊ��";
		b1.display();

		b1 -= 10;
		cout << "b1Ӧ���Ǹ����ISBN��Ϊ:978-7-121-95995-0������Ϊ:3418����ԭ��Ϊ:100Ԫ���ۿ�Ϊ:0.9���ּ�Ϊ:90Ԫ�������۶�Ϊ:311800Ԫ\nʵ��Ϊ��";
		b1.display();


		wait_for_press();
	}

	{
		Book_Sale_Limit b1(95994, 3000, 100, 0.8, 2500);
		Book_Sale_Limit b2(95996, 5000, 100, 0.5, 5000);
		Book_Sale_Limit b3(95998, 2000, 100, 0.9, 1000);

		cout << "���ԱȽ������" << endl;

		cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (b1 > b3) << endl;
		cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (b2 >= b3) << endl;
		cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b1 < b3) << endl;
		cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b2 <= b3) << endl;
		cout << "�ȽϽ��ӦΪ1��ʵ��Ϊ��" << (b1 == b2) << endl;
		cout << "�ȽϽ��ӦΪ0��ʵ��Ϊ��" << (b1 != b1) << endl;

		wait_for_press();
	}
	return 0;
}