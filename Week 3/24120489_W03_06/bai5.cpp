#include <iostream>
#include <cstring>
using namespace std;

class SoNguyenLon
{
private:
    // static constexpr int maxSize = 100; (cái này em xem qua AI em không biết được xài không nên em comment ở đây). Nó có thể được tính toán tại thời điểm compile.
    // char snl[maxSize + 1]; //Dùng cái đó có thể giúp khai báo mảng không bị lỗi.

    char snl[101];
    static int maxSize;
    char *reverse(const char *str);

    static SoNguyenLon *_snlMax;
    static bool SoSanhBeHonBang(const char *a, const char *b);
    static void Xoa0Odau(char *s);

public:
    SoNguyenLon();
    SoNguyenLon(long long number);
    SoNguyenLon(int value, int size);
    SoNguyenLon(const SoNguyenLon &other);
    SoNguyenLon(const char *str);
    SoNguyenLon operator+(const SoNguyenLon &other);
    SoNguyenLon operator-(const SoNguyenLon &other);

    friend ostream &operator<<(ostream &os, const SoNguyenLon &other);

    void CapNhatSNLMax();
    static SoNguyenLon SNLMax();
};

int SoNguyenLon::maxSize = 100;

SoNguyenLon *SoNguyenLon::_snlMax = nullptr;

SoNguyenLon SoNguyenLon::SNLMax()
{
    if (_snlMax == nullptr)
        return SoNguyenLon(); // Bắc buộc nhưng hợp lí
    return *_snlMax;
}
char *SoNguyenLon::reverse(const char *str)
{
    if (str == nullptr)
        return nullptr;
    int len = strlen(str);
    char *rev = new char[len + 1];

    int l = 0;
    int r = len - 1;
    while (l <= r)
    {
        rev[l] = str[r];
        rev[r] = str[l];
        r--;
        l++;
    }

    // cout << rev << '\n';

    rev[len] = '\0';
    return rev;
}

bool SoNguyenLon::SoSanhBeHonBang(const char *a, const char *b)
{
    int lenA = strlen(a);
    int lenB = strlen(b);

    if ((lenA < lenB) || (lenA == lenB && strcmp(a, b) <= 0))
    {
        return true;
    }

    return false;
}

SoNguyenLon::SoNguyenLon()
{
    strcpy_s(snl, sizeof(snl), "0");
    CapNhatSNLMax();
}

void SoNguyenLon::CapNhatSNLMax()
{

    if (_snlMax == nullptr || SoSanhBeHonBang(_snlMax->snl, snl))
    {
        _snlMax = this;
    }
}

SoNguyenLon::SoNguyenLon(const char *str) : SoNguyenLon()
{
    if (strcmp(snl, "") == 0)
    {
        return;
    }

    bool isValid = true;
    bool laSoAm = (snl[0] == '-') ? true : false;

    // Vì đề yêu cầu số âm thì cho bằng 0;
    if (!laSoAm)
    {
        for (int i = 0; i < strlen(snl); i++)
        {
            int digit = snl[i] - '0';
            if (digit < 0 || digit > 9)
            {
                isValid = false;
                break;
            }
        }
    }

    if (!isValid || laSoAm)
    {
        return;
    }

    strcpy_s(snl, sizeof(snl), str);

    CapNhatSNLMax();
}

SoNguyenLon::SoNguyenLon(long long number) : SoNguyenLon()
{
    if (number == 0)
    {
        return;
    }

    int tmp = number;
    int len = 0;
    while (tmp > 0)
    {
        len++;
        tmp /= 10;
    }

    int i = len - 1;
    while (number > 0)
    {
        snl[i--] = number % 10 + '0';
        number /= 10;
    }

    snl[len] = '\0';
    CapNhatSNLMax();
}

SoNguyenLon::SoNguyenLon(int value, int size) : SoNguyenLon()
{
    if (value <= 0 || size <= 0)
    {
        return;
    }

    if (size > maxSize)
    {
        size = maxSize;
    }

    if (value > 9)
        value = 9;

    for (int i = 0; i < size; i++)
    {
        snl[i] = value + '0';
    }

    snl[size] = '\0';
    CapNhatSNLMax();
}

SoNguyenLon::SoNguyenLon(const SoNguyenLon &other)
{
    strcpy_s(snl, sizeof(snl), other.snl);
}

SoNguyenLon SoNguyenLon::operator+(const SoNguyenLon &other)
{
    int lenA = strlen(snl);
    int lenB = strlen(other.snl);

    char *revA = reverse(snl);
    char *revB = reverse(other.snl);

    int maxLen = max(lenA, lenB);
    int carry = 0;

    char *res = new char[maxLen + 2];

    int i = 0;
    for (; i < maxLen; i++)
    {
        int digitA = (i < lenA) ? revA[i] - '0' : 0;
        int digitB = (i < lenB) ? revB[i] - '0' : 0;

        int digit = digitA + digitB + carry;

        res[i] = digit % 10 + '0';
        carry = digit / 10;
    }

    if (carry > 0)
    {
        res[i++] = carry + '0';
    }

    res[i] = '\0';

    char *revRes = reverse(res);
    SoNguyenLon kq(revRes);

    delete[] revA;
    delete[] revB;
    delete[] res;
    delete[] revRes;

    return kq;
}

SoNguyenLon SoNguyenLon::operator-(const SoNguyenLon &other)
{
    int lenA = strlen(snl);
    int lenB = strlen(other.snl);

    bool behonbang = SoSanhBeHonBang(snl, other.snl) ? true : false;

    if (behonbang)
    {
        return SoNguyenLon();
    }
    char *revA = reverse(snl);
    char *revB = reverse(other.snl);
    int maxLen = max(lenA, lenB);
    int carry = 0;

    char *res = new char[maxLen + 1];

    int i = 0;
    for (; i < maxLen; i++)
    {
        int digitA = (i < lenA) ? revA[i] - '0' : 0;
        int digitB = (i < lenB) ? revB[i] - '0' : 0;

        int digit = (digitA - digitB) - carry;

        res[i] = (digit + 10) % 10 + '0';
        carry = digit < 0 ? 1 : 0;
    }

    res[i] = '\0';

    char *revRes = reverse(res);
    SoNguyenLon kq(revRes);

    delete[] revA;
    delete[] revB;
    delete[] res;
    delete[] revRes;

    return kq;
}

SoNguyenLon operator-(const long long &number, const SoNguyenLon &other)
{
    return SoNguyenLon(number) - other;
}

SoNguyenLon operator+(const long long &number, const SoNguyenLon &other)
{
    return SoNguyenLon(number) + other;
}

ostream &operator<<(ostream &os, const SoNguyenLon &other)
{

    os << other.snl;
    return os;
}

int main()
{
    SoNguyenLon snl1;
    SoNguyenLon snl2(1234567);
    SoNguyenLon snl3(3, 14);
    SoNguyenLon snl4(9, 20);
    SoNguyenLon snl5 = snl3 - snl2;
    SoNguyenLon snl6 = 45678910 - snl2;
    SoNguyenLon snl7 = snl4 - snl3 + 123456789;
    cout << snl1 << endl
         << snl2 << endl
         << snl3 << endl;
    cout << snl4 << endl
         << snl5 << endl
         << snl6 << endl;
    cout << snl7 << endl
         << endl;

    cout << "SoNguyenLon Max: " << endl;
    cout << SoNguyenLon::SNLMax() << endl;
    system("pause");
    return 0;
}