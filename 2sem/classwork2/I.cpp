#include <iostream>
using namespace std;

bool isPrime(int x){
    for (int i = 2; i * i <= x; i++){
        if (x % i == 0){
            return false;
        }
    }
    return true;
}

int main(){
    int n = 0;
    cin >> n;
    while(n != 1){
        int save_n = n;
        for (int i = 2; i * i <= n; i++){
            if (n % i == 0 && isPrime(i)){
                n /= i;
                cout << i << " ";
                break;
            }
        }
        if (n == save_n){
            cout << n << endl;
            return 0;
        }
    }
    return 0;
}