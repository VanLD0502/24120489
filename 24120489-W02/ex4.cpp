#include <iostream>

using namespace std;
int a[1906];
bool check(int a[], int n, int k, int x)
{
    int cnt = 1;
    // cout << '\n';
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] > x)
            return false;
        sum += a[i];
        if (sum > x)
        {
            // cout << sum << '\n';
            sum = a[i];
            cnt++;
        }
        else if (sum == x)
        {
            // cout << sum << '\n';
            sum = 0;
            cnt++;
        }
    }
    // cout << "CNT " << cnt << '\n';
    return cnt <= k;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int days;
    cin >> days;

    int l = 1;
    int r = 20;
    int res = 0;
    // cout << "CHeck " << check(a, n, days, 15) << '\n';
    while (l <= r)
    {
        int mid = (l + r) / 2;
        // cout << mid << '\n';
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