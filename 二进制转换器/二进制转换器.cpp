#include<iostream>
using namespace std;
#define max_length 32
void itobs(int num, char* buffer)
{
	/* ������ת��Ϊ�����Ʋ�����buffer�ַ��� */
	for (int i = 0; i < max_length; i++)
	{
		if (1 << (max_length - i - 1) & num)
			*(buffer + i) = '1';
		else
			*(buffer + i) = '0';
	}
	*(buffer + max_length) = 0;
}
void output_buffer(char* buffer)
{
	int i = 0;
	while (*(buffer + i) != 0)
	{
		cout << *(buffer + i);
		if (i % 8 == 7)
		{
			cout << ' ';
		}
		i++;
	}
	cout << endl;
}
int main()
{
	int num;
	char* buffer = (char*)malloc(sizeof(char) * (max_length + 1));
	cout << "����һЩ����:" << endl;
	while (1)
	{
		if (cin >> num)
		{
			cout << num << "�Ķ������ǣ�";
			itobs(num, buffer);
			output_buffer(buffer);
		}
		else
		{
			break;
		}
	}
	free(buffer);
	return 0;
}