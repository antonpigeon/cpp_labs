#include <iostream>
using namespace std;

struct Student{
    char name[40];
    float score;
};


int main(){
    Student students[10];
    for(int i = 0; i < 10; i++){
        cin >> students[i].name >> students[i].score;
    }
    float threshold;
    cin >> threshold;
    for(int i = 0; i < 10; i++){
        if(students[i].score > threshold){
            cout << students[i].name << " ";
        }
    }
    cout << endl;
    return 0;
}