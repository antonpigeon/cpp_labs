#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int dp[3] = {0};
    dp[0] = 1;
    for(int i = 1; i <= n; i++){
        dp[i%3] += dp[(i - 1)%3];
        if(i > 1) dp[i%3] += dp[(i - 2)%3];
    }
    cout << dp[n%3] << endl;
    return 0;
}