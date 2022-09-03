#include <iostream>
using namespace std;
int main(){
    int coins[] = {98, 49, 7, 1};
    int n, res = 0, i = 0;
    cin >> n;
    while(n > 0){
        int sum = 0;
        while(sum <= n){
            sum += coins[i];
            res++;
        }
        res--;
        sum -= coins[i];
        n -= sum;
        i++;
    }
    cout << res << endl;
    return 0;
}