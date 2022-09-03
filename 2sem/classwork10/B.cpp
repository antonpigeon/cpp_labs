#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int dp[3] = {0};
    dp[0] = 0;
    cout << "0 0 0" << endl;
    for(int i = 1; i <= n; i++){
        int cost;
        cin >> cost;
        dp[i%3] = min(dp[i%3], dp[(i - 1)%3]);
        if(i > 1) dp[i%3] = min(dp[i%3], dp[(i - 2)%3]);
        dp[i%3] += cost;
        cout << dp[0] << ' ' << dp[1] << ' ' << dp[2] << endl;
    }
    cout << dp[n%3] << endl;
    return 0;
}