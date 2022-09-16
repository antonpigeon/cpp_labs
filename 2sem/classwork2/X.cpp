#include <iostream>
using namespace std;

double nth_term(int n){
    double res = 1/(n * n * 1.0);
    return res;
}

int main(){
    int n = 0;
    cin >> n;
    double sum = 0.0;
    for (int i = 1; i <= n; i++){
        sum += nth_term(i);
    }
    cout << sum << endl;
    return 0;
}