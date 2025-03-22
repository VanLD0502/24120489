#include <iostream>
#include <string>
#include <queue>
using namespace std;

typedef long long ll;

// //BackTrack
// void generateBinaryStrings(int n, string str) {
//    str has n elements
//     if (str.length() == n) {
//         cout << str << '\n';
//         return;
//     }

//     for (int j = '0'; j <= '1'; j ++) {
//         str.push_back(j);
//         generateBinaryStrings(n, str);
//         //BackTrack;
//         str.pop_back();
//     }
// }

//function to print all binary strings with n elementselements
void generateBinaryStrings(int n, string str) {
    //str has n elements
    if (str.length() == n) {
        cout << str << '\n';
        return;
    }  
    //Recursive to add "0" into current str
    generateBinaryStrings(n, str + "0");
    //Recursive to add "1" into current str
    generateBinaryStrings(n, str + "1");
}

int main() {
    int n; cin >> n;
    generateBinaryStrings(n, "");
    return 0;
}