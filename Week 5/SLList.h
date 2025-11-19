#include <iostream>
using namespace std;

// Dành cho bài 3,4;
template <class T>
class SLList
{
private:
    struct Node
    {
        T _info;
        Node *_pNext;
    };

    Node *_pHead, *_pTail;
    int _n;
    static Node *CreateNode(const T &value)
    {
        Node *node = new Node{value, nullptr};
        return node;
    }

public:
    class Iterator;
    using iterator = Iterator;
    SLList();
    SLList(const SLList<T> &other);
    ~SLList();

    void AddHead(const T &);
    void AddTail(const T &);
    void RemoveHead();
    void RemoveTail();
    void Clear();

    Iterator begin() const
    {
        return Iterator(_pHead);
    }

    Iterator end() const
    {
        return Iterator(nullptr);
    }

    T operator[](int idx) const;
    SLList &operator=(const SLList &other);
    friend ostream &operator<<(ostream &os, const SLList<T> &ll)
    {
        SLList<T>::Node *node = ll._pHead;

        while (node != nullptr)
        {
            os << node->_info << ", ";
            node = node->_pNext;
        }

        return os;
    }

    void insert(Iterator it, T value);
    void push_back(T value);
    T back();
    int size() const
    {
        return _n;
    }
};

template <class T>
SLList<T>::SLList()
{
    _pHead = _pTail = nullptr;
    _n = 0;
}

template <class T>
SLList<T>::SLList(const SLList<T> &other) : SLList<T>()
{
    for (SLList<T>::iterator it = other.begin(); it != other.end(); ++it)
    {
        AddTail(*it);
    }
}

template <class T>
SLList<T>::~SLList()
{
    Clear();
}

template <class T>
void SLList<T>::Clear()
{
    Node *node = _pHead;

    while (node != nullptr)
    {
        Node *tmp = node;

        node = node->_pNext;
        delete tmp;
    }

    _pHead = _pTail = nullptr;
    _n = 0;
}

template <class T>
void SLList<T>::AddTail(const T &value)
{
    Node *node = CreateNode(value);

    if (node == nullptr)
    {
        return;
    }

    if (_pHead == nullptr)
    {
        _pHead = _pTail = node;
        _n++;
        return;
    }

    _pTail->_pNext = node;
    _pTail = node;
    _n++;
}

template <class T>
void SLList<T>::AddHead(const T &value)
{
    Node *node = CreateNode(value);

    if (node == nullptr)
        return;

    if (_pHead == nullptr)
    {
        _pHead = _pTail = node;
        _n++;
        return;
    }

    node->_pNext = _pHead;
    _pHead = node;
    _n++;
}

template <class T>
void SLList<T>::RemoveHead()
{
    if (_pHead == nullptr)
    {
        return;
    }

    Node *tmp = _pHead;
    _pHead = _pHead->_pNext;
    delete tmp;
    _n--;

    if (_pHead == nullptr)
    {
        _pTail = nullptr;
    }
}

template <class T>
void SLList<T>::RemoveTail()
{
    if (_pHead == nullptr)
    {
        return;
    }

    _n--;
    if (_pHead == _pTail)
    {
        delete _pHead;
        _pHead = _pTail = nullptr;
        return;
    }

    Node *node = _pHead;
    while (node->_pNext != _pTail)
    {
        node = node->_pNext;
    }

    delete _pTail;
    _pTail = node;
    _pTail->_pNext = nullptr;
}

template <class T>
T SLList<T>::operator[](int idx) const
{
    if (idx >= _n || idx < 0)
    {
        throw out_of_range("Error: Out of range");
    }

    int pos = 0;
    Node *node = _pHead;
    while (pos < idx)
    {
        pos++;
        node = node->_pNext;
    }

    return node->_info;
}

template <class T>
SLList<T> &SLList<T>::operator=(const SLList &other)
{
    if (this == &other)
    {
        return *this;
    }

    Clear();

    for (Iterator it = other.begin(); it != other.end(); it++)
    {
        AddTail(*it);
    }

    return *this;
}

template <class T>
void SLList<T>::insert(Iterator it, T value)
{
    if (it == begin())
    {
        AddHead(value);
        return;
    }

    if (it == end())
    {
        AddTail(value);
        return;
    }

    Node *node = _pHead;

    while (node && node->_pNext != it.current_node)
    {
        node = node->_pNext;
    }

    if (node != nullptr)
    {
        Node *newNode = CreateNode(value);

        if (newNode == nullptr)
            return;

        newNode->_pNext = node->_pNext;
        node->_pNext = newNode;
        _n++;
    }
}

template <class T>
void SLList<T>::push_back(T value)
{
    AddTail(value);
}

template <class T>
T SLList<T>::back()
{
    if (_pHead == nullptr)
    {
        throw std::out_of_range("Error: Out of range");
    }
    return _pTail->_info;
}
template <class T>
class SLList<T>::Iterator
{
public:
    using iterator_category = forward_iterator_tag;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

private:
    Node *current_node;
    Iterator(Node *node) : current_node(node) {}
    friend class SLList<T>;

public:
    Iterator() : current_node(nullptr) {}
    reference operator*() const
    {
        if (!current_node)
        {
            throw out_of_range("Dereferencing end() of null iterator");
        }

        return current_node->_info;
    }

    pointer operator->() const
    {
        if (!current_node)
        {
            throw out_of_range("Accessing member via end() or null iterator");
        }

        return &(current_node->_info);
    }

    Iterator &operator++()
    {
        if (current_node)
        {
            current_node = current_node->_pNext;
        }
        else
        {
            throw out_of_range("Incrementing end() or null iterator");
        }

        return *this;
    }

    Iterator operator++(int)
    {
        if (!current_node)
        {
            throw out_of_range("Incrementing end() or null iterator");
        }

        Iterator temp = *this;
        current_node = current_node->_pNext;
        return temp;
    }

    bool operator==(const Iterator &other) const
    {
        return current_node == other.current_node;
    }

    bool operator!=(const Iterator &other) const
    {
        return !(*this == other);
    }
};