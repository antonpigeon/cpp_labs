#include <iostream>
using namespace std;
int main(){
    int res = 0, a = 0;
    while(cin >> a){
        if (a == 0){
            break;
        }
        if (a % 2 == 0){
            res++;
        }
    }
    cout << res << endl;
    return 0;
}