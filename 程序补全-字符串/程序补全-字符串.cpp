#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string.h>
using namespace std;
#define max_length 100
class TString
{
private:
    char* content;        //Ö¸Ïò×Ö·û´®µÄÖ¸Õë
    int   len;            //×Ö·û´®µÄ³¤¶È£¬²»º¬Î²Áã
public:
    TString(char* s = NULL);
    TString(const TString&);
    ~TString();
    char* get_content();
    void set(char* s = NULL);
    void set(const TString&);
    int length();
};
TString::~TString()
{
    if(content!=NULL)
        delete content;//ÊÍ·ÅÄÚ´æ
}
TString::TString(char*s)
{   

    if (s != NULL)
    {
        content = new(nothrow)char[max_length];
        if (content == 0)
        {
            cerr << "ÄÚ´æÉêÇëÊ§°Ü" << endl;
            exit(-1);
        }
        strcpy(content, s);
        len = strlen(s);
    }
    else
    {
        content = NULL;
        len = 0;
    }
}
TString::TString(const TString& a)
{
    if (a.content != NULL)
    {      
        content = new(nothrow)char[max_length];
        if (content == 0)
        {
            cerr << "ÄÚ´æÉêÇëÊ§°Ü" << endl;
            exit(-1);
        }
        strcpy(content, a.content);
        len = strlen(content);
    }
    else
    {
        content = NULL;
        len = 0;
    }
}
char* TString::get_content()
{
    return content;
}
void TString::set(char* s)
{
    if (s != NULL)
    {
        if (content == NULL)
        {
            content = new(nothrow)char[max_length];
            if (content == 0)
            {
                cerr << "ÄÚ´æÉêÇëÊ§°Ü" << endl;
                exit(-1);
            }
        }
        strcpy(content, s);
        len = strlen(s);
    }
    else
    {
        content = NULL;
        len = 0;
    }
}
void TString::set(const TString& a)
{
    if (a.content != NULL)
    {
        if (content == NULL)
        {
            content = new(nothrow)char[max_length];
            if (content == 0)
            {
                cerr << "ÄÚ´æÉêÇëÊ§°Ü" << endl;
                exit(-1);
            }
        }
        strcpy(content, a.content);
        len = strlen(a.content);
    }
    else
    {
        content = NULL;
        len = 0;
    }
}
int TString::length() 
{
    return (len);
}