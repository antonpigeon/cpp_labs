#include <iostream>

template <typename T>
struct Comparator{
    virtual bool operator()(T const &, T const &) = 0;
};

struct IntComparator final: Comparator<int>{
    bool operator()(int const &lha, int const &rha){
        return lha < rha;
    }
};

template <typename T>
T* qsort_partition(T* begin, T* end, T pivot, Comparator<T> &comp){
    T* l_idx = begin, *r_idx = end - 1; 
    while(true){
        std::cout << l_idx - begin << " " << r_idx - begin << " "; 
        while(comp(*l_idx, pivot)) ++l_idx;
        while(comp(pivot, *r_idx)) --r_idx;
        std::cout << l_idx - begin << " " << r_idx - begin << std::endl; 
        if(r_idx + 1 <= l_idx){
            return r_idx + 1;
        }
        std::swap(*(l_idx++), *(r_idx--));
    }
    return r_idx;
}

template <typename T>
void quicksort(T* begin, T* end, Comparator<T> &comp){
    if(begin + 1 >= end){
        return;
    }
    T* split_idx = qsort_partition<T>(begin, end, *(begin + (end - begin)/2), comp);
    quicksort(begin, split_idx, comp);
    quicksort(split_idx, end, comp);
}

struct FloatComparator final: Comparator<float>{
    bool operator()(float const &lha, float const &rha) override{
        return lha < rha;
    }
};


struct Complex_number{
    float abs, arg;
};

struct ComplexComparator final: Comparator<Complex_number>{
    bool operator()(Complex_number const &lha, Complex_number const &rha) override{
        return lha.abs < rha.abs ? true : lha.arg < rha.arg;
    }
};

int main(){
    ComplexComparator comp;
    Complex_number *arr = new Complex_number[6];
    float pi = 3.1415;
    arr[0] = {10, pi};
    arr[1] = {10, pi/2};
    arr[2] = {3, 0.75*pi};
    arr[3] = {2, 0.75*pi};
    arr[4] = {2, pi};
    arr[5] = {5, 1.5*pi};
    quicksort(arr, arr + 6, comp);
    for(int i = 0; i < 6; i++){
        std::cout << arr[i].abs << " " << arr[i].arg << "  ";
    }
    std::cout << std::endl;
    return 0;
}