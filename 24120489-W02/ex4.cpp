#include <iostream>

using namespace std;

int a[1906]; // Array to store the input values

// Function to check if the array can be divided into at most 'k' subarrays 
// such that the maximum sum of any subarray does not exceed 'x'
bool check(int a[], int n, int k, int x)
{
    int cnt = 1;  // Number of subarrays
    int sum = 0;  // Sum of the current subarray

    for (int i = 0; i < n; i++)
    {
        if (a[i] > x) // If any element is greater than 'x', it's not possible
            return false;

        sum += a[i];

        if (sum > x) 
        {
            // new sub array with first element a[i];
            sum = a[i];
            // increase subarrayarray
            cnt++;
        }
        else if (sum == x) 
        {
            // new sub arrayarray
            sum = 0;
            cnt++;
        }
    }
    
    return cnt <= k; // minimum days to delivery <= k(allowed delivery dayday)
}

int main()
{
    int n;
    cin >> n; // Read number of elements in the array

    int sum = 0; // Variable to store the total sum of the array
    for (int i = 0; i < n; i++)
    {
        cin >> a[i]; // Read array elements (a[i] : weight of packeage[i])
        sum += a[i]; // Calculate the total sum
    }

    int days;
    cin >> days; //(subarrays allowed)

    int l = 1;   //low of possible answer
    int r = sum; //high of possible answer (total sum of the array)
    int res = 0; // Variable to store the minimum maximum sum

    // Binary search to find the minimum possible maximum sum
    while (l <= r)
    {
        int mid = (l + r) / 2; // Middle value (possiple minimum capacity)

        if (check(a, n, days, mid)) // If it's possible , can delivery packages in allowed days
        {
            res = mid; // Update result
            r = mid - 1; // find a smaller maximum sum
        }
        else
        {
            l = mid + 1; // increase lower 
        }
    }

    cout << res << '\n'; // print result(minimum weight)
    return 0;
}
