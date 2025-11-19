#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class Vector
{
private:
    T *data;
    size_t size;
    size_t opacity;

public:
    class Iterator
    {
    private:
        T *cur;
        Iterator(T *data) : cur(data) {}
        friend class Vector;

    public:
        using iterator_category = forward_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

    public:
        T &operator*()
        {
            if (cur == nullptr)
            {
                throw out_of_range("Out of range");
            }

            return *cur;
        }

        T *operator->()
        {
            if (cur == nullptr)
            {
                throw out_of_range("Out of range");
            }

            return cur;
        }

        Iterator &operator++()
        {
            cur = cur + 1;
            return *this;
        }

        Iterator operator++(int)
        {

            Iterator temp(cur);
            cur = cur + 1;
            return temp;
        }

        Iterator &operator--()
        {
            cur = cur - 1;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator temp(cur);
            cur = cur - 1;
            return temp;
        }

        Iterator operator+(int n)
        {
            return Iterator(cur + n);
        }

        Iterator operator-(int n)
        {
            return Iterator(cur - n);
        }

        bool operator==(const Iterator &other)
        {
            return cur == other.cur;
        }

        bool operator!=(const Iterator &other)
        {
            return cur != other.cur;
        }
    };

    Vector()
    {
        data = nullptr;
        size = 0;
        opacity = 1;
    }

    ~Vector()
    {
        clear();
    }

    Vector(const Vector &other)
    {
        size = other.size;
        opacity = other.opacity;
        data = new T[opacity];

        for (int i = 0; i < other.size; i++)
        {
            data[i] = other.data[i];
        }
    }
    T &operator[](int idx)
    {

        if (idx < 0 || idx >= size)
        {
            throw out_of_range("Out of range");
        }
        return data[idx];
    }

    void push_back(T value)
    {
        if (data == nullptr)
        {
            data = new T[opacity]; // opacity = 1
        }
        size_t newSize = size + 1;

        if (newSize > opacity)
        {
            opacity = opacity * 2;

            T *newData = new T[opacity];

            for (int i = 0; i < size; i++)
            {
                newData[i] = data[i];
            }
            delete[] data;

            data = newData;
        }

        data[size] = value;
        size = newSize;
    }

    void pop_back()
    {
        if (size <= 0)
        {
            return;
        }
        size--;
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            clear();
            data = new T[other.opacity];
            for (int i = 0; i < other.size; i++)
            {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    Iterator begin()
    {
        return Iterator(data);
    }

    Iterator end()
    {
        return Iterator(data + size);
    }

    T &back()
    {
        return *(data + size - 1);
    }

    void clear()
    {
        delete[] data;
        data = nullptr;
        size = 0;
        opacity = 1;
    }

    int getSize() const
    {
        return size;
    }
};

void print(int a)
{
    cout << a << " ";
}

int main()
{
    Vector<int> v;
    Vector<int> b;
    v.push_back(0);
    v.push_back(2);
    v.push_back(3);
    v[1] = 10;
    b = v;
    // cout << v[1] << '\n';
    // cout << v.back() << '\n';
    // v.pop_back();
    // cout << v.back() << '\n';
    Vector<int> c(v);

    for (Vector<int>::Iterator it = c.begin(); it != c.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    for (Vector<int>::Iterator it = c.end() - 1; it != c.begin(); it--)
    {
        cout << *it << " ";
    }
    cout << endl;
    for (int i = 0; i < c.getSize(); i++)
    {
        cout << c[i] << ' ';
    }
    return 0;
}