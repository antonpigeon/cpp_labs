#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

float kahan_sum(float psi[], float pdf[], float dv, int length) {
    float sum = 0.0;
    float c = 0.0;
    float ans[length];
    for(int i = 0; i < length; i++){
        ans[i] = psi[i] * pdf[i] * dv;
    }           
    for (int i = 0; i < length; ++i) {
        float y = ans[i] - c;
        float t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
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
    cout << kahan_sum(psi, pdf, dv, 1000)/sqrt(M_PI*T) << endl;
    return 0;
}