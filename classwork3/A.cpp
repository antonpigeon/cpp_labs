#include <iostream>
using namespace std;

void SwapInPlace(int &x, int &y){
    int t = x;
    x = y;
    y = t;
}

void PrintArray(int array[], int size){
    for (int i = 0; i < size; i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

int main(){
    int n;
    cin >> n;
    int arr[n] = {0};
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    int i = 1, j = 2;
    while (i < n){
        if (arr[i - 1] < arr[i]){
            i = j;
            j = j + 1;
        }
        else{
            SwapInPlace (arr[i - 1], arr[i]);
            i = i - 1;
            if (i == 0){
                i = j;
                j = j + 1;
            }
        }
        PrintArray(arr, n);
    }
    cout << endl;
    return 0;
}