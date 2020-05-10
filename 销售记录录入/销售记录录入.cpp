#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<iostream>
#include<iomanip>
using namespace std;
class Book_Sale
{
private:
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
	Book_Sale(istream&);
	~Book_Sale();
	void set(int isbn_4, int sold, double price, double discount);
	void show();
	int flag = 0;//��־λ��ʶ�Ƿ��ѱ���ʼ��
};
Book_Sale::Book_Sale(istream& temp)
{
	isbn = new(nothrow)char[18];
	if (isbn == NULL)
	{
		cerr << "�ڴ�����ʧ��";
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
		cout << "�����ISBN��Ϊ��" << isbn << endl;
		cout << "����Ϊ��" << setprecision(0) << sold << " ԭ��Ϊ��" << setprecision(4) << sellingprice << "Ԫ �ۿ�Ϊ��" << discount << " �ּ�Ϊ��" << saleprice << "Ԫ �����۶�Ϊ��" << total << "Ԫ" << endl;
	}
}
int main()
{
	istream& temp(cin);
	int isbn_4;
	int sold;
	double price;
	double discount;
	cout << "�����������鼮��isbn��8-12λ���������������ԭ���Լ�������ۿۣ���-1����" << endl;
	Book_Sale book_info(temp);
	book_info.show();
	if (book_info.flag == 0)
	{
		cout << "δ�����鼮��Ϣ�������˳�" << endl;
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