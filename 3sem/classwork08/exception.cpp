#include <iostream>

struct base_exception {
    virtual std::string what() = 0;
};

struct math_exception: base_exception {
    float value;
    math_exception(float i): value(i) { }

    math_exception(math_exception const &other): math_exception(other.value) { }

    math_exception& operator=(math_exception const &other) {
        value = other.value;
        return *this;
    }

    std::string what() override {
        return std::string("Error: attempt to divide " + std::to_string(value) + " by zero");
    }
};

struct invalid_argument: base_exception {
    float value;
    invalid_argument(float i): value(i) { }
    invalid_argument(invalid_argument const &other): invalid_argument(other.value) { }
    invalid_argument& operator=(invalid_argument const &other) {
        value = other.value;
        return *this;
    }
    std::string what() override {
        return std::string("Invalid argument for square root: " + std::to_string(value) + " is less than 0");
    }
};

float inv(float f){
    if(f == 0) throw math_exception(1);
    return 1/f;
}

float my_sqrt(float f){
    if(f < 0) throw invalid_argument(f);
    if(f == 0) return 0;
    float l = 0, r = std::max(1.0f, f);
    while(r - l > 1.e-5){
        float mid = l + (r - l)/2;
        if(mid*mid < f){
            l = mid;
        }
        else{
            r = mid;
        }
    }
    return r;
}
int main(){
    float g = 3;
    try{
        std::cout << my_sqrt(g) << std::endl;
        std::cout << inv(0) << std::endl;
    }
    catch(invalid_argument invarg){
        std::cout << invarg.what() << std::endl;
    }
    catch(math_exception mexc){
        std::cout << mexc.what() << std::endl;
    }

}