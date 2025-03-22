#include <iostream>

using namespace std;

typedef long long ll;
int a[1906];
bool isSorted(int arr[], int n) {
    if (n == 1 || n == 0) return true;

    if (arr[0] > arr[1]) return false;

    return isSorted(arr + 1, n - 1);
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i ++) {
        cin >> a[i];
    }
    cout << isSorted(a, n);
    return 0;
}