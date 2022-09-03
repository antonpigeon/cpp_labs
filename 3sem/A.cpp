#include <iostream>
#include <cstdlib>

void swap(void* &a, void* &b){
    void* tmp;
    tmp = a;
    a = b;
    b = tmp;
}

int main(){
    memcpy()
    char a = 'a', b = 'b';
    void* ptra = &a, *ptrb = &b;
    swap(ptra, ptrb);
    std::cout << *(reinterpret_cast<char*> (ptra)) << " " << *(reinterpret_cast<char*> (ptrb)) << std::endl;
    return 0; 
}