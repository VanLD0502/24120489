#include <iostream>

using namespace std;
int a[1906];
int LinearSearchWithSentinel(int a[], int n, int k) {
    int last = a[n - 1];
    a[n - 1] = k;
    int i = 0;
    while (a[i] != k) {
        i ++;
    }
    a[n - 1] = last;
    if (i < n - 1 || (i == n - 1 && last == k)) {
        return i;
    }
    return -1;
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i ++) cin >> a[i];
    int k; cin >> k;
    cout << LinearSearchWithSentinel(a, n, k);
    return 0;
}