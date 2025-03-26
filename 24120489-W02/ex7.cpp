#include <iostream>

using namespace std;
int a[1906];
int pre[1001];
#include <map>
#include <vector>
#include <algorithm>
int main()
{
    /*
        6
-1 0 1 2 -1 4
    */
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);
    for (int i = 0; i < n - 1; i++)
    {
        map<int, int> mp;
        for (int j = i + 1; j < n; j++)
        {
            int tmp = -a[i] - a[j];
            //
            // cout << tmp << ' ' << mp[tmp] << '\n';
            if (mp[tmp] == 1)
            {
                cout << a[i] << ' ' << tmp << ' ' << a[j] << '\n';
            }
            mp[a[j]] = 1;
        }
    }
    return 0;
}
