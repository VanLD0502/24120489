#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;

struct NgayThang
{
    int ngay, thang, nam;
    NgayThang(int ng, int th, int nam) : ngay(ng), thang(th), nam(nam) {}
};

class SinhVien
{
private:
    char MSSV[100];
    char HoTen[100];
    char NgaySinh[100];
    float DLT;
    float DTH;

public:
    SinhVien();
    SinhVien(const char *);
    SinhVien(const char *, const char *, float, float);
    SinhVien(const char *, const char *, float, float, int, int, int);
    SinhVien(const char *, const char *, float, float, NgayThang n);
    SinhVien(const SinhVien &other);

    const char *GetMSSV() const;
    const char *GetHoTen() const;
    const char *GetNgaySinh() const;
    float GetDLT() const;
    float GetDTH() const;

    void Xuat();
};

SinhVien::SinhVien()
{
    strcpy_s(MSSV, sizeof(MSSV), "\"xxxxxxx\"");
    strcpy_s(HoTen, sizeof(HoTen), "\"xxxx\"");
    strcpy_s(NgaySinh, sizeof(NgaySinh), "\"xx/xx/xxxx\"");
    DLT = 10;
    DTH = 10;
}

const char *SinhVien::GetMSSV() const
{
    return this->MSSV;
}

const char *SinhVien::GetHoTen() const
{
    return this->HoTen;
}

const char *SinhVien::GetNgaySinh() const
{
    return this->NgaySinh;
}

float SinhVien::GetDLT() const
{
    return this->DLT;
}

float SinhVien::GetDTH() const
{
    return this->DTH;
}

SinhVien::SinhVien(const char *MSSV) : SinhVien()
{
    strcpy_s(this->MSSV, sizeof(MSSV), MSSV);
}

SinhVien::SinhVien(const char *MSSV, const char *HoTen, float DLT, float DTH) : SinhVien(MSSV)
{
    strcpy_s(this->HoTen, sizeof(this->HoTen), HoTen);
    this->DLT = DLT;
    this->DTH = DTH;
}

SinhVien::SinhVien(const char *MSSV, const char *HoTen, float DLT, float DTH, int ngay, int thang, int nam) : SinhVien(MSSV, HoTen, DLT, DTH)
{
    sprintf_s(NgaySinh, "\"%02d/%02d/%04d\"", ngay, thang, nam);
}

SinhVien::SinhVien(const char *MSSV, const char *HoTen, float DLT, float DTH, NgayThang n) : SinhVien(MSSV, HoTen, DLT, DTH, n.ngay, n.thang, n.nam)
{
}

SinhVien::SinhVien(const SinhVien &other)
{
    strcpy_s(this->MSSV, sizeof(this->MSSV), other.MSSV);
    strcpy_s(this->HoTen, sizeof(this->HoTen), other.HoTen);
    strcpy_s(this->NgaySinh, sizeof(this->NgaySinh), other.NgaySinh);
    this->DLT = other.DLT;
    this->DTH = other.DTH;
}

void SinhVien::Xuat()
{
    cout << "MSSV: " << MSSV << ", "
         << "HoTen: " << HoTen << ", "
         << "NgaySinh: " << NgaySinh << ", "
         << "DLT: " << DLT << ", "
         << "DTH: " << DTH << ".\n";
}

int main()
{
    SinhVien sv1;
    sv1.Xuat();
    SinhVien sv2("1363001");
    sv2.Xuat();
    SinhVien sv3("1363002", "Nguyen Van A", 7, 8.5);
    sv3.Xuat();
    SinhVien sv4("1363003", "Tran Thi B", 8, 9.5, 12, 3, 1996);
    sv4.Xuat();
    NgayThang n(30, 2, 1996);
    SinhVien sv5("1363004", "Ngo Van C", 5, 6, n);
    sv5.Xuat();
    SinhVien sv6(sv5);
    sv6.Xuat();

    return 0;
}
