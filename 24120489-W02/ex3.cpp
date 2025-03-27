#include <iostream>

using namespace std;
int a[1906];

// Function to find the minimum element in a rotated sorted array
int find(int a[], int n) {
    int l = 0;            // Left pointer
    int r = n - 1;        // Right pointer

    while (l < r) {       // Loop until the minimum element is found
        int mid = (l + r) / 2;  // Find the middle element

        // If the middle element is greater than the rightmost element,
        // the minimum must be in the right half.
        if (a[mid] > a[r]) {
            l = mid + 1;  
        }
        else {  
            // Otherwise, the minimum could be in the left half or at mid
            r = mid;  
        }
    }

    // l == r, which is the index of the minimum element
    return a[l];
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }
    cout << find(a,n);
    return 0;
}