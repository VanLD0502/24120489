#include <iostream>
#include <string>
#include <queue>
using namespace std;

typedef long long ll;

#include <iostream>
using namespace std;

// Recursive function to solve Tower of Hanoi
void towerOfHanoi(int n, char from, char to, char aux) {
    //Base Case
    if (n == 1) {
        cout << "Move disk 1 from " << from << " to " << to<< endl;
        return;
    }
    //Recursive Case: Move n-1 disks from `from` to `aux`, using `to` as an auxiliary peg
    towerOfHanoi(n - 1, from, aux, to);
    //Move largest disc from column from "from" to "to"
    cout << "Move disk " << n << " from " << from << " to " << to << endl;
    //Recursive Case: Move n-1 disks from `aux` to `to`, using `from` as an auxiliary peg
    towerOfHanoi(n - 1, aux, to, from);
}

int main() {
    int n; cin >> n;
    towerOfHanoi(n, 'A', 'C', 'B');
    return 0;
}