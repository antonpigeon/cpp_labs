#include <iostream>
#include <random>
using namespace std;

const int CRYSTAL_HEIGHT = 5, CRYSTAL_WIDTH = 5;

void PrintCrystal(int crystal[CRYSTAL_HEIGHT][CRYSTAL_WIDTH]){
    for (int i = 0; i < CRYSTAL_HEIGHT; i++){
        for (int j = 0; j < CRYSTAL_WIDTH; j++){
            cout << crystal[i][j] << " ";
        }
    cout << endl;
    }
}

bool IsBorderCell(int i, int j){
    return((i == 0) || (j == 0) || (i == CRYSTAL_HEIGHT - 1) || (j == CRYSTAL_WIDTH - 1));
}

int main(){
    mt19937 generator(1);
    uniform_int_distribution<int> directions(1, 4);

    int crystal[CRYSTAL_HEIGHT][CRYSTAL_WIDTH] = {0};
    crystal[1][2] = 1;
    crystal[3][3] = 1;

    bool finished = false;
    int iteration = 1;
    while(!finished){
        PrintCrystal(crystal);
        cout << "//////////////////////////////////////////////" << endl;
        int count_active_dislocs = 0;
        for (int i = 0; i < CRYSTAL_HEIGHT; i++){
            for (int j = 0; j < CRYSTAL_WIDTH; j++){
                if(crystal[i][j] == iteration){
                    if(IsBorderCell(i, j) == true){
                        crystal[i][j] = -1;
                    }
                    else{
                        count_active_dislocs++;
                        int direction = directions(generator);  // 1 - влево, 2 - вверх, 3 - вправо, 4 - вниз
                        int cell_to_move_i = i + (direction - 2) % 2;
                        int cell_to_move_j = j + (direction - 3) % 2;
                        if(crystal[cell_to_move_i][cell_to_move_j] == 0){
                            crystal[cell_to_move_i][cell_to_move_j] = iteration + 1;
                            crystal[i][j] = 0;
                        }
                    }
                }
            }
        }
        if(count_active_dislocs == 0){
            finished = true;
            PrintCrystal(crystal);
            cout << "//////////////////////////////////////////////" << endl;
        }
        iteration++;
    }
    return 0;
}