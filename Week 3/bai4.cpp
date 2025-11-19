#include <iostream>
#include <fstream>
using namespace std;

class Ngay
{
private:
    int _ng, _th, _n;
    void chuanHoa();
    void chuanHoaKoAm();
    void chuanHoaNamNhuan();
    bool KiemTraNamNhuan(int y);
    int ngayTrongThang(int m, int y);

public:
    int getTotalDays() const;
    Ngay();
    Ngay(int ng, int th, int n);
    Ngay(int ng);

    Ngay operator+(const Ngay &other) const;
    Ngay operator-(const Ngay &other) const;
    friend ostream &operator<<(ostream &os, const Ngay &);

    bool operator>(const Ngay &other);
};

Ngay::Ngay()
{
    _ng = 1;
    _th = 1;
    _n = 1;
}

Ngay::Ngay(int ng, int th, int n)
{
    _ng = abs(ng);
    _th = abs(th);
    _n = abs(n);

    chuanHoa();
}

Ngay::Ngay(int ng)
{
    _ng = abs(ng);
    _th = 1;
    _n = 1;

    chuanHoaNamNhuan();
}

Ngay Ngay::operator+(const Ngay &other) const
{
    return Ngay(_ng + other._ng, _th + other._th, _n + other._n);
}

Ngay Ngay::operator-(const Ngay &other) const
{
    Ngay kq;
    kq._ng = _ng - other._ng;
    kq._th = _th - other._th;
    kq._n = _n - other._n;

    kq.chuanHoaKoAm();
    return kq;
}

bool Ngay::operator>(const Ngay &other)
{
    if (_n != other._n)
        return _n > other._n;
    if (_th != other._th)
        return _th > other._th;
    return _ng > other._ng;
}

void Ngay::chuanHoa()
{
    _th += (_ng - 1) / 30;
    _ng = (_ng - 1) % 30 + 1;
    _n += (_th - 1) / 12;
    _th = (_th - 1) % 12 + 1;
}

void Ngay::chuanHoaKoAm()
{
    while (_ng <= 0)
    {
        _th--;
        if (_th <= 0)
        {
            _th += 12;
            _n--;
        }
        _ng += ngayTrongThang(_th, _n);
    }

    while (_th <= 0)
    {
        _th += 12;
        _n--;
    }

    if (_n < 0)
    {
        _ng = _th = _n = 0;
    }
}

void Ngay::chuanHoaNamNhuan()
{
    if (_th > 12)
    {
        _n += (_th - 1) / 12;
        _th = (_th - 1) % 12 + 1;
    }

    chuanHoaKoAm(); // Kiểm tra Nếu Âm thì chuẩn hóa sao cho không âm;

    // Chuẩn hóa khi ngày lớn hơn ngày hiện tại của tháng.
    while (_ng > ngayTrongThang(_th, _n))
    {
        _ng -= ngayTrongThang(_th, _n);
        _th++;
        if (_th > 12)
        {
            _n++;
            _th = 1;
        }
    }
}

bool Ngay::KiemTraNamNhuan(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int Ngay::ngayTrongThang(int m, int y)
{
    if (m == 2)
    {
        return KiemTraNamNhuan(y) ? 29 : 28;
    }
    else if (m == 4 || m == 6 || m == 9 || m == 11)
    {
        return 30;
    }
    return 31;
}

int Ngay::getTotalDays() const
{
    return _ng + _th * 30 + _n * 360;
}

Ngay operator-(const int &ngay, const Ngay &other)
{
    return Ngay(ngay) - other;
}

Ngay operator+(const int &ngay, const Ngay &other)
{
    return Ngay(ngay) + other;
}

ostream &operator<<(ostream &os, const Ngay &ngay)
{
    os << ngay._ng << '/' << ngay._th << '/' << ngay._n;
    return os;
}

int main()
{

    Ngay n1;
    Ngay n2(2, 10, 2014);
    Ngay n3(-10, 16, 2000);
    Ngay n4(1000);
    Ngay n5 = n2 + n3;
    Ngay n6 = n1 + 5000;
    // Các test trước, em tìm ra được quy luật rồi mà đến test này nó lại quy luật khác.
    // Em chịu. (n7 lại tính từ ngày 0/0/0 không phải từ ngày 1/1/1)
    Ngay n7 = 1234 + n4;
    Ngay n8 = 190 + n6 + n7;
    Ngay n9 = n8 - n6;
    Ngay n10 = 12000 - n9;
    if (n10 > n6)
    {
        n10 = n2 - 1000 + n6;
    }
    cout << n1 << endl
         << n2 << endl
         << n3 << endl
         << n4 << endl;
    // cout << n5 << endl
    //      << n6 << endl
    //      << n7 << endl
    //      << n8 << endl;
    // cout << n9 << endl
    //      << n10 << endl;

    ifstream fin("input.txt");

    if (!fin.is_open())
    {
        cout << "OK";
    }

    int a, b, c;
    char d, f;
    char line[100];
    while (fin >> a >> d >> b >> f >> c)
    {
        // cout << a << " " << b << " " << c << endl;
        cout << Ngay(a, b, c) << endl;
    }
    return 0;
}