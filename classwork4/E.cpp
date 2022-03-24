#include <iostream>
#include <algorithm>
using namespace std;

void siftDown(int a[], int start, int end){
    int root = start;
    while(2*root + 1 <= end){
        int child = 2*root + 1;
        int to_swap = root;
        if(a[to_swap] < a[child]){
            to_swap = child;
        }
        if(child + 1 <= end && a[to_swap] < a[child + 1]){
            to_swap = child + 1;
        }
        if(to_swap == root){
            return;
        }
        else{
            swap(a[root], a[to_swap]);
            root = to_swap;
        }
    }
}

void heapify(int a[], int count){
    //int start = (count-1)%2 == 0 ? (count - 2)/2 : (count-1)/2;
    int start = (count / 2) - 1;
    while (start >= 0){
        siftDown(a, start, count - 1);
        start--;
    }
}

void heapsort(int a[], int count){
    heapify(a, count);
    int end = count - 1;
    while (end > 0){
        swap(a[end], a[0]);
        end--;
        siftDown(a, 0, end);
    }
}

int main(){
    int array[] = {2, 6, 3, 0, 7, 2, 6};
    heapsort(array, 7);
    for(int i = 0; i < 7; i++){
        cout << array[i] << " ";
    }
    cout << endl;
    return 0;
}