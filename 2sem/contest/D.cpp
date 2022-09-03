#include<iostream>

using namespace std;

void recognize(int* data_start, int* data_end, int* command, int** frame){
    for(int* current = data_start; current < data_end; current++){
        bool found_left = true, found_right = true, found_back = true, found_meow = true;
        for(int i = 0; i < N; i++){
            if(*(current + i) != left[i]){
                found_left = false;
            }
            if(*(current + i) != right[i]){
                found_right = false;
            }
            if(*(current + i) != back[i]){
                found_back = false;
            }
            if(*(current + i) != meow[i]){
                found_meow = false;
            }
        }
        if(found_back){
            command = back;
            *frame = current;
            return;
        }
        if(found_left){
            command =left;
            *frame = current;
            return;
        }
        if(found_right){
            command = right;
            *frame = current;
            return;
        }
        if(found_meow){
            command = meow;
            *frame = current;
            return;
        }

    }
    *command = 0;
}