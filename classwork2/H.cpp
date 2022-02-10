#include <iostream>
using namespace std;

int myPow(int a, int n){
    int res = 1;
    for (int i = 0; i < n; i++){
        res *= a;
    }
    return res;
}

int main(){
    int n = 0, a = 0, reversed = 0;
    cin >> n >> a;
    int save_a = a;
    for (int i = 0; i < n; i++){
        reversed += myPow(10, n - 1 - i) * (a % 10);
        a /= 10;
    }
    if (reversed == save_a){
        cout << 1 << endl;
    }
    else{
        cout << reversed << endl;
    }
    return 0;
}