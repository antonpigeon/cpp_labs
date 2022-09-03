#include <vector>
#include <iostream>
using namespace std;

int main(){
    vector <int> arr;
    int n;
    for(int i = 0; i < 10; i++)
    {   
        cin >> n;
        cout << n << ' ';
        arr.push_back(n);
    }
    cout << "haha!" << endl;
    return 0;
}