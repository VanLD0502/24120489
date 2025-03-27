#include <iostream>

using namespace std;
int a[1906];
bool check(int a[], int n, int k, int x)
{
    int cnt = 1;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > x)
            return false;
        sum += a[i];
        if (sum > x)
        {
            sum = a[i];
            cnt++;
        }
        else if (sum == x)
        {
            sum = 0;
            cnt++;
        }
    }
    return cnt <= k;
}
int main()
{
    int n;
    cin >> n;
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }
    int days;
    cin >> days;

    int l = 1;
    int r = sum; 
    int res = 0;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(a, n, days, mid))
        {
            res = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    cout << res << '\n';
    return 0;
}