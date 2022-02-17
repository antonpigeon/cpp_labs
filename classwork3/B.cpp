#include <iostream>
using namespace std;

int main(){
    int n = 0, to_find = 0;
    cin >> n;
    int arr[n] = {0};
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    cin >> to_find;
    int l = -1, r = n;
    while (r - l > 1){
        int mid = l + (r - l) / 2;
        if (arr[mid] < to_find){
            l = mid;
        }
        else{
            r = mid;
        }
    }
    cout << r << endl;
    return 0;
}