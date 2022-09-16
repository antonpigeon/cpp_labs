#include <iostream>
using namespace std;
int main(){
    int max = -1000000000, a = 0, count = 0;
    while(cin >> a){
        if (a == 0){
            break;
        }
        if (a > max){
            max = a;
            count = 0;
        }
        if (a == max){
            count++;
        }
    }
    cout << count << endl;
    return 0;
}