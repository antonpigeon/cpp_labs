#include <iostream>
#include <cmath>
using namespace std;
int main(){
    int n = 0;
    cin >> n;
    int res = 1;
    for (int i = 1; i <= n; i++){
        res *= i;
    }
    cout << res;
    return 0;
}