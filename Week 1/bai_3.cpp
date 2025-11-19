#include <iostream>
#include <string>
using namespace std;

class ThoiGian
{
private:
    int _giay, _phut, _gio;

    void calculate(int giay, int phut = 0, int gio = 0);

public:
    ThoiGian();
    ThoiGian(int);
    ThoiGian(int, int);
    ThoiGian(int, int, int);

    void Xuat();
};

ThoiGian::ThoiGian()
{
    _giay = 0;
    _phut = 0;
    _gio = 0;
}

ThoiGian::ThoiGian(int giay)
{
    calculate(giay);
}

ThoiGian::ThoiGian(int phut, int giay)
{
    calculate(giay, phut);
}

ThoiGian::ThoiGian(int gio, int phut, int giay)
{
    calculate(giay, phut, gio);
}

void ThoiGian::Xuat()
{
    printf_s("%02d:%02d:%02d\n", _gio, _phut, _giay);
}

void ThoiGian::calculate(int giay, int phut, int gio)
{
    giay = (giay < 0) ? 0 : abs(giay);
    gio = (gio < 0) ? 0 : abs(gio);
    phut = (phut < 0) ? 0 : abs(phut);

    _giay = giay % 60;
    phut += giay / 60;
    _phut = phut % 60;
    _gio = gio + phut / 60;
}

int main()
{
    ThoiGian tg1;
    tg1.Xuat();
    ThoiGian tg2(1212);
    tg2.Xuat();
    ThoiGian tg3(125, 45);
    tg3.Xuat();
    ThoiGian tg4(12, 239, -78);
    tg4.Xuat();

    return 0;
}