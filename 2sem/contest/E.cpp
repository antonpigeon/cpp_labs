#include<iostream>

using namespace std;

uint32_t get_results(uint32_t channel)
{
    static uint32_t calls = 0;
    calls++;
    if (calls > 25) return static_cast<uint32_t>(-1);

    static uint32_t min = 10, max = 255760;
    static uint32_t min_channel = 50, max_channel = 250;
    static uint32_t zero = 100000;

    if (channel <= min_channel)
        return static_cast<uint32_t>(zero - channel*((double)zero - min)/min_channel);
    if (channel <= max_channel)
        return static_cast<uint32_t>(min + ((double)channel - min_channel)*((double)max - min)/((double)max_channel - min_channel));
    if (channel <= 360)
        return static_cast<uint32_t>(max - ((double)channel - max_channel)*((double)max - zero)/((double)360 - max_channel));
    return static_cast<uint32_t>(-1);
}

uint32_t get_res(uint32_t i, bool reverse=false){
    if(reverse==false){
        return get_results(i%360);
    }
    else{
        return get_results((359-i)%360);
    }
}

int32_t deriv(uint32_t i, bool reverse=false){
    return (get_res(((i + 1)%360), reverse) - get_res((i%360), reverse));
}

void deriv_binsearch(uint32_t left, uint32_t right, bool reverse=false){
    uint32_t lval = get_res(left, reverse);
    while(right - left > 1){
        uint32_t mid = left + (right - left)/2;
        uint32_t midval = get_res(mid, reverse);
        if(midval < lval){
            left = mid;
        }
        else{
            int32_t mid_deriv = get_res(mid+1, reverse) - midval;
            if (mid_deriv< 0){
                right = mid;
            }
            else{
                left = mid;
            }
        }
    }
    cout << get_res(right%360, reverse) << " " << ((reverse==false) ? (right%360) : (359-right)%360);
}

void detect(){
    bool reverse = false;
    uint32_t start_channel = 0, end_channel = 359;
    if(deriv(359) < 0){
        reverse = true;
    }
    // теперь start_channel находится на возрастающей части    
    deriv_binsearch(start_channel, end_channel, reverse);
}

int main() {
    cout << endl;
    detect();
    return 0;
}