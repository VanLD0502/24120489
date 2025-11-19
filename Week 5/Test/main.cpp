#include <iostream>
#include "MyList.h"
#include <cstring>
#include <vector>
using namespace std;

class SNL
{
private:
    MyList<int> list;
    void printReverse(ostream &os, MyList<int>::Iterator it) const;

    void Pow10(int i);

public:
    SNL();
    SNL(const char *str);
    SNL(const SNL &other);
    SNL(const long long &n);
    bool operator<=(const SNL &other);
    bool operator>=(const SNL &other);
    bool operator<(const SNL &other);
    SNL operator+(const SNL &other);
    SNL operator-(const SNL &other);
    SNL operator*(const SNL &other);
    SNL operator/(const SNL &other);
    friend ostream &operator<<(ostream &os, const SNL &snl);
};

void SNL::printReverse(ostream &os, MyList<int>::Iterator it) const
{
    if (it == list.end())
    {
        return;
    }

    auto curIt = it;
    it++;
    printReverse(os, it);
    os << *curIt;
}

void SNL::Pow10(int i)
{
    for (int j = 0; j < i; j++)
    {
        list.insert(list.begin(), 0);
    }
}

SNL::SNL()
{
    list.push_back(0);
}

SNL::SNL(const char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            cerr << "Loi";
            return;
        }

        list.insert(list.begin(), str[i] - '0');
    }
}
SNL::SNL(const SNL &other)
{
    list = other.list;
}
SNL::SNL(const long long &n)
{
    int temp = n;
    do
    {
        list.push_back(temp % 10);
        temp /= 10;
    } while (temp > 0);
}
bool SNL::operator<=(const SNL &other)
{
    if (list.size() > other.list.size())
    {
        return false;
    }

    if (list.size() < other.list.size())
    {
        return true;
    }

    for (int i = list.size() - 1; i >= 0; i--)
    {
        if (list[i] > other.list[i])
            return false;
        if (list[i] < other.list[i])
            return true;
    }

    return true;
}
bool SNL::operator>=(const SNL &other)
{
    if (list.size() > other.list.size())
    {
        return true;
    }

    if (list.size() < other.list.size())
    {
        return false;
    }

    for (int i = list.size() - 1; i >= 0; i--)
    {
        if (list[i] > other.list[i])
            return true;
        if (list[i] < other.list[i])
            return false;
    }

    return true;
}
bool SNL::operator<(const SNL &other)
{
    if (list.size() > other.list.size())
    {
        return false;
    }

    if (list.size() < other.list.size())
    {
        return true;
    }

    for (int i = list.size() - 1; i >= 0; i--)
    {
        if (list[i] > other.list[i])
            return false;
        if (list[i] < other.list[i])
            return true;
    }

    return false;
}
SNL SNL::operator+(const SNL &other)
{
    MyList<int>::Iterator itA = list.begin();
    MyList<int>::Iterator itB = other.list.begin();

    int nho = 0;

    SNL res;
    res.list.Clear();
    while (itA != list.end() || itB != other.list.end())
    {
        int digitA = (itA == list.end()) ? 0 : *itA;
        int digitB = (itB == other.list.end()) ? 0 : *itB;

        int digit = digitA + digitB + nho;

        res.list.push_back(digit % 10);

        nho = digit / 10;

        if (itA != list.end())
            itA++;
        if (itB != other.list.end())
            ++itB;
    }

    if (nho > 0)
    {
        res.list.push_back(1);
    }

    return res;
}

SNL SNL::operator-(const SNL &other)
{
    if (*this <= other)
    {
        return SNL();
    }

    // Thang A luon lon hon bang B
    MyList<int>::Iterator itA = list.begin();
    MyList<int>::Iterator itB = other.list.begin();
    int nho = 0;
    SNL res;
    res.list.Clear();
    while (itA != list.end() || itB != other.list.end())
    {
        int digitA = (itA == list.end()) ? 0 : *itA;
        int digitB = (itB == other.list.end()) ? 0 : *itB;

        int digit = digitA - digitB - nho;

        res.list.push_back((digit + 10) % 10);

        nho = digit < 0 ? 1 : 0;

        if (itA != list.end())
            itA++;
        if (itB != other.list.end())
            ++itB;
    }

    return res;
}

SNL SNL::operator*(const SNL &other)
{
    int nho = 0;
    SNL res;
    res.list.Clear();

    // 374 255
    // 473
    // 552
    int cnt = 0;
    for (auto itA = list.begin(); itA != list.end(); itA++)
    {
        SNL temp;
        temp.list.Clear();
        int nho = 0;
        for (auto itB = other.list.begin(); itB != other.list.end(); itB++)
        {
            int digit = *itA * *itB + nho;
            temp.list.push_back(digit % 10);
            nho = digit / 10;
        }

        if (nho > 0)
        {
            temp.list.push_back(nho);
        }
        temp.Pow10(cnt);

        res = res + temp;
        cnt++;
    }

    return res;
}

SNL SNL::operator/(const SNL &other)
{
    SNL temp;
    temp.list.Clear();

    if (other.list.size() == 1 && other.list.back() == 0)
    {
        throw "Loi";
    }
    if (*this <= other)
    {
        return SNL("1");
    }

    SNL cur;
    cur.list.Clear();
    SNL kq;
    kq.list.Clear();
    // 52
    // 25
    for (int i = list.size() - 1; i >= 0; i--)
    {
        cur.list.AddHead(list[i]);
        cout << "L: " << list[i] << endl;

        if (cur < other)
        {
            continue;
        }

        int thuong = 0;
        for (int j = 1; j <= 9; j++)
        {
            SNL temp = (SNL(j) * other);

            if (cur >= temp)
            {
                cout << "H " << cur << " " << temp << endl;
                thuong = j;
            }
            else
            {
                kq.list.AddHead(thuong);
                break;
            }
        }

        cur = cur - SNL(thuong) * other;
    }
    return kq;
}
// 225
// 13
// 552

// 25
//  31
int main()
{
    // SNL a("374");
    // SNL b("255");
    // cout << a + b << endl;
    // cout << a - b << endl;
    // cout << 374 * 255 << endl;
    // cout << a * b << endl;
    // cout << SNL("225") / SNL("13") << endl;
    // cout << 225 / 13;
    vector<int> v;
    v.push_back(2);

    cout << *(v.end());
    cout << *(--v.end());

    return 0;
}

ostream &operator<<(ostream &os, const SNL &snl)
{
    snl.printReverse(os, snl.list.begin());
    return os;
}
