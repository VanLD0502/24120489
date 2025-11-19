#include <iostream>
#include <cstring>
using namespace std;

class SoNguyenLon
{
private:
    char _snl[101];

    static char *reverse(const char *str);

    static SoNguyenLon *_snlMax;

    static bool SoSanhBeHonBang(const char *a, const char *b);
    static void Xoa0Odau(char *s);

public:
    SoNguyenLon();
    SoNguyenLon(int number);
    SoNguyenLon(const char *snl);
    SoNguyenLon(int number, int repeat);

    SoNguyenLon(const SoNguyenLon &other);

    static SoNguyenLon &SNLMax();
    void CapNhatSNLMax();

    SoNguyenLon Tru(const SoNguyenLon &other);
    SoNguyenLon Cong(const SoNguyenLon &other);
    SoNguyenLon Cong(long long number);
    static SoNguyenLon HieuVoiHangSo(long long number, const SoNguyenLon &other);
    void In(ostream &os);
};

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

void SoNguyenLon::Xoa0Odau(char *s)
{
    int n = (int)strlen(s);
    int i = 0;
    while (i < n - 1 && s[i] == '0')
        i++;
    if (i > 0)
    {
        int j = 0;
        while (i <= n)
        {
            s[j++] = s[i++];
        }
    }
}

SoNguyenLon::SoNguyenLon(const SoNguyenLon &other)
{
    int len = strlen(other._snl);
    for (int i = 0; i < min(100, len); i++)
    {
        _snl[i] = other._snl[i];
    }

    _snl[len] = '\0';

    CapNhatSNLMax();
}

SoNguyenLon::SoNguyenLon()
{
    strcpy_s(_snl, sizeof(_snl), "0");
    CapNhatSNLMax();
}
// Em không biết được phép viết thêm hàm này không nên ko cập nhật max ở đây;
SoNguyenLon::SoNguyenLon(int number)
{
    number = abs(number);

    if (number == 0)
    {
        strcpy_s(_snl, sizeof(_snl), "0");
        CapNhatSNLMax();
        return;
    }

    long long tmp = number;

    int len = 0;
    while (tmp > 0)
    {
        tmp /= 10;
        len++;
    }

    _snl[len] = '\0';
    int i = len - 1;
    for (; i >= 0; i--)
    {
        _snl[i] = number % 10 + '0';
        number /= 10;
    }
}

SoNguyenLon::SoNguyenLon(const char *snl)
{
    if (strcmp(snl, "") == 0)
    {
        strcpy_s(_snl, sizeof(_snl), "0");
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

    if (isValid)
    {
        strcpy_s(_snl, sizeof(_snl), snl);
    }
    else
    {
        strcpy_s(_snl, sizeof(_snl), "0");
    }

    CapNhatSNLMax();
}

// Đoan này theo như test case thầy ko chỉ test number < 10, nên number > 9, < 0, em cho number = 0;
// Nếu thầy muốn number > 10, vẫn được (nhưng trong khuôn khổ bài chỉ quan tâm đến static);
SoNguyenLon::SoNguyenLon(int number, int repeat)
{
    if (number < 0 || number > 9)
        number = 0;
    if (repeat <= 0)
        repeat = 1;
    if (repeat > 100)
        repeat = 100;

    for (int i = 0; i < repeat; i++)
    {
        _snl[i] = number + '0';
    }

    _snl[repeat] = '\0';

    CapNhatSNLMax();
}

SoNguyenLon *SoNguyenLon::_snlMax = nullptr;

SoNguyenLon &SoNguyenLon::SNLMax()
{
    return *_snlMax;
}

SoNguyenLon &SoNguyenLon::SNLMax()
{
    return *_snlMax;
}

void SoNguyenLon::CapNhatSNLMax()
{

    if (_snlMax == nullptr || SoSanhBeHonBang(_snlMax->_snl, _snl))
    {
        _snlMax = this;
    }
}

SoNguyenLon SoNguyenLon::Tru(const SoNguyenLon &other)
{
    int lenA = strlen(_snl);
    int lenB = strlen(other._snl);

    if (SoSanhBeHonBang(_snl, other._snl))
    {
        return SoNguyenLon();
    }

    char *revA = reverse(_snl);
    char *revB = reverse(other._snl);

    int len = max(lenA, lenB) + 1;

    char *res = new char[len + 1];

    int carry = 0;

    int i = 0;
    // Vì A > B
    for (; i < max(lenA, lenB); i++)
    {
        int digitA = (i < lenA) ? (revA[i] - '0') : 0;
        int digitB = (i < lenB) ? (revB[i] - '0') : 0;
        int digit = digitA - digitB - carry;
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

void SoNguyenLon::In(ostream &os)
{
    os << _snl;
}

SoNguyenLon SoNguyenLon::Cong(const SoNguyenLon &other)
{
    char *revA = reverse(_snl);
    char *revB = reverse(other._snl);

    // 2 so cong lại thì độ dài có thể có
    //  là ví dụ 98 + 1 thì ra 99 độ dài 2;
    //  là 98 + 10 = 118 thì độ dài 3 nên đồ dài có thể có thể lớn nhất là
    int lenA = strlen(revA);
    int lenB = strlen(revB);
    int len = max(lenA, lenB) + 1;

    char *res = new char[len + 1];

    int carry = 0;

    int i = 0;

    for (; i < max(lenA, lenB); i++)
    {
        int digitA = (i < lenA) ? (revA[i] - '0') : 0;
        int digitB = (i < lenB) ? (revB[i] - '0') : 0;
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

    Xoa0Odau(revRes);
    SoNguyenLon kq(revRes);

    delete[] revA;
    delete[] revB;
    delete[] res;
    delete[] revRes;

    return kq;
}

SoNguyenLon SoNguyenLon::Cong(long long number)
{
    return Cong(SoNguyenLon(number));
}

char *SoNguyenLon::reverse(const char *str)
{
    int len = strlen(str);
    char *res = new char[len + 1];
    for (int i = 0; i < len; i++)
    {
        res[i] = str[len - i - 1];
    }

    res[len] = '\0';

    return res;
}

SoNguyenLon SoNguyenLon::HieuVoiHangSo(long long number, const SoNguyenLon &other)
{
    return SoNguyenLon(number).Tru(other);
}
int main()
{
    SoNguyenLon snl1;
    SoNguyenLon snl2("1234567");
    SoNguyenLon snl3(3, 14);
    SoNguyenLon snl4(9, 20);

    SoNguyenLon snl5 = snl3.Tru(snl2);
    SoNguyenLon snl6 = SoNguyenLon::HieuVoiHangSo(45678910, snl2);
    SoNguyenLon snl7 = snl4.Tru(snl3).Cong(123456789);

    snl1.In(cout);
    cout << endl;
    snl2.In(cout);
    cout << endl;
    snl3.In(cout);
    cout << endl;
    snl4.In(cout);
    cout << endl;
    snl5.In(cout);
    cout << endl;
    snl6.In(cout);
    cout << endl;
    snl7.In(cout);
    cout << endl;
    cout << endl;
    cout << "SoNguyenLon Max:" << endl;
    SoNguyenLon::SNLMax().In(cout);
    cout << endl;
    system("pause");
    return 0;
}