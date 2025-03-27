#include <iostream>

using namespace std;
int nums[1906];
int pre[1001];
#include <vector>
#include <algorithm>
struct threeNum
{
    int x,y,z;
};


int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    sort(nums, nums + n);
    vector<threeNum> v;

    for (int i = 0; i < n - 2; i ++) {
        //If the current element is equal to the previous element then it doesn't matter.

        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        //fix i and find the sum of 2 elements from the interval [i + 1, n - 1] == -nums[i]
        int l = i + 1;
        int r = n - 1;
        while (l < r) {
            int sum = nums[r] + nums[l];
             //idea is the same exercise 6: 2 Sum.
            if (sum == -nums[i]){
                v.push_back({nums[i], nums[l], nums[r]});
                //remove duplicated elementelement
                //do not select element nums[l] again
                while (l < r && nums[l] == nums[l + 1]) {
                    l++;
                }
                ////do not select element nums[r] again
                while (l < r && nums[r] == nums[r - 1]) {
                    r --;
                }
                //l == r when 
                //find new triple(nums[i], nums[j], nums[k]) with new nums[j], nums[k]
                l ++;
                r --;
            }
            //reduce r, to reduce a[l] + a[r] to can be equal to target
            else if (sum > -nums[i]) {
                r --;
            }
            //reduce r, to reduce a[l] + a[r] to can be equal to target
            else l ++;
        }
    }
    cout << '[';
    for (int i = 0; i < v.size(); i ++) {
        cout << '[' << v[i].x << ", " << v[i].y << ", " << v[i].z << ']';
        if (i != v.size() - 1) {
            cout << ", ";
        }
    }
    cout << ']';    
    return 0;
}
