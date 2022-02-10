#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    while(n % 2 == 0){
        n /= 2;
    }
    cout << (n == 1 ? "YES" : "NO") << endl;
    return 0;
}