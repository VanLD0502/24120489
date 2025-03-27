#include <iostream>

using namespace std;
int a[1906];
int pre[1001];

bool find(int a[], int n, int target)
{
    int l = 0;// left pointer
    int r = n - 1; // right pointer
    while (l < r)
    {
        //Obviously returns True
        if (a[l] + a[r] == target)
        {
            return true;
        }
        //reduce r, to reduce a[l] + a[r] to can be equal to target
        else if (a[l] + a[r] > target)
            r--;
        //increare l, to increase a[l] + a[r] to can be equal to target
        else
            l++;
    }
    //dont find sum = target
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
