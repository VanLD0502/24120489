#include <iostream>
#include <cstring>
using namespace std;

class Ngay
{
private:
    int _ng, _th, _nam;

public:
    Ngay();
    Ngay(int ng, int th, int n);
    Ngay(int ng);
    Ngay(const char *date);

    void ChuanHoa();

    void Xuat();
};

Ngay::Ngay()
{
    _ng = 1;
    _th = 1;
    _nam = 1;
}

void Ngay::ChuanHoa()
{
    int thangDu = (_ng - 1) / 30;
    _ng = (_ng - 1) % 30 + 1;

    _th += thangDu;

    int NamDu = (_th - 1) / 12;
    _th = (_th - 1) % 12 + 1;

    _nam += NamDu;
}

Ngay::Ngay(int ng, int th, int n)
{
    _ng = abs(ng);
    _th = abs(th);
    _nam = abs(n);

    ChuanHoa();
}

Ngay::Ngay(const char *date)
{
    const char *delim = "-/";
    char *context;
    int len = strlen(date);
    char *cloneDate = new char[len + 1];
    strcpy_s(cloneDate, len + 1, date);

    char *token = strtok_s(cloneDate, delim, &context);
    if (token)
        _ng = atoi(token);

    token = strtok_s(NULL, delim, &context);
    if (token)
        _th = atoi(token);

    token = strtok_s(NULL, delim, &context);
    if (token)
        _nam = atoi(token);
    ChuanHoa();
}

void Ngay::Xuat()
{
    cout << _ng << '/' << _th << '/' << _nam;
}

Ngay::Ngay(int ng)
{
    ng = abs(ng);

    _ng = ng;
    _th = _nam = 1;

    ChuanHoa();
}
int main()
{
    Ngay n1;
    n1.Xuat();
    cout << endl;
    Ngay n2(2, 10, 2024);
    n2.Xuat();
    cout << endl;
    Ngay n3(-100, 16, 1990);
    n3.Xuat();
    cout << endl;
    Ngay n4(1403);
    n4.Xuat();
    cout << endl;
    Ngay n5("12-12-2012");
    n5.Xuat();
    cout << endl;
    return 0;
}