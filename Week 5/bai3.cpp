#include <iostream>
#include "SLList.h"
#include <cstring>
#include <fstream>
using namespace std;
class SoNguyenLon
{
private:
    SLList<unsigned char> lCS;
    void Pow10(const int &n);
    void Normalize();

public:
    SoNguyenLon(void);
    SoNguyenLon(const int &cs, const int &scs);
    SoNguyenLon(const unsigned long &n);
    SoNguyenLon(const SoNguyenLon &snl);
    SoNguyenLon(const char *s);
    ~SoNguyenLon(void);

    int SoCS();
    SoNguyenLon operator+(SoNguyenLon snl);
    SoNguyenLon operator-(SoNguyenLon snl);
    SoNguyenLon operator*(SoNguyenLon snl);
    bool operator>(SoNguyenLon &snl);
    const SoNguyenLon &operator=(const SoNguyenLon &snl);
    SoNguyenLon &operator+=(SoNguyenLon snl);
    friend SoNguyenLon operator+(const unsigned int &n, const SoNguyenLon &snl);
    friend SoNguyenLon operator-(const unsigned int &n, const SoNguyenLon &snl);
    friend SoNguyenLon operator*(const unsigned int &n, const SoNguyenLon &snl);
    friend ostream &operator<<(ostream &os, const SoNguyenLon &snl);
};

void SoNguyenLon::Pow10(const int &n)
{
    for (int i = 0; i < n; i++)
    {
        lCS.insert(lCS.begin(), 0);
    }
}

void SoNguyenLon::Normalize()
{
    while (lCS.size() > 1 && lCS.back() == 0)
    {
        lCS.RemoveTail();
    }
}

SoNguyenLon::SoNguyenLon(void)
{
    lCS.push_back(0);
}

SoNguyenLon::SoNguyenLon(const int &cs, const int &scs)
{
    int csR = cs;

    if (csR < 1)
    {
        csR = 1;
    }

    if (csR > 9)
    {
        csR = 9;
    }

    int soCS = abs(scs);

    if (soCS < 1)
    {
        soCS = 1;
    }

    for (int i = 0; i < soCS; i++)
    {
        lCS.push_back(csR);
    }
}

SoNguyenLon::SoNguyenLon(const unsigned long &n)
{
    unsigned long temp = n;

    // Làm cách này có thể xử lí được khi n = 0;
    do
    {
        lCS.push_back(temp % 10);
        temp /= 10;
    } while (temp > 0);
}

SoNguyenLon::SoNguyenLon(const SoNguyenLon &snl)
{
    lCS = snl.lCS;
}

SoNguyenLon::SoNguyenLon(const char *s)
{
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        if (s[i] < '0' || s[i] > '9')
        {
            cerr << "So Nguyen Lon khong the chua ki tu: " << s[i] << '\n';
            return;
        }
        lCS.push_back(s[i] - '0');
    }
}

SoNguyenLon::~SoNguyenLon(void)
{
}

int SoNguyenLon::SoCS()
{
    return lCS.size();
}

bool SoNguyenLon::operator>(SoNguyenLon &snl)
{
    if (lCS.size() > snl.lCS.size())
    {
        return true;
    }

    if (lCS.size() < snl.lCS.size())
    {
        return false;
    }

    for (int i = lCS.size() - 1; i >= 0; i--)
    {
        if (lCS[i] == snl.lCS[i])
        {
            continue;
        }

        if (lCS[i] > snl.lCS[i])
        {
            return true;
        }

        return false;
    }

    return false;
}

const SoNguyenLon &SoNguyenLon::operator=(const SoNguyenLon &snl)
{
    lCS = snl.lCS;
    return *this;
}

SoNguyenLon &SoNguyenLon::operator+=(SoNguyenLon snl)
{
    *this = *this + snl;

    return *this;
}

SoNguyenLon SoNguyenLon::operator+(SoNguyenLon snl)
{
    SoNguyenLon snlKQ;

    snlKQ.lCS.Clear();
    SoNguyenLon *snlSCSMax = (SoCS() > snl.SoCS()) ? this : &snl;
    SoNguyenLon *snlSCSMin = (SoCS() < snl.SoCS()) ? this : &snl;

    int nho = 0, temp;

    for (int i = 0; i < snlSCSMin->SoCS(); ++i)
    {
        temp = lCS[i] + snl.lCS[i] + nho;
        snlKQ.lCS.push_back(temp % 10);
        nho = temp / 10;
    }

    for (int i = snlSCSMin->SoCS(); i < snlSCSMax->SoCS(); ++i)
    {
        temp = snlSCSMax->lCS[i] + nho;
        snlKQ.lCS.push_back(temp % 10);
        nho = temp / 10;
    }

    if (nho > 0)
    {
        snlKQ.lCS.push_back(1);
    }

    return snlKQ;
}

SoNguyenLon SoNguyenLon::operator-(SoNguyenLon snl)
{
    if (!(*this > snl))
    {
        return SoNguyenLon();
    }

    SoNguyenLon kq;
    kq.lCS.Clear();
    int lenA = lCS.size();
    int lenB = snl.SoCS();

    int nho = 0;
    for (int i = 0; i < lenB; i++)
    {
        int digit = lCS[i] - snl.lCS[i] - nho;

        kq.lCS.push_back((digit + 10) % 10);
        nho = digit < 0 ? 1 : 0;
    }

    for (int i = lenB; i < lenA; i++)
    {
        int digit = lCS[i] - nho;
        kq.lCS.push_back((digit + 10) % 10);
        nho = digit < 0 ? 1 : 0;
    }

    kq.Normalize();

    return kq;
}

SoNguyenLon SoNguyenLon::operator*(SoNguyenLon snl)
{
    SoNguyenLon snlKq, *psnlTemp;
    /*
        // Do code của thầy bị sai so sánh kiểu này 2 số có cùng chữ số thì nó chỉ lấy &snl, em xin phép thầy sửa nó.
        // SoNguyenLon *snlSCSMax = (SoCS() > snl.SoCS()) ? this : &snl;
        // SoNguyenLon *snlSCSMin = (SoCS() < snl.SoCS()) ? this : &snl;
    */

    SoNguyenLon *snlSCSMax = nullptr;
    SoNguyenLon *snlSCSMin = nullptr;

    if (*this > snl)
    {
        snlSCSMax = this;
        snlSCSMin = &snl;
    }
    else
    {
        snlSCSMax = &snl;
        snlSCSMin = this;
    }

    int nho = 0, temp;
    for (int i = 0; i < snlSCSMin->SoCS(); ++i)
    {
        psnlTemp = new SoNguyenLon;
        psnlTemp->lCS.Clear();
        nho = 0;

        for (int j = 0; j < snlSCSMax->SoCS(); ++j)
        {
            temp = snlSCSMin->lCS[i] * snlSCSMax->lCS[j] + nho;
            psnlTemp->lCS.push_back(temp % 10);
            nho = temp / 10;
        }

        if (nho > 0)
        {
            psnlTemp->lCS.push_back(nho);
        }

        psnlTemp->Pow10(i);
        snlKq += *psnlTemp;

        delete psnlTemp;
    }
    return snlKq;
}

SoNguyenLon operator+(const unsigned int &n, const SoNguyenLon &snl)
{
    return SoNguyenLon(n) + snl;
}

SoNguyenLon operator-(const unsigned int &n, const SoNguyenLon &snl)
{
    return SoNguyenLon(n) - snl;
}

SoNguyenLon operator*(const unsigned int &n, const SoNguyenLon &snl)
{
    return SoNguyenLon(n) * snl;
}

ostream &operator<<(ostream &os, const SoNguyenLon &other)
{
    for (int i = other.lCS.size() - 1; i >= 0; --i)
    {
        os << (int)other.lCS[i];
    }

    return os;
}

int main()
{
    // const int iTest = 78912;
    // SoNguyenLon snl1(123);
    // SoNguyenLon snl2(40000);

    // cout << snl1 << " + " << snl2 << " = ";
    // cout << (snl1 + snl2) << endl;
    // cout << snl1 << " * " << snl2 << " = ";
    // cout << snl1 * snl2 << endl;
    // cout << snl1 << " - " << snl2 << " = ";
    // cout << snl1 - snl2 << endl;
    // cout << snl2 << " - " << snl1 << " = ";
    // cout << snl2 - snl1 << endl;
    // cout << iTest << " - " << snl2 << " = ";
    // cout << iTest - snl2 << endl;

    // ifstream fin("input.txt");

    // char line[1000];
    // char left[500], right[500];
    // char oper;

    // while (fin.getline(line, 1000))
    // {
    //     int i;
    //     for (i = 0; i < strlen(line); i++)
    //     {
    //         if (line[i] < '0' || line[i] > '9')
    //         {
    //             oper = line[i];
    //             break;
    //         }
    //     }

    //     strncpy_s(left, sizeof(left), line, i);
    //     left[i] = '\0';
    //     strcpy_s(right, sizeof(right), line + i + 1);

    //     SoNguyenLon a(left);
    //     SoNguyenLon b(right);

    //     switch (oper)
    //     {
    //     case '+':
    //         /* code */
    //         cout << a + b;
    //         break;
    //     case '-':
    //         /* code */
    //         cout << a - b;
    //         break;
    //     case '*':
    //         /* code */
    //         cout << a * b;
    //         break;
    //     case '/':
    //         /* code */
    //         break;
    //     default:
    //         break;
    //     }
    //     cout << endl;
    // }

    ifstream fin("input.txt");
    char line[100];
    while (fin.getline(line, 100))
    {
        int a, b, c;
        char d, f;

        cin >> a >> d >> b >> f >> c;
    }
    system("pause");
    return 0;
}
