#include <iostream>

using namespace std;
int a[1906];

int find(int a[], int n) {
    int l = 0;
    int r = n - 1;
    while (l < r) {
        int mid = (l + r) / 2;
        if (a[mid] > a[r]) {
            l = mid + 1;
        }
        else{
            r = mid;
        }
    }
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