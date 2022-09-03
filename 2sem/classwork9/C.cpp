#include <iostream>
using namespace std;

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    int last_fueled = 0, prev_coord = 0, res = 0;

    for (int i = 0; i <= k; i++){
        int next;
        if(i == k){
            next = n;
        }
        else{
            cin >> next;
        }
        if(next - last_fueled <= m){
            prev_coord = next;
            continue;
        }
        if(prev_coord == last_fueled){
            cout << -1;
            return 0;
        }
        last_fueled = prev_coord;
        prev_coord = next;
        res++;
    }
    cout << res << endl;
    return 0;
}