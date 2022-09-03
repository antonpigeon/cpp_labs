#include <iostream>
using namespace std;

struct Time{
    int h;
    int m;
    int s;

    void canonize(){
        while(s > 59){
            s -= 60;
            m++;
        }
        while(m > 59){
            m -= 60;
            h++;
        }
        h = h%24;
    }

    Time operator+(Time other){
        Time ans{h + other.h, m + other.m, s + other.s};
        ans.canonize();
        return ans;
    }

    friend ostream& operator<<(ostream &output, const Time &other) {
        output << other.h << ":" << other.m << ":" << other.s;
        return output;            
    }
};

int main(){
    Time t_start, length;
    cin >> t_start.h >> t_start.m >> t_start.s >> length.h >> length.m >> length.s;
    Time end = t_start + length;
    cout << end << endl;
}