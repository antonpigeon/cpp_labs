#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

float adjacent_sum(float const psi[], float const pdf[], float const dv, int length){
    int step = 1;
    float ans[length];
    for(int i = 0; i < length; i++){
        ans[i] = psi[i] * pdf[i] * dv;
    }
    while(step < length){
        for(int i = 0; i + step < length; i += 2*step){
            ans[i] = ans[i] +ans[i + step];
        }
        step *= 2;
    }
    return ans[0];
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
    cout << adjacent_sum(psi, pdf, dv, 1000)/sqrt(M_PI*T) << endl;
    return 0;
}