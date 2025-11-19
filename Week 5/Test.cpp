#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main()
{
    try
    {
        throw out_of_range("Hello");
    }
    catch (out_of_range e)
    {
        cout << e.what();
    }

    return 0;
}