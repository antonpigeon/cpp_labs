#include <iostream>
using namespace std;

void swap(int &a, int &b){
    int t = a;
    a = b;
    b = t;
    return;
}

int main(){
    int x = 5, y = 2;
    cout << x << " " << y << endl;
    swap(x, y);
    cout << x << " " << y << endl;
    return 0;
}