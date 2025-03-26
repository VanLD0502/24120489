#include <iostream>

using namespace std;
int a[1906];
int pre[1001];

bool check(int len, int n, int target)
{
    for (int i = 1; i <= n - len + 1; i++)
    {
        if (pre[i + len - 1] - pre[i - 1] == target)
        {
            cout << i + len - 1 << ' ' << i << '\n';
            return true;
        }
    }

    return false;
}
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    int target;
    cin >> target;
    int l = 0;
    int r = n;
    int res = 0;
    // cout << "HELLO";
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(mid, n, target))
        {
            res = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    cout << res;
    return 0;
}