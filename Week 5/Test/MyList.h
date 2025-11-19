#include <iostream>

using namespace std;

template <class T>
class MyList
{
private:
    struct Node
    {
        T data;
        Node *_pNext;
    };

    Node *_pHead, *_pTail;
    int _n;

    static Node *createNode(T value)
    {
        Node *node = new Node{value, nullptr};
        return node;
    }

public:
    ~MyList()
    {
        Clear();
    }

    MyList &operator=(const MyList &other)
    {
        if (this != &other)
        {
            Clear();
            Node *temp = other._pHead;
            while (temp != nullptr)
            {
                push_back(temp->data);
                temp = temp->_pNext;
            }
        }
        return *this;
    }

    MyList(const MyList &other)
    {
        _n = 0;
        _pHead = _pTail = nullptr;
        for (MyList<int>::Iterator it = other.begin(); it != other.end(); it++)
        {
            AddTail(*it);
        }
    }

    int size() const
    {
        return _n;
    }

    void Clear()
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
    class Iterator
    {
    private:
        Node *current_node;
        Iterator(Node *node) : current_node(node) {}
        friend class MyList;

    public:
        using iterator_category = forward_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

    public:
        reference operator*()
        {
            if (current_node == nullptr)
            {
                throw out_of_range("Error : out of range");
            }

            return current_node->data;
        }

        pointer operator->()
        {
            if (!current_node)
            {
                throw out_of_range("Error : out of range");
            }

            return &(current_node->data);
        }

        Iterator &operator++()
        {
            if (!current_node)
            {
                throw out_of_range("Error : out of range");
            }

            current_node = current_node->_pNext;

            return *this;
        }

        Iterator operator++(int)
        {
            if (!current_node)
            {
                throw out_of_range("Error: out of range");
            }

            Iterator temp = *this;
            current_node = current_node->_pNext;
            return temp;
        }

        bool operator==(const Iterator &other)
        {
            return current_node == other.current_node;
        }

        bool operator!=(const Iterator &other)
        {
            return !(*this == other);
        }
    };

public:
    MyList()
    {
        _pHead = _pTail = nullptr;
        _n = 0;
    }
    Iterator begin() const
    {
        return Iterator(_pHead);
    }

    Iterator end() const
    {
        return Iterator(nullptr);
    }

    void AddTail(T value)
    {
        Node *node = createNode(value);
        if (!node)
        {
            return;
        }
        _n++;
        if (_pHead == nullptr)
        {
            _pHead = _pTail = node;
            return;
        }

        _pTail->_pNext = node;
        _pTail = node;
    }

    void AddHead(T value)
    {
        Node *node = createNode(value);

        if (!node)
        {
            return;
        }

        _n++;

        if (_pHead == nullptr)
        {
            _pHead = _pTail = node;
            return;
        }

        node->_pNext = _pHead;
        _pHead = node;
    }

    void push_back(T value)
    {
        AddTail(value);
    }

    void insert(Iterator it, T value)
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
        Node *node = createNode(value);

        node->_pNext = it.current_node->_pNext;
        it.current_node->_pNext = node;
    }

    T operator[](int idx) const
    {
        if (idx < 0 || idx >= _n)
        {
            throw out_of_range("Out of range");
        }

        Node *node = _pHead;
        int pos = 0;
        while (pos < idx)
        {
            node = node->_pNext;
            pos++;
        }

        return node->data;
    }

    T back() const
    {
        return _pTail->data;
    }
};