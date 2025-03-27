#include <iostream>

using namespace std;
int a[1906];
int pre[1001];

bool find(int a[], int n, int target)
{
    int l = 0;
    int r = n - 1;
    while (l < r)
    {
        if (a[l] + a[r] == target)
        {
            return true;
        }
        else if (a[l] + a[r] > target)
            r--;
        else
            l++;
    }
    return false;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int target;
    cin >> target;
    if (find(a, n, target))
    {
        cout << "YES\n";
    }
    else
        cout << "NO\n";

    return 0;
}
