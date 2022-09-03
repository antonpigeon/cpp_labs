#include <iostream>
using namespace std;
int main(){
    int a, b;
    cin >> a >> b;
    if(b > a){
        swap(a, b);
    }
    while (b != 0){
        a = a%b;
        swap(a, b);
    }
    cout << a;
    return 0;
}