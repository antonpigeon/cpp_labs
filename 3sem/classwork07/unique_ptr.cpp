#include <iostream>
#include <memory>

template <typename T>
class unique_ptr {
    private:
        T* ptr;
    public:
        explicit unique_ptr(T* ptr): ptr(ptr) {
            //std::cout << "u_ptr\n";
        }

        ~unique_ptr(){
            delete ptr;
            //std::cout << "~u_ptr\n";
        }

        unique_ptr<T>& operator=(const unique_ptr<T> &other) = delete;
        unique_ptr<T>(const unique_ptr<T> &other) = delete;
        unique_ptr<T>(unique_ptr<T>&& other): ptr(other.ptr){
            //std::cout << "u_ptr(&&u_ptr)\n";
            delete other.ptr;
            other.ptr = nullptr;
        }
        T& operator*(){
            return *(ptr);
        }
        T* operator->(){
            return ptr;
        }
};

struct my_struct{
    int a, b;
};

int main(){
    double *ptr = new double;
    *ptr = 3.14;
    unique_ptr <double> uniq3(ptr);
    my_struct *pair = new my_struct;
    pair->a = 5;
    pair->b = 7;
    unique_ptr <my_struct> uniq_pair(pair);
    std::cout << uniq_pair->a << " " << uniq_pair->b << std::endl;
    return 0;
}
