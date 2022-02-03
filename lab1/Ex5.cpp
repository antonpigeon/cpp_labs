#include <iostream>
using namespace std;
int main(){
    int a0, b0;
    cin >> a0 >> b0;
    int a = a0, b = b0;
    if(b > a){
        swap(a, b);
    }
    while (b != 0){
        a = a%b;
        swap(a, b);
    }
    cout <<(a0 * b0 / a);
    return 0;
}