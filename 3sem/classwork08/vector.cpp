#include <iostream>
#include <stdlib.h>

template<typename T>
class Vector {
    private:
        size_t size = 0, Capacity = 0;
        T* buffer = nullptr;

        void add_memory(){
            size_t new_Capacity = Capacity * 2;
            T* new_buffer = new T[new_Capacity];
            for(size_t i = 0; i < Capacity; i++){
                new_buffer[i] = buffer[i];
            }
            delete[] buffer;
            buffer = new_buffer;
            Capacity = new_Capacity;
        }

    public:
        Vector(): Capacity(1), buffer(new T) {}
        Vector(Vector const &vec): size(vec.size), Capacity(vec.size) {
            buffer = new T[size];
            for(size_t i = 0; i < size; i++){
                buffer[i] = vec.buffer[i];
            }
        }
        Vector(Vector &&vec) noexcept: size(vec.size), Capacity(vec.Capacity), buffer(vec.buffer){
            vec.size = 0;
            vec.buffer = nullptr;
            vec.Capacity = 0;
        }

        void shrink_to_fit(){
            for(size_t i = size; i < Capacity; i++){
                delete (buffer + i);
            }
            Capacity = size;
        }

        void push_back(const T& value){
            if(size == Capacity){
                add_memory();
            }
            buffer[size] = value;
            size += 1;
        }

        T& top(){
            return buffer[size - 1];
        }
        void pop(){
            if(is_empty()){
                throw std::length_error("Cannot pop an empty vector");
            }
            size -= 1;
        }

        bool is_empty() const{
            return (size == 0);
        }
        size_t capacity() const{
            return Capacity;
        }

        T& at(size_t index){
            if(index >= size or index < 0){
                throw std::out_of_range();
            }
            return buffer[index];
        }

        //T& operator[](size_t index);
        const T& operator[](size_t index){
            return buffer[index];
        }
        ~Vector(){
            delete[] buffer;
        }
};

int main(){
    for(int i = 0; i < 10000000; i++){
        Vector<int> v;
        v.push_back(2);
        v.push_back(5);
        std::cout << v.top() << " " << v.capacity() << " ";
        v.pop();
        std::cout << v.top() << " " << v.capacity() << " ";
        v.shrink_to_fit();
        std::cout << v.capacity();
    }
   
    return 0;
}