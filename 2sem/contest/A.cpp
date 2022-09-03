#include<iostream>

using namespace std;

int main(){
    int pos[30] = {0};
    int a, b, l, n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a >> b;
        for(int i = a; i < a + b; i++){
            pos[i] = 1;
        }
    }
    cin >> l;
    for(int i = 0; i < 30; i++){
        if(pos[i] == 0){
            int checking = i;
            bool can_fit = true;
            for(int j = checking; j < checking + l; j++){
                if(j > 29){
                    can_fit = false;
                    break;
                }
                if(pos[j] == 1){
                    can_fit = false;
                    break;
                }
            }
            if(can_fit == true){
                cout << i;
                return 0;
            }
        }
    }
    cout << "-1";
    return 0;
}