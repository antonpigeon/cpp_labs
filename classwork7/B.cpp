#include <iostream>
using namespace std;


struct Student{
    char name[40];
    int score;

    bool operator<(const Student &other){
        return(score < other.score);
    }
    //friend ostream operator<<(ostream o, Student other){
    //    o << other.name << " " << other.score;
    //    return o;
    //}
};

unsigned partition_by_number(Student data[], unsigned l_idx, unsigned r_idx, Student pivot) {
    while(true) {
        while (data[l_idx] < pivot) ++l_idx;
        while (pivot < data[r_idx]) --r_idx;

        if (r_idx <= l_idx)
            return r_idx;
        
        swap(data[l_idx++], data[r_idx--]);
    }
    return r_idx;
}

void quick_sort(Student data[], unsigned l_idx, unsigned r_idx) {
    //cout << "Sorting between indices " << l_idx << " and " << r_idx << endl;
    if (!(l_idx < r_idx)) 
        return;
    auto split_idx = partition_by_number(data, l_idx, r_idx, data[l_idx + (r_idx - l_idx) / 2]);
    
    quick_sort(data, l_idx, split_idx);
    quick_sort(data, split_idx + 1, r_idx);
}

int main(){
    int n, m;
    cin >> n;
    Student students[n];
    for(int i = 0; i < n; i++){
        cin >> students[i].name >> students[i].score;
    }
    cin >> m;
    Student etalon_student{"haha", m};
    quick_sort(students, 0, n - 1);
    //cout << "Sorted!" << endl;
    for(int i = 0; i < n; i++){
        if(etalon_student < students[i]){
            cout << students[i].name << " ";
        }
    }
    return 0;
}