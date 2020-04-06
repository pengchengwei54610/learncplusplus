#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
using namespace std;
#define Status bool
#define num_of_number 10
#define success 1
#define fail 0
Status readFromStdin(int array[])
{
	int count1 = 0;
	while (count1 < num_of_number)
	{
		cin >> array[count1];
		count1++;
	}
	return success;
}
Status readFromFile(int array[])
{
	FILE* infile;
	infile = fopen("D:\\1.txt", "r");
	if (infile == NULL)
	{
		printf("打开需读入的文件失败\n");
		return fail;
	}
	int count1 = num_of_number;
	while (count1 < 2 * num_of_number)
	{
		fscanf(infile, "%d", &array[count1]);
		count1++;
	}
	fclose(infile);
	return success;
}
void bubblesort(int array[], int num)
{
	int temp;
	for (int count1 = 0; count1 < num - 1; count1++)
	{
		for (int count2 = 0; count2 < (num - count1 - 1); count2++)
		{
			if (array[count2] > array[count2 + 1])
			{
				temp = array[count2];
				array[count2] = array[count2 + 1];
				array[count2 + 1] = temp;
			}
		}
	}
}
Status outToFile(int array[], int num)
{
	FILE* fout;
	fout = fopen("1.out", "w");
	if (fout == NULL)
	{
		printf("打开需写入的文件失败\n");
		return fail;
	}
	int count1 = 0;
	while (count1 < num)
	{
		fprintf(fout, "%d ", array[count1]);
		count1++;
	}
	fclose(fout);
	return success;
}
int main()
{
	int array[2 * num_of_number];
	readFromStdin(array);
	if (readFromFile(array) == fail)
		return 0;
	bubblesort(array, 2 * num_of_number);
	if (outToFile(array, 2 * num_of_number) == success)
		cout << "已成功保存文件" << endl;
	return 0;
}