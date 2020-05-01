/*通过Huffman编码对文件进行无损压缩,对ser.log压缩一次至6.43MB，压缩比约为65%，多次压缩可有更高压缩率*/
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

//数据结构定义
//Huffman树节点数据结构定义
struct Node
{
	char c; //字符
	int weight; //权重
	Node* left; //左子节点
	Node* right; //右子节点
	Node* parent; //父节点
};

//统计文件中各字符的出现次数及文件总字节数
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

//构造Huffman树的节点
void createNodes(vector<Node>& nodes, const vector<int>& count)
{
	for (int i = 0; i < 256; ++i)
		if (count[i])
		{
			Node node = { char(i),count[i],NULL,NULL,NULL };
			nodes.push_back(node);
		}
}

//将通过权重节点排序
bool cmp(Node a, Node b)
{
	return a.weight > b.weight;
}

//构造Huffman树
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

//生成编码
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

//将霍夫曼树和压缩后的内容写入压缩文件
void compress(ifstream& fin, ofstream& fout, const int sum, const vector<int>& count, map<char, string>& codes)
{
	//写入原文件总字节数,字符总类数和各字符出现的次数
	fout << sum << endl;
	fout << codes.size() << endl;
	for (int i = 0; i < 256; ++i)
		if (count[i])
			fout << i << ' ' << count[i] << endl;
	//写入原文件内容
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

//释放Huffman树
void deleteTree(Node* root)
{
	if (root->left)
		deleteTree(root->left);
	if (root->right)
		deleteTree(root->right);
	delete root;
}

//压缩总函数
void zip(ifstream& fin, ofstream& fout)
{
	//统计文件中各字符出现次数及总字节数
	vector<int> count(256, 0);
	int sum = countChar(fin, count);
	//构造Huffman树的节点
	vector<Node> nodes;
	createNodes(nodes, count);
	//构造Huffman树
	Node* root = createTree(nodes);
	//生成Huffman编码
	map<char, string> codes;
	string code;
	generateCodes(codes, root, code);
	//写入文件
	compress(fin, fout, sum, count, codes);
	//释放Huffman树
	deleteTree(root);
}

//读取原文件总字节数和各字符出现的次数
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
	fin.get(); //读取最后一个\n
	return sum;
}

//写入解压文件
void uncompress(ifstream& fin, ofstream& fout, int sum, Node* const root)
{
	//将压缩文件内容转换为Huffman编码
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

	//Huffman编码解压文件
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

//解压函数
void unzip(ifstream& fin, ofstream& fout)
{
	//读取原文件总字节数和各字符分别出现的次数
	vector<int> count(256, 0);
	int sum = readCount(fin, count);
	//构造Huffman树的节点
	vector<Node> nodes;
	createNodes(nodes, count);
	//构造Huffman树
	Node* root = createTree(nodes);
	//写入文件
	uncompress(fin, fout, sum, root);
	//释放Huffman树所占内存空间
	deleteTree(root);
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cerr << "请确保输入参数个数正确" << endl;
		return -1;
	}

	if (strcmp(argv[3], "zip") && strcmp(argv[3], "unzip"))
	{
		cerr << "未知参数!\n命令列表:\nzip\nunzip" << endl;
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
		cout << "成功压缩" << endl;
	else if (strcmp(argv[3], "unzip") == 0)
		cout << "成功解压" << endl;
	return 0;
}