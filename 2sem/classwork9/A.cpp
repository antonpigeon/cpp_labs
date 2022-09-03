#include <iostream>
using namespace std;

int main(){
    int n, res = 0, current_begin = 0, current_end = 0;
    cin >> n;
    for(int i = 0; i < n; i++){
        int begin, end;
        cin >> begin >> end;
        if(begin < current_end){
            continue;
        }
        else{
            current_begin = begin;
            current_end = end;
            res++;
        }
    }
    cout << res << endl;
    return 0;
}