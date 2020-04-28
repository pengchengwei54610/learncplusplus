#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void replaceString(string& origin, string old_value, string new_value) {

    /* �ú������ڶ�originȫ�Ĳ��ҳ��ֵ�old_value ����new_value�滻 */

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

    ifstream fin(argv[1], ios::binary);               // �Զ����Ʒ�ʽ���ļ�
    if (!fin) {
        cerr << "Can not open the input file!" << endl;   // ���������Ϣ���˳�
        return -1;
    }

    istreambuf_iterator<char> beg(fin), end;              // ���������ļ�ָ�룬ָ��ʼ�ͽ�������char(һ�ֽ�)Ϊ����
    string content(beg, end);                             // ���ļ�ȫ������string�ַ���
    fin.close();                                          // �������ļ���ر��ļ������һ����ϰ��

    /* ��������������ݽ����޳� */
    replaceString(content, "#Software: Hllpoj Server 1.0.1 / Logger 1.0.0 built 0001\r\n#Version: 1.0\r\n#Date: 2019-03-13 ", "");
    replaceString(content, "#Fields: date time s-ip cs-method cs-uri-stem cs-uri-query s-port "
        "cs-username c-ip cs(User-Agent) cs(Referer) sc-status sc-substatus sc-win32-status time-taken", "");
    replaceString(content, "Mozilla/5.0+(Windows+NT+10.0;+Win64;+x64)+AppleWebKit/537.36+(KHTML,+like+Gecko)+", "");
    replaceString(content, "2019-03-13 ", "");

    ofstream fout(argv[2], ios::binary); // ������ļ�
    if (!fout) {
        cerr << "Can not open the output file!" << endl;
        return -1;
    }
    fout << content;                                      // ֱ�ӽ������õ��ַ����������
    fout.close();

    cout << "Complete!" << endl;
    return 0;
}