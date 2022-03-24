#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

float recursive_sum(float const psi[], float const pdf[], float const dv, int left, int right){
    if(right == left + 1){
        return dv*psi[left]*pdf[left];
    }
    int mid = left + (right - left) / 2;
    return recursive_sum(psi, pdf, dv, left, mid) + recursive_sum(psi, pdf, dv, mid, right);
}

int main(){
    cout << setprecision(15) << fixed;
    float psi[1000];
    float pdf[1000];
    float T = 1;
    float dv = 0.01*sqrt(T);
    for(int i = 0; i < 1000; i++){ 
        psi[i] = abs((i-500)*dv);
        pdf[i] = exp(-((i- 500)*dv*(i - 500)*dv)/T);
    }
    cout << recursive_sum(psi, pdf, dv, 0, 1000)/sqrt(M_PI*T) << endl;
    return 0;
}