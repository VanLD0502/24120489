#include <iostream>
#include "SLList.h"
#include <cstring>
using namespace std;

class MyString
{
private:
    SLList<char> str;

public:
    MyString();
    MyString(const char *s);
    MyString(const MyString &other);
    ~MyString();

    bool isEmpty() const;
    MyString &operator=(const MyString &other);
    MyString operator+(const MyString &other);

    friend MyString operator+(const char *s, const MyString &myStr);
    friend ostream &operator<<(ostream &os, const MyString &myStr);

    SLList<MyString> Split(const SLList<char> &arrChar, bool removeEmpty);
};

MyString::MyString()
{
}
MyString::MyString(const char *s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        str.push_back(s[i]);
    }
}

MyString::MyString(const MyString &other)
{
    str = other.str;
}

MyString::~MyString()
{
    // Không cần vì Linkedlist trong SSList tự hủy.
}

bool MyString::isEmpty() const
{
    return str.size() == 0;
}

MyString &MyString::operator=(const MyString &other)
{
    if (this != &other)
    {
        str = other.str;
    }
    return *this;
}

MyString MyString::operator+(const MyString &other)
{
    MyString kq(*this);

    for (SLList<char>::Iterator it = other.str.begin(); it != other.str.end(); it++)
    {
        kq.str.push_back(*it);
    }

    return kq;
}

SLList<MyString> MyString::Split(const SLList<char> &arrChar, bool removeEmpty)
{
    SLList<MyString> kq;

    MyString cur;
    for (SLList<char>::Iterator i = str.begin(); i != str.end(); i++)
    {
        bool isDelimiter = false;
        for (SLList<char>::Iterator j = arrChar.begin(); j != arrChar.end(); j++)
        {
            if (*i == *j)
            {
                isDelimiter = true;
                break;
            }
        }

        if (isDelimiter)
        {
            bool curEmpty = cur.isEmpty();

            if (!removeEmpty || !curEmpty)
            {
                kq.push_back(cur);
            }

            cur.str.Clear();
        }
        else
        {
            cur.str.push_back(*i);
        }
    }

    bool curEmpty = cur.isEmpty();

    if (!removeEmpty || !curEmpty)
    {
        kq.push_back(cur);
    }
    return kq;
}

MyString operator+(const char *s, const MyString &myStr)
{
    return MyString(s) + myStr;
}

ostream &operator<<(ostream &os, const MyString &myStr)
{

    for (SLList<char>::Iterator it = myStr.str.begin(); it != myStr.str.end(); it++)
    {
        os << *it;
    }

    return os;
}

int main()
{
    MyString ms1("abcdsf");
    MyString ms2 = "____" + ms1;
    MyString ms3 = ms1 + ms2;

    cout << "ms1 = " << ms1 << endl;
    cout << "ms2 = " << ms2 << endl;
    cout << "ms3 = " << ms3 << endl
         << endl;

    MyString ms = "a,b,c;d.r;.,h;e,w__u,t.f;j_..";
    SLList<char> arrChar;
    arrChar.push_back(',');
    arrChar.push_back('.');
    arrChar.push_back(';');

    SLList<MyString> vMs = ms.Split(arrChar, false);
    cout << "Split: " << endl;

    for (SLList<MyString>::iterator itMS = vMs.begin(); itMS != vMs.end(); itMS++)
    {
        cout << *itMS << " ";
    }

    cout << endl
         << "size= " << vMs.size() << endl
         << endl;

    vMs = ms.Split(arrChar, true);
    cout << "Split co loai bo empty: " << endl;
    for (SLList<MyString>::iterator itMS = vMs.begin(); itMS != vMs.end(); itMS++)
    {
        cout << *itMS << " ";
    }
    cout << endl
         << "size= " << vMs.size() << endl
         << endl;
    system("pause");
    return 0;
}
