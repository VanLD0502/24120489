#include <iostream>
#include "LinkedList.h"
// Em không biết bài này nên dùng lại LinkedList ở câu 4 ko.
using namespace std;

class SoNguyenLon
{
private:
    LinkedList<int> list;

    SoNguyenLon multiplyWithOneDigit(int digit) const;
    void removeLeadingZeros();

public:
    SoNguyenLon();
    SoNguyenLon(long long number);
    SoNguyenLon(int number, int size);
    SoNguyenLon(const SoNguyenLon &other);
    SoNguyenLon(const LinkedList<int> &linkedlist);

    bool operator<=(const SoNguyenLon &other) const;
    SoNguyenLon operator+(const SoNguyenLon &other) const;
    SoNguyenLon operator-(const SoNguyenLon &other) const;
    SoNguyenLon operator*(const SoNguyenLon &other) const;
    friend ostream &operator<<(ostream &os, const SoNguyenLon &other);
};

SoNguyenLon::SoNguyenLon()
{
    list.AddTail(0);
}

SoNguyenLon::SoNguyenLon(long long number)
{
    if (number == 0)
    {
        list.AddTail(0);
        return;
    }
    while (number > 0)
    {
        int digit = number % 10;
        list.AddHead(digit);
        number /= 10;
    }
}

SoNguyenLon::SoNguyenLon(int number, int size)
{
    if (size <= 0 || number <= 0)
    {
        list.AddTail(0);
        return;
    }
    if (number > 10)
        number = 9;

    for (int i = 0; i < size; i++)
    {
        list.AddTail(number);
    }
}
SoNguyenLon::SoNguyenLon(const SoNguyenLon &other)
{
    list = other.list;
}

SoNguyenLon::SoNguyenLon(const LinkedList<int> &linkedlist)
{
    list = linkedlist;
}

bool SoNguyenLon::operator<=(const SoNguyenLon &other) const
{
    if (list.getSize() < other.list.getSize())
    {
        return true;
    }
    if (list.getSize() > other.list.getSize())
    {
        return false;
    }

    // Hai thang co size bang nhau
    for (int i = 0; i < this->list.getSize(); i++)
    {
        Node<int> *A = list.get(i);
        Node<int> *B = other.list.get(i);
        // Chac chan A,B khac nullptr
        if (A->info > B->info)
        {
            return false;
        }
    }

    return true;
}

SoNguyenLon SoNguyenLon::multiplyWithOneDigit(int digit) const
{
    LinkedList<int> revA = list.createReverse();
    LinkedList<int> result;
    int carry = 0;
    for (int i = 0; i < revA.getSize(); i++)
    {
        Node<int> *node = revA.get(i);
        int prod = node->info * digit + carry;
        result.AddHead(prod % 10);
        carry = prod / 10;
    }

    if (carry > 0)
        result.AddHead(carry);

    if (result.getSize() == 0)
    {
        result.AddHead(0);
    }

    // SỬA: Tạo kết quả và dọn dẹp
    SoNguyenLon rs(result);
    rs.removeLeadingZeros(); // Quan trọng! (123 * 0 = 000 -> 0)
    return rs;
}

SoNguyenLon SoNguyenLon::operator+(const SoNguyenLon &other) const
{
    LinkedList<int> revA = list.createReverse();
    LinkedList<int> revB = other.list.createReverse();

    int lenA = revA.getSize();
    int lenB = revB.getSize();

    int carry = 0;
    // 999
    // 222
    LinkedList<int> newList;
    // Ở đây thì lenA >= lenB
    for (int i = 0; i < max(lenA, lenB); i++)
    {
        Node<int> *nodeA = revA.get(i);
        Node<int> *nodeB = revB.get(i);

        int digitA = (nodeA == nullptr) ? 0 : nodeA->info;
        int digitB = (nodeB == nullptr) ? 0 : nodeB->info;
        int digit = digitA + digitB + carry;
        newList.AddHead((digit) % 10);
        carry = (digit) / 10;
    }

    if (carry > 0)
    {
        newList.AddHead(carry);
    }
    SoNguyenLon kq(newList);
    kq.removeLeadingZeros();
    return kq;
}

SoNguyenLon SoNguyenLon::operator-(const SoNguyenLon &other) const
{
    if (this->operator<=(other))
    {
        return SoNguyenLon();
    }
    LinkedList<int> revA = list.createReverse();
    LinkedList<int> revB = other.list.createReverse();

    int lenA = revA.getSize();
    int lenB = revB.getSize();

    int carry = 0;
    LinkedList<int> newList;
    for (int i = 0; i < max(lenA, lenB); i++)
    {
        Node<int> *nodeA = revA.get(i);
        Node<int> *nodeB = revB.get(i);

        int digitA = (nodeA == nullptr) ? 0 : nodeA->info;
        int digitB = (nodeB == nullptr) ? 0 : nodeB->info;
        int digit = digitA - digitB + carry;
        newList.AddHead((digit + 10) % 10);
        carry = digit < 0 ? -1 : 0;
    }

    SoNguyenLon kq(newList);
    kq.removeLeadingZeros();
    return kq;
}

SoNguyenLon SoNguyenLon::operator*(const SoNguyenLon &other) const
{
    LinkedList<int> revB = other.list.createReverse();
    SoNguyenLon res;
    int zeros = 0;

    for (int i = 0; i < revB.getSize(); i++)
    {
        int digit = revB.get(i)->info;
        SoNguyenLon mul = multiplyWithOneDigit(digit);

        for (int j = 0; j < zeros; j++)
            mul.list.AddTail(0);

        res = res + mul;
        zeros++;
    }

    return res;
}

SoNguyenLon operator-(const long long number, const SoNguyenLon &other)
{
    return SoNguyenLon(number) - other;
}

SoNguyenLon operator+(const long long number, const SoNguyenLon &other)
{
    return other + SoNguyenLon(number);
}

SoNguyenLon operator*(const long long number, const SoNguyenLon &other)
{
    return other * SoNguyenLon(number);
}

void SoNguyenLon::removeLeadingZeros()
{
    while (list.getSize() > 1 && list.get(0)->info == 0)
    {
        Node<int> *node = list.RemoveHead();

        if (node)
            delete node;
    }
}

ostream &operator<<(ostream &os, const SoNguyenLon &other)
{
    cout << other.list;
    return os;
}
int main()
{
    // SoNguyenLon snl1;
    // SoNguyenLon snl2(44667733);
    // SoNguyenLon snl3(5, 9);
    // SoNguyenLon snl4(7, 30);
    // SoNguyenLon snl5 = snl3 - snl2;
    // SoNguyenLon snl6 = 1098765432 - snl2;
    // SoNguyenLon snl7 = snl4 - snl3 + 123456789;
    // SoNguyenLon snl8 = snl2 * snl3;
    // cout << snl1 << endl
    //      << snl2 << endl
    //      << snl3 << endl;
    // cout << snl4 << endl
    //      << snl5 << endl
    //      << snl6 << endl;
    // cout << snl7 << endl
    //      << snl8 << endl;

    char *a = new char[100];
    const char *b = "Hello";
    strcpy_s(a, 100, b);
    cout << a << endl;
    system("pause");
    return 0;
}

// 24815407197406815