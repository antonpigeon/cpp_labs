#include <iostream>
using namespace std;
int main(){
    int max = -1000000000, a = 0;
    while(cin >> a){
        if (a == 0){
            break;
        }
        if (a % 2 == 0 && a > max){
            max = a;
        }
    }
    if (max == -1000000000){
        cout << endl;
    }
    else{
        cout << max << endl;
    }
    return 0;
}