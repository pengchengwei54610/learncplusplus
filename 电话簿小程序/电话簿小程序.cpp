#include<iostream>
#include<fstream>
#include<sstream>//�����ַ�����ʱ��ע�͵�
using namespace std;
#define Status bool
#define max_length_per_row 100
void valid(char* files, long long& old)
{
	long long b = atoll(files);
	if (b >= 13000000000 && b <= 19999999999)
	{
		if (b > old)
		{
			old = b;
			return;
		}
		else
		{
			return;
		}
	}
	else
		return;
}
int main(int argc, char* argv[])
{
	stringstream stream;//���Բ����ַ�����ֱ���������
	string result;
	/*�����п�ע��*/
	long long max_phonenumber = 1;
	char temp[max_length_per_row];
	if (argc != 3) {
		cerr << "������ļ�����ǰ��λ����" << endl;
		return -1;
	}
	ifstream in(argv[1]);
	if (!in)
	{
		cerr << "�޷��������ļ�" << endl;
		return -1;
	}
	while (in.peek() != EOF)
	{
		in >> temp;
		if (temp[0] == argv[2][0] && temp[1] == argv[2][1] && temp[2] == argv[2][2])
			valid(temp, max_phonenumber);
	}
	//Ϊ��ʹ���ַ�����ǿ�иĵģ�Ч�ʵͲ���ֱ��������֣���
	stream << max_phonenumber;
	stream >> result;
	cout << "��ѯ���ĵ绰�����ǣ�" << result << endl;

	//	cout <<"��ѯ���ĵ绰�����ǣ�"<< max_phonenumber << endl;//�����ַ�������ֱ���������
		/* ͨ��argv[2]�������кϷ���Ϣ���������ƥ������ֵ */
		/* ��Ҫע��argv��Ϊ�ַ������ͣ��������Ҫ�Ըò�������ת�� */
	in.close();
	return 0;
}