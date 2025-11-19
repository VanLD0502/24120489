#include <iostream>
#include <cstring>
using namespace std;

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

    void free();

public:
    LinkedList<T> createReverse() const;
    LinkedList();
    ~LinkedList();

    Node<T> *AddHead(const T &);
    Node<T> *AddTail(const T &);
    Node<T> *RemoveHead();
    Node<T> *RemoveTail();

    T &operator[](const int &);

    int getSize() const;

    // Linklist khá đặt biệt là nó dùng con trỏ nên mình có thể tận dụng nó khi xử lí out of range giống như ngôn ngữ khác như js thì nó sẽ là undefined
    // undefine có thể quy ra 0 nếu xử lí cẩn thận
    // Mục tiêu lấy con trỏ trong bài bài 5 nếu nullptr thì trả về giá trị 0 (mình tự code phần này)
    Node<T> *get(int idx) const;

    LinkedList &operator=(const LinkedList &other);
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
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &other)
{
    if (&other == this)
    {
        return *this;
    }

    this->free();

    Node<T> *node = other._pHead;

    while (node != nullptr)
    {
        AddTail(node->info);
        node = node->pNext;
    }

    return *this;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    cout << "LinkedList duoc huy";
    free();
}
template <class T>
Node<T> *LinkedList<T>::CreateNode(const T &value)
{
    Node<T> *node = new Node<T>{value, nullptr};

    return node;
}

template <class T>
void LinkedList<T>::free()
{
    _n = 0;
    Node<T> *node = _pHead;

    while (_pHead != nullptr)
    {
        _pHead = _pHead->pNext;
        delete node;
        node = _pHead;
    }
    _pHead = _pTail = nullptr;
    _n = 0;
}

template <class T>
LinkedList<T> LinkedList<T>::createReverse() const
{
    Node<T> *node = _pHead;

    LinkedList<T> newLinkedList;
    while (node != nullptr)
    {
        newLinkedList.AddHead(node->info);
        node = node->pNext;
    }

    return newLinkedList;
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
    Node<T> *node = _pHead;

    if (i < 0 || i >= _n)
    {
        throw out_of_range("Error: Index out of range");
    }
    int pos = 0;

    while (pos < i)
    {
        node = node->pNext;
        pos++;
    }

    return node->info;
}

template <class T>
int LinkedList<T>::getSize() const
{
    return _n;
}

template <class T>
Node<T> *LinkedList<T>::get(int idx) const
{
    if (idx < 0 || idx >= _n)
    {
        return nullptr;
    }
    int pos = 0;
    Node<T> *node = _pHead;
    while (pos < idx)
    {
        node = node->pNext;
        pos++;
    }

    return node;
}

template <class U>
ostream &operator<<(ostream &os, const LinkedList<U> &ll)
{
    Node<U> *node = ll._pHead;

    while (node != nullptr)
    {
        os << node->info;
        node = node->pNext;
    }

    return os;
}