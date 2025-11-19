#include <iostream>
#include "CString.h"
#include <cstring>
using namespace std;

// LinkedList

template <class T>
struct Node
{
    T info;
    Node *pNext;
};

template <class T>
class LinkedList
{
private:
    Node<T> *_pHead, *_pTail;
    int _n;

    static Node<T> *CreateNode(const T &);

public:
    LinkedList();
    ~LinkedList();

    Node<T> *AddHead(const T &);
    Node<T> *AddTail(const T &);
    Node<T> *RemoveHead();
    Node<T> *RemoveTail();

    T &operator[](const int &);
    template <class U>
    friend ostream &operator<<(ostream &, const LinkedList<U> &ll);
};

template <class T>
LinkedList<T>::LinkedList()
{
    _pHead = _pTail = nullptr;
    _n = 0;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    _n = 0;
    Node<T> *node = _pHead;

    while (_pHead != nullptr)
    {
        _pHead = _pHead->pNext;
        delete node;
        node = _pHead;
    }
}
template <class T>
Node<T> *LinkedList<T>::CreateNode(const T &value)
{
    Node<T> *node = new Node<T>{value, nullptr};

    return node;
}

template <class T>
Node<T> *LinkedList<T>::AddTail(const T &value)
{
    Node<T> *node = CreateNode(value);

    if (node == nullptr)
    {
        return nullptr;
    }

    if (_pHead == nullptr)
    {
        _pHead = _pTail = node;
        _n++;
        return node;
    }

    _pTail->pNext = node;
    _pTail = node;
    _n++;

    return node;
}

template <class T>
Node<T> *LinkedList<T>::AddHead(const T &value)
{
    Node<T> *node = CreateNode(value);

    if (node == nullptr)
    {
        return nullptr;
    }

    if (_pHead == nullptr)
    {
        _pHead = _pTail = node;
        _n++;
        return node;
    }

    node->pNext = _pHead;
    _pHead = node;
    _n++;

    return node;
}

template <class T>
Node<T> *LinkedList<T>::RemoveHead()
{
    if (_pHead == nullptr)
    {
        return nullptr;
    }

    Node<T> *node = _pHead;
    _pHead = _pHead->pNext;
    _n--;

    if (_pHead == nullptr)
    {
        _pTail = nullptr;
    }

    return node;
}

template <class T>
Node<T> *LinkedList<T>::RemoveTail()
{
    if (_pHead == nullptr)
    {
        return nullptr;
    }
    Node<T> *node = _pHead;
    // Chỉ 1 node
    if (_pHead == _pTail)
    {
        _pHead = _pTail = nullptr;
        _n = 0;
        return node;
    }
    while (node && node->pNext != _pTail)
    {
        node = node->pNext;
    }

    Node<T> *temp = _pTail;
    _pTail = node;
    _pTail->pNext = nullptr;
    _n--;

    return temp;
}

template <class T>
T &LinkedList<T>::operator[](const int &i)
{
    // Thầy bảo đoạn này không chạy được nên xóa đành chịu.
    // Em ko bit cái này có gây lỗi trên máy thầy ko
    if (i < 0 || i >= _n)
    {
        throw out_of_range("Error: Index out of range\n");
    }

    Node<T> *node = _pHead;

    if (_pHead == nullptr)
    {
        // Xu li lỗi vì không dùng được throw exception
        // throw exception("Dont access this indices");
        throw out_of_range("Dont access this indices\n");
    }
    int pos = 0;

    while (pos < i)
    {
        node = node->pNext;
        pos++;
    }

    return node->info;
}

template <class U>
ostream &operator<<(ostream &os, const LinkedList<U> &ll)
{
    Node<U> *node = ll._pHead;

    while (node != nullptr)
    {
        os << node->info << ", ";
        node = node->pNext;
    }

    return os;
}