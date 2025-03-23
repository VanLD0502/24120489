#include <iostream>

using namespace std;

typedef long long ll;
int a[1906];
// Function to check if an array is sorted using recursion
bool isSorted(int arr[], int n) {
    // Base case: If there is only one or zero elements, it is sorted
    if (n == 1 || n == 0) return true;
    // If first element is greater than the second, it's not sorted
    if (arr[0] > arr[1]) return false;
    // Recursive call to check the rest of the array
    return isSorted(arr + 1, n - 1);
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }

    if (isSorted(a, n))
        cout << "The array is sorted.\n";
    else {
        cout << "The array is NOT sorted.\n";
    }
    return 0;

    return 0;
}