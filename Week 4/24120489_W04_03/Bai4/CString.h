#include <iostream>
#include <string>

using namespace std;
class CString
{
private:
    char *_mang;

public:
    CString();
    CString(const char *);
    ~CString();
    CString(const CString &);
    CString &operator=(const CString &);

    friend ostream &operator<<(ostream &, const CString &);
};

CString::CString()
{
    _mang = nullptr;
}

CString::~CString()
{
    if (_mang)
    {
        delete[] _mang;
        _mang = nullptr;
    }
}

ostream &operator<<(ostream &os, const CString &cs)
{
    os << cs._mang;

    return os;
}

CString::CString(const char *str)
{
    int len = strlen(str);

    _mang = new char[len + 1];
    strcpy_s(_mang, len + 1, str);
}

CString::CString(const CString &cs) : CString(cs._mang)
{
    // cout << "Th copy constructor was called" << endl;
}

CString &CString::operator=(const CString &cs)
{

    if (_mang != nullptr)
    {
        delete[] _mang;
    }

    int len = strlen(cs._mang) + 1;
    _mang = new char[len];
    strcpy_s(_mang, len, cs._mang);

    return *this;
}
