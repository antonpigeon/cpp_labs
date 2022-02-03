#include <iostream>
using namespace std;

int gcd(int a, int b){  // greatest common divider
    if(b > a){
        swap(a, b);
    }
    while (b != 0){
        a = a%b;
        swap(a, b);
    }
    return a;
}

int lcm(int a, int b){  // least common mmultiple
    return (a * b / gcd(a, b));
}

int main(){
    int a, b;
    cin >> a >> b;
    cout << "GCD(" << a << ", " << b << ") = " << gcd(a, b) << "\n";
    cout << "LCM(" << a << ", " << b << ") = " << lcm(a, b) << "\n";
    return 0;
}