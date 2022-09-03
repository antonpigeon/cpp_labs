#include <iostream>
using namespace std;

int main(){
    bool black[8][8];
    int dp[8][8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            black[i][j] = false;
            dp[i][j] = 0;
        }
    }
    int n;
    cin >> n;
    char inp[3];
    for(int i = 0; i < n; i++){
        cin >> inp;
        black[inp[1]-'1'][inp[0]-'a'] = true;
    }
    char white_inp[3] = "a1";
    cin >> white_inp;
    dp[white_inp[1]-'1'][white_inp[0]-'a'] = 1;
    for(int i = 1; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(black[i][j] == false){
                dp[i][j] += dp[i - 1][j];
            }
            else{
                dp[i][j] += (dp[i - 1][j - 1] + dp[i - 1][j + 1]);         
            }
        }
    }
    int sum = 0;
    for(int j = 0; j < 8; j++){
        sum += dp[7][j];
    }
    cout << sum;
    return 0;
}