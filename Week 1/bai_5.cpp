#include <iostream>

using namespace std;

class MangSoNguyen
{
private:
    int *arr;
    int size;

public:
    MangSoNguyen();
    MangSoNguyen(int size);
    MangSoNguyen(int a[], int size);
    MangSoNguyen(const MangSoNguyen &other);

    ~MangSoNguyen();

    void Xuat();
};

MangSoNguyen::MangSoNguyen()
{
    arr = nullptr;
    size = 0;
}

MangSoNguyen::MangSoNguyen(int size)
{
    this->size = size;
    arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = 0;
    }
}

MangSoNguyen::MangSoNguyen(int a[], int size)
{
    arr = new int[size];
    this->size = size;
    for (int i = 0; i < size; i++)
    {
        arr[i] = a[i];
    }
}

MangSoNguyen::MangSoNguyen(const MangSoNguyen &other)
{
    arr = new int[other.size];
    size = other.size;
    for (int i = 0; i < size; i++)
    {
        arr[i] = other.arr[i];
    }
}

MangSoNguyen::~MangSoNguyen()
{
    if (arr)
    {
        delete[] arr;
    }
}

void MangSoNguyen::Xuat()
{
    cout << "Mang co kich thuoc: " << size << '\n';
    if (size != 0)
    {
        cout << "Cac phan tu cua mang: ";
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << ' ';
        }
    }
    else
    {
        cout << "Khong co phan tu ";
    }
    cout << '\n';
    cout << '\n';
}
int main()
{
    MangSoNguyen msn1;
    msn1.Xuat();
    MangSoNguyen msn2(5);
    msn2.Xuat();
    int arr[10];
    for (int i = 0; i < 8; i++)
    {
        arr[i] = i * i;
    }

    MangSoNguyen msn3(arr, 8);
    msn3.Xuat();

    MangSoNguyen msn4(msn3);
    msn4.Xuat();

    return 0;
}