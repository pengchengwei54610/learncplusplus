/*ͨ��Huffman������ļ���������ѹ��,��ser.logѹ��һ����6.43MB��ѹ����ԼΪ65%�����ѹ�����и���ѹ����*/
#define _CRT_SECURE_NO_WARNINGS 
#include <algorithm>
#include <map>
#include <iostream> 
#include <cstring>
#include <fstream>
#include <cstdlib> 
#include <cstdio> 
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

//���ݽṹ����
//Huffman���ڵ����ݽṹ����
struct Node
{
	char c; //�ַ�
	int weight; //Ȩ��
	Node* left; //���ӽڵ�
	Node* right; //���ӽڵ�
	Node* parent; //���ڵ�
};

//ͳ���ļ��и��ַ��ĳ��ִ������ļ����ֽ���
int countChar(ifstream& fin, vector<int>& count)
{
	char c;
	fin.read(&c, 1);
	while (!fin.eof())
	{
		++count[unsigned char(c)];
		fin.read(&c, 1);
	}
	int sum = 0;
	for (auto i : count)
		sum += i;
	return sum;
}

//����Huffman���Ľڵ�
void createNodes(vector<Node>& nodes, const vector<int>& count)
{
	for (int i = 0; i < 256; ++i)
		if (count[i])
		{
			Node node = { char(i),count[i],NULL,NULL,NULL };
			nodes.push_back(node);
		}
}

//��ͨ��Ȩ�ؽڵ�����
bool cmp(Node a, Node b)
{
	return a.weight > b.weight;
}

//����Huffman��
Node* createTree(vector<Node>& nodes)
{
	sort(nodes.begin(), nodes.end(), cmp);
	while (nodes.size() != 1)
	{
		Node* leftNode = new Node, * rightNode = new Node;
		*leftNode = nodes.back();
		nodes.pop_back();
		*rightNode = nodes.back();
		nodes.pop_back();
		Node parentNode = { 0,leftNode->weight + rightNode->weight,leftNode,rightNode,NULL };
		leftNode->parent = &parentNode;
		rightNode->parent = &parentNode;
		nodes.push_back(parentNode);
		sort(nodes.begin(), nodes.end(), cmp);
	}
	Node* root = new Node;
	*root = nodes.back();
	nodes.pop_back();
	return root;
}

//���ɱ���
void generateCodes(map<char, string>& codes, Node* root, string code)
{
	if (root->left == 0 && root->right == 0)
	{
		codes[root->c] = code;
		return;
	}
	generateCodes(codes, root->left, code + '0');
	generateCodes(codes, root->right, code + '1');
}

//������������ѹ���������д��ѹ���ļ�
void compress(ifstream& fin, ofstream& fout, const int sum, const vector<int>& count, map<char, string>& codes)
{
	//д��ԭ�ļ����ֽ���,�ַ��������͸��ַ����ֵĴ���
	fout << sum << endl;
	fout << codes.size() << endl;
	for (int i = 0; i < 256; ++i)
		if (count[i])
			fout << i << ' ' << count[i] << endl;
	//д��ԭ�ļ�����
	int pos = 0;
	char input = 0, output = 0;
	fin.clear();
	fin.seekg(0, ios::beg);
	fin.read(&input, 1);
	while (!fin.eof())
	{
		string code = codes[input];
		int codeSize = code.size();
		for (int i = 0; i < codeSize; ++i)
		{
			output <<= 1;
			if (code[i] == '1')
				output |= 1;
			else
				output |= 0;
			++pos;
			if (pos == 8)
			{
				fout.write(&output, 1);
				output = pos = 0;
			}
		}
		fin.read(&input, 1);
	}
	if (pos)
	{
		output <<= (8 - pos);
		fout.write(&output, 1);
	}
}

//�ͷ�Huffman��
void deleteTree(Node* root)
{
	if (root->left)
		deleteTree(root->left);
	if (root->right)
		deleteTree(root->right);
	delete root;
}

//ѹ���ܺ���
void zip(ifstream& fin, ofstream& fout)
{
	//ͳ���ļ��и��ַ����ִ��������ֽ���
	vector<int> count(256, 0);
	int sum = countChar(fin, count);
	//����Huffman���Ľڵ�
	vector<Node> nodes;
	createNodes(nodes, count);
	//����Huffman��
	Node* root = createTree(nodes);
	//����Huffman����
	map<char, string> codes;
	string code;
	generateCodes(codes, root, code);
	//д���ļ�
	compress(fin, fout, sum, count, codes);
	//�ͷ�Huffman��
	deleteTree(root);
}

//��ȡԭ�ļ����ֽ����͸��ַ����ֵĴ���
int readCount(ifstream& fin, vector<int>& count)
{
	int sum = 0, codesSize = 0;
	fin >> sum >> codesSize;
	for (int i = 0; i < codesSize; ++i)
	{
		int c, times;
		fin >> c >> times;
		count[c] = times;
	}
	fin.get(); //��ȡ���һ��\n
	return sum;
}

//д���ѹ�ļ�
void uncompress(ifstream& fin, ofstream& fout, int sum, Node* const root)
{
	//��ѹ���ļ�����ת��ΪHuffman����
	string content;
	char c;
	fin.read(&c, 1);
	while (!fin.eof())
	{
		for (int i = 0; i < 8; ++i)
		{
			if (c & (1 << 7))
				content += '1';
			else
				content += '0';
			c <<= 1;
		}
		fin.read(&c, 1);
	}

	//Huffman�����ѹ�ļ�
	Node* p = root;
	for (auto i : content)
	{
		if (p != NULL)
		{
			if (i == '0')
				p = p->left;
			else
				p = p->right;
			if (p != NULL)
			{
				if ((p->left == NULL) && (p->right == NULL))
				{
					fout.write(&p->c, 1);
					--sum;
					if (sum == 0)
						break;
					if (p != NULL)
						p = root;
				}
			}
		}
	}
}

//��ѹ����
void unzip(ifstream& fin, ofstream& fout)
{
	//��ȡԭ�ļ����ֽ����͸��ַ��ֱ���ֵĴ���
	vector<int> count(256, 0);
	int sum = readCount(fin, count);
	//����Huffman���Ľڵ�
	vector<Node> nodes;
	createNodes(nodes, count);
	//����Huffman��
	Node* root = createTree(nodes);
	//д���ļ�
	uncompress(fin, fout, sum, root);
	//�ͷ�Huffman����ռ�ڴ�ռ�
	deleteTree(root);
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cerr << "��ȷ���������������ȷ" << endl;
		return -1;
	}

	if (strcmp(argv[3], "zip") && strcmp(argv[3], "unzip"))
	{
		cerr << "δ֪����!\n�����б�:\nzip\nunzip" << endl;
		return -1;
	}

	ifstream fin(argv[1], ios::binary);
	if (!fin)
	{
		cerr << "Can not open the input file!" << endl;
		return -1;
	}

	ofstream fout(argv[2], ios::binary);
	if (!fout)
	{
		cerr << "Can not open the output file!" << endl;
		return -1;
	}
	if (strcmp(argv[3], "zip") == 0)
		zip(fin, fout);
	else if (strcmp(argv[3], "unzip") == 0)
		unzip(fin, fout);
	fin.close();
	fout.close();
	if (strcmp(argv[3], "zip") == 0)
		cout << "�ɹ�ѹ��" << endl;
	else if (strcmp(argv[3], "unzip") == 0)
		cout << "�ɹ���ѹ" << endl;
	return 0;
}