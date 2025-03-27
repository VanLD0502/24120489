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