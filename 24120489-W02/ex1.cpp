#include <iostream>

using namespace std;
int a[1906];
int find(int a[], int n, int k) {
    for (int i = 0; i < n; i ++) {
        if (a[i] == k) return i;
    }
    return -1;
}
int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i ++) cin >> a[i];
    int k; cin >> k;
    cout << find(a, n, k);
    return 0;
}