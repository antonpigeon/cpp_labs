# include <iostream> 


int main() {
    int arr[5] = {0};
    int var = 2;
    int *array_ref = &arr[5];
    arr[0] = var;
    std::cout << typeid(arr).name() << std::endl;
    std::cout << typeid(arr[0]).name() << std::endl;
    std::cout << typeid(var).name() << std::endl;
    std::cout << typeid(array_ref).name() << std::endl;
    return 0;
}