#include <iostream>
#include <cassert>
#include <random>
#include <algorithm>
using namespace std;

long* allocate(unsigned long long N){
    long* arr_ptr = new long[N];
    return arr_ptr;
}

long* allocate_at(long** dst, unsigned long long N){
    long* arr_ptr = new long[N];
    *dst = arr_ptr;
    return arr_ptr;
}

void release(long **ptr){
    delete[] *ptr;
    *ptr = nullptr;
}

// 2

long* reallocate(long** ptr, unsigned long long N, unsigned long long new_N){
    long* new_ptr = new long[new_N];
    unsigned long long min_N = (N < new_N) ? N : new_N;
    for(unsigned long long i = 0; i < min_N; i++){
        new_ptr[i] = (*ptr)[i];
    }
    delete[] *ptr;
    *ptr = new_ptr;
    return new_ptr;
}

long* next(long *current){
    return current + 1;
}

void dump(char const* begin, char const* end){
    for(int i = 0; i < end - begin; i++){
        cout << *(begin + i);
    }
}

void reverse(char* begin, char* end){
    for(int i = 0; i <= (end - begin)/2; i++){
        char t = *(end - 1 - i);
        *(end - 1 - i) = *(begin + i);
        *(begin + i) = t;
    }
}

void merge(long *begin_a, long *end_a, long *begin_b, long *end_b, long *out){
    long* ptr_a = begin_a, *ptr_b = begin_b, *ptr_out = out;
    while(ptr_a != end_a || ptr_b != end_b){
        if((ptr_b == end_b) || ((ptr_a != end_a) && (*ptr_a < *ptr_b))){
            *ptr_out = *ptr_a;
            ptr_a++;
        }
        else{
            if(ptr_b != end_b || ptr_a == end_a){
                *ptr_out = *ptr_b;
                cout << *ptr_b << "  ";
                ptr_b++;
            }
        }
        ptr_out++;
    }
}

long* qs_partition(long* begin, long* end, long X){
    long* left_ptr = begin, *right_ptr = end - 1;
    while(true){
        while(*left_ptr < X){
            left_ptr++;
        }
        while(*right_ptr > X){
            right_ptr--;
        }
        if(left_ptr >= right_ptr){
            return right_ptr;
        }
        long t = *right_ptr;
        *right_ptr - 1 = *left_ptr;
        *left_ptr = t;
        left_ptr++;
        right_ptr--;
    }

}

void dump_array(long *begin, long *end){
    while (begin != end){
        std::cout << *(begin++) << " ";
    }
    std::cout << "\n";
}

unsigned partition_by_number(long data[], unsigned l_idx, unsigned r_idx, unsigned pivot) {
    while(true) {
        while (data[l_idx] < pivot) ++l_idx;
        while (pivot < data[r_idx]) --r_idx;

        if (r_idx <= l_idx){
            dump_array(data, data+9);
            return r_idx;
        }
        swap(data[l_idx++], data[r_idx--]);
    }
    return r_idx;
}


int main(){
    long arr[] = {4, 2, 5, 1, 18, 7, 6, 9, 5};
    partition_by_number(arr, 0, 9, 5);
    auto middle = qs_partition(arr, arr + 9, 5);
    dump_array(arr, arr+9);
  }