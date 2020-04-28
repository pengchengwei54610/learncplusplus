#include<iostream>
#include<fstream>
using namespace std;
#define file_name_max_length 100
void path_catch(char* file_name, char* file_path)
{
	int position = 0;
	int count1 = 0;
	int count2 = 0;
	while (file_name[count1] != 0)
	{
		if (file_name[count1] == '/')
		{
			position = count1;
		}
		count1++;
	}
	count1 = position + 1;
	while (file_name[count1] != 0)
	{
		file_path[count2] = file_name[count1];
		count1++;
		count2++;
	}
	file_path[count2] = 0;
	return;
}
void new_path(char* file_path)
{
	char* temp = (char*)malloc(sizeof(char) * file_name_max_length);
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int position = 0;
	while (*(file_path + count1) != 0)
	{
		if (*(file_path + count1) == '.')
		{
			position = count1;
		}
		count1++;
	}
	count2 = position;
	while (*(file_path + count2) != 0)
	{
		*(temp + count3) = *(file_path + count2);
		count2++;
		count3++;
	}
	*(temp + count3) = 0;
	count3 = 0;
	*(file_path + position) = '_';
	position++;
	*(file_path + position) = 'r';
	position++;
	*(file_path + position) = 'e';
	position++;
	*(file_path + position) = 'd';
	position++;
	while (*(temp + count3) != 0)
	{
		*(file_path + position) = *(temp + count3);
		position++;
		count3++;
	}
	*(file_path + position) = 0;
	return;
}
int main(int argc, char* argv[])
{
	char temp;
	int count1 = 0;
	char* output_file_path = (char*)malloc(sizeof(char) * file_name_max_length);
	if (argc != 2) {
		cerr << "��ȷ���������������ȷ" << endl;
		return -1;
	}
	ifstream in(argv[1]);
	if (!in) {
		cerr << "�޷��������ļ�" << endl;
		return -1;
	}
	path_catch(argv[1], output_file_path);
	new_path(output_file_path);
	ofstream out(output_file_path);
	if (!out) {
		cerr << "�޷�������ļ�" << endl;
		return -1;
	}
	cout << "�����ȥ�����������" << endl;
	while (in.peek() != EOF)
	{
		in.get(temp);
		if (count1 % 3 == 0)
		{
			out << temp;
		}
		count1++;
	}
	/* ��ȡ�ļ������н��� */
	/* ���ݹ����Զ������ļ����������������������:����ļ���������������ļ�������_red*/
	in.close();
	out.close();
	return 0;
}