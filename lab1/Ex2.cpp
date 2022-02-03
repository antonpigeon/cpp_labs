#include <iostream>
#include <cmath>
using namespace std;
int main(){
    int a, b, c;
    cin >> a >> b >> c;
    if (a == 0){
        double x = -c*1.0/b;
        cout << x;
    }
    else{
        double d = b*b - 4*a*c;
        cout << d << "\n";
        if (d < 0){
            cout << "\n";
            return 0;
        }
        else if(d == 0){
            double x =  -b * 1.0 / (2.0*a);
            cout << x;
            return 0;
        }
        else{
            double x1 = (-b - sqrt(d)) / 2*a;
            double x2 = (-b + sqrt(d)) / 2*a;
            cout << x1 << " " << x2;
        }
    }
    return 0;
}