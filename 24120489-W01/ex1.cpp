#include <iostream>

using namespace std;

typedef long long ll;

//Recursive function to compute Fibonacci numbers
ll fibonacci(ll n) {
    //Base Case
    if (n == 0) return 0; //f(0) = 0;
    //Base Case
    if (n == 1) return 1;//f(1) = 1;
    //Recursive Case: f(n) = f(n - 1) + f(n - 2)
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n; cin >> n;
    //Loop: print i th fibonacci number
    for (int i = 0; i < n; i ++) {
        cout << fibonacci(i) << ' ';
    }
    return 0;
}