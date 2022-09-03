#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void Split(float const x, float &x_h, float &x_l) {
    auto c = static_cast<float>((1ul << 11) + 1ul);
    x_h = (c * x) + (x - (c * x));
    x_l = x - x_h;
}

float TwoMult(float const a, float const b){
    float a_high, a_low, b_high, b_low;
    Split(b, b_high, b_low);
    Split(a, a_high, a_low);
    float s = a * b, t;
    t = a_high * b_high;
    t += a_high * b_low;
    t += a_low * b_high;
    t += a_low * b_low;
    return t;
}

float fma_sum(float psi[], float pdf[], float dv, int length) {
    float s = 0;
    for(int i = 0; i < length; i++){
        s += TwoMult(TwoMult(psi[i], pdf[i]), dv); 
    }
    return s;
}

float naive_sum(float psi[], float pdf[], float dv, int length){
    float s = 0;
    for (int i = 0; i < length; i++){
        s += psi[i] * pdf[i] * dv;
    }
    return s;
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
    cout << fma_sum(psi, pdf, dv, 1000)/sqrt(M_PI*T) << endl;
    cout << naive_sum(psi, pdf, dv, 1000)/sqrt(M_PI*T) << endl;
    return 0;
}