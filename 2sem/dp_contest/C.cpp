#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int n;
    cin >> n;
    int dp[n];
    int heights[n];
    dp[0] = 0;
    for(int i = 0; i < n; i++){
        cin >> heights[i];
    }
    for(int i = 1; i < n; i++){
        dp[i] = dp[i - 1] + abs(heights[i] - heights[i - 1]);
        if (i > 1){
            dp[i] = min(dp[i], dp[i - 2] + 3*abs(heights[i] - heights[i - 2]));
        }
    }
    cout << dp[n - 1] << "\n";
    return 0;
}