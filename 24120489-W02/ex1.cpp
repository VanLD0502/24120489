#include <iostream>

using namespace std;
int a[1906];
int linearSearch(int a[], int n, int k) {
    for (int i = 0; i < n; i ++) {
        if (a[i] == k) return i; // Return the index directly
    }
    return -1; // Return -1 if not found
}
int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i ++) cin >> a[i];
    int k; cin >> k;
    cout << linearSearch(a, n, k);
    return 0;
}