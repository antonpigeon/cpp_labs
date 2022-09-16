#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    cout << (n % 4 == 0 && n % 100 != 0 ? "YES\n" : "NO\n");
    return 0;
}