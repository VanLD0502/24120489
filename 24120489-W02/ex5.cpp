#include <iostream>

using namespace std;
int a[1906];
int pre[1001];

bool check(int len, int n, int target)
{
    //loop all subarray start i
    for (int i = 1; i <= n - len + 1; i++)
    {
        //end at i + len - 1, (start i, length of subarray = len)
        //pre[i + len - 1] - pre[i - 1] : sum of elements of [i, i + len - 1];
        if (pre[i + len - 1] - pre[i - 1] == target)
        {
            return true;
        }
    }
    //dont find 
    return false;
}

int twoPointer() {
    int n; cin >> n; 
    for (int i = 0; i < n; i ++) cin >> a[i];
    int target; cin >> target;
    //pointer left
    int l = 0;
    int sum = 0;
    int res = 1e9;
    //r : pointer right;
    for (int r = 0; r < n; r ++) {
        //current sum/
        sum += a[r];
        //if sum >= target, uppdate minimum length and erase left element(decrease sum) such that sum >= target. 
        while (sum >= target && l <= r) {
            res = min(res, r - l + 1);
            sum -= a[l];
            l ++;
        }
    }
    //Don't find any subarrays in array return 0;
    if (res == 1e9) return 0;
    //print result.
    return res;
}

int BinarySearchOnAnswer() {
    //BinarySearchByAnswer
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        //prefix[sum]
        pre[i] = pre[i - 1] + a[i];
    }
    int target;
    cin >> target;
    int l = 0; // low, len = 0;
    int r = n;// hight, len = n;
    int res = 0;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (check(mid, n, target))
        {
            res = mid;
            // find a smaller subarray(length)
            r = mid - 1;
        }
        else
            //example mid = 2(current subarray = 2, not be answer, length = 1, not be answer, sum < target(len = 2) => sum < target(len = 1));
            l = mid + 1;
    }
    return res; // minimum length of subarray.
}
int main()
{
    cout << twoPointer();
    
    return 0;
}