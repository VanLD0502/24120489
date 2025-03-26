#include <iostream>

using namespace std;
int a[1906];
int find(int a[], int l, int r) {
    if (l == r) return a[l];
    int mid = (l + r) / 2;
    int m1 = find(a, l, mid);
    int m2 = find(a, mid + 1, r);
    return min(m1, m2);
}
int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }
    cout << find(a, 0,n - 1);
    return 0;
}