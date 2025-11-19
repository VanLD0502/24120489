#include <vector>
#include <iostream>
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

            return cur;
        }

        T *operator->()
        {
            if (cur == nullptr)
            {
                throw out_of_range("Out of range");
            }

            return &cur;
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
    };

    Vector()
    {
        data = nullptr;
        size = 0;
        opacity = 1;
    }
    T operator[](int idx)
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
};

int main()
{
    Vector<int> v;
    v.push_back(0);
    v.push_back(2);

    cout << v[1];
    return 0;
}