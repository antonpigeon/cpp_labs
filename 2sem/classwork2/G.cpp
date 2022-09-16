#include <iostream>
using namespace std;
#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    for (int i = n/2 + 1; i >= 2; i--){
        if (n % i == 0){
            cout << i << " ";
        }
    }
    cout << "\n";
    return 0;
}