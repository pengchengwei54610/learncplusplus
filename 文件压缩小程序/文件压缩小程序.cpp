#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void replaceString(string& origin, string old_value, string new_value) {

    /* 该函数用于对origin全文查找出现的old_value 并用new_value替换 */

    for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
        if ((pos = origin.find(old_value, pos)) != string::npos)
            origin.replace(pos, old_value.length(), new_value);
        else break;
    }
}

int main(int argc, char* argv[]) {
    cout << "Zipper 0.001! Author: root" << endl;
    if (argc != 4) {
        cerr << "Please make sure the number of parameters is correct." << endl;
        return -1;
    }

    if (strcmp(argv[3], "zip")) {
        cerr << "Unknown parameter!\nCommand list:\nzip" << endl;
        return -1;
    }

    ifstream fin(argv[1], ios::binary);               // 以二进制方式打开文件
    if (!fin) {
        cerr << "Can not open the input file!" << endl;   // 输出错误信息并退出
        return -1;
    }

    istreambuf_iterator<char> beg(fin), end;              // 设置两个文件指针，指向开始和结束，以char(一字节)为步长
    string content(beg, end);                             // 将文件全部读入string字符串
    fin.close();                                          // 操作完文件后关闭文件句柄是一个好习惯

    /* 在这里对冗余数据进行剔除 */
    replaceString(content, "#Software: Hllpoj Server 1.0.1 / Logger 1.0.0 built 0001\r\n#Version: 1.0\r\n#Date: 2019-03-13 ", "");
    replaceString(content, "#Fields: date time s-ip cs-method cs-uri-stem cs-uri-query s-port "
        "cs-username c-ip cs(User-Agent) cs(Referer) sc-status sc-substatus sc-win32-status time-taken", "");
    replaceString(content, "Mozilla/5.0+(Windows+NT+10.0;+Win64;+x64)+AppleWebKit/537.36+(KHTML,+like+Gecko)+", "");
    replaceString(content, "2019-03-13 ", "");

    ofstream fout(argv[2], ios::binary); // 打开输出文件
    if (!fout) {
        cerr << "Can not open the output file!" << endl;
        return -1;
    }
    fout << content;                                      // 直接将操作好的字符串进行输出
    fout.close();

    cout << "Complete!" << endl;
    return 0;
}