#include <iostream>

using namespace std;

typedef long long ll;
//Recursive function to compute factorial of n
ll factorial(int n) {
    //Base Case: 0! = 1, 1! = 1
    if (n == 0 || n == 1) return 1;
    //Recursive Case: n = n * (n - 1) !
    return n * factorial(n - 1);
}
int main() {
    int n; cin >> n;
    // Print factorial of n
    cout << factorial(n);
    return 0;
}