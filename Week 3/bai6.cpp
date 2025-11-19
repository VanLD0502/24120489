#include <iostream>

#include <iomanip>
using namespace std;

class ThoiGian
{
private:
    int _giay, _phut, _gio;

    void tinhtoan();

public:
    ThoiGian();
    int GetTongGiay() const;
    ThoiGian(int giay);
    ThoiGian(int phut, int giay);
    ThoiGian(int gio, int phut, int giay);

    ThoiGian operator+(const ThoiGian &other);
    ThoiGian operator-(const ThoiGian &other);
    bool operator<=(const ThoiGian &other);
    friend ostream &operator<<(ostream &os, const ThoiGian &other);
};

void ThoiGian::tinhtoan()
{
    _giay = abs(_giay);
    _phut = abs(_phut);
    _gio = abs(_gio);

    _phut += _giay / 60;
    _giay %= 60;
    _gio += _phut / 60;
    _phut %= 60;
}

int ThoiGian::GetTongGiay() const
{
    return _giay + _phut * 60 + _gio * 3600;
}

ThoiGian::ThoiGian()
{
    _giay = _phut = _gio = 0;
}

ThoiGian::ThoiGian(int giay)
{
    _giay = giay;
    _phut = _gio = 0;

    tinhtoan();
}

ThoiGian::ThoiGian(int phut, int giay)
{
    _giay = giay;
    _phut = phut;
    _gio = 0;

    tinhtoan();
}

ThoiGian::ThoiGian(int gio, int phut, int giay)
{
    _giay = giay;
    _phut = phut;
    _gio = gio;

    tinhtoan();
}

ThoiGian ThoiGian::operator+(const ThoiGian &other)
{
    return ThoiGian(GetTongGiay() + other.GetTongGiay());
}

ThoiGian ThoiGian::operator-(const ThoiGian &other)
{
    int tonggiay = GetTongGiay() - other.GetTongGiay();
    return ThoiGian(tonggiay < 0 ? 0 : tonggiay);
}

bool ThoiGian::operator<=(const ThoiGian &other)
{
    return GetTongGiay() <= other.GetTongGiay();
}

bool operator<=(const int giay, const ThoiGian &other)
{
    return ThoiGian(giay) <= other;
}

ThoiGian operator+(int giay, const ThoiGian &other)
{
    return ThoiGian(giay + other.GetTongGiay());
}

ThoiGian operator-(int giay, const ThoiGian &other)
{
    int tonggiay = giay - other.GetTongGiay();
    return ThoiGian(tonggiay < 0 ? 0 : tonggiay);
}

ostream &operator<<(ostream &os, const ThoiGian &other)
{
    // os << setfill('0') << setw(2) << other._gio << ":" << setfill('0') << setw(2) << other._phut << ":"
    //    << setfill('0') << setw(2) << other._giay;

        return os;
}

int main()
{
    ThoiGian tg1;
    ThoiGian tg2(1212);
    ThoiGian tg3(125, 45);
    ThoiGian tg4(12, 239, 78);
    ThoiGian tg5 = tg2 + tg3;
    ThoiGian tg6 = 5000 + tg2;
    ThoiGian tg7 = tg4 - tg6;
    ThoiGian tg8 = 12300 - tg4;
    ThoiGian tg9, tg10;

    if (tg8 <= tg3)
    {
        tg9 = tg1 + tg2 + 36000;
    }

    if (12345 <= tg5)
    {
        tg10 = tg5 + 12345;
    }
    cout << tg1 << endl
         << tg2 << endl
         << tg3 << endl
         << tg4 << endl;

    cout << tg5 << endl
         << tg6 << endl
         << tg7 << endl
         << tg8 << endl;
    cout << tg9 << endl
         << tg10 << endl;
    return 0;
}
