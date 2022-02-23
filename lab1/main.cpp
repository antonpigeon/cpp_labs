#include <iostream>
#include <random>
using namespace std;

const int CRYSTAL_HEIGHT = 10, CRYSTAL_WIDTH = 10, TOTAL_DISLOCATIONS = 4;

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

bool CheckAdjacentCells(int crystal[CRYSTAL_HEIGHT][CRYSTAL_WIDTH], int i, int j, int value){
    return ((crystal[i][j - 1] == value) || (crystal[i - 1][j] == value) || (crystal[i][j + 1] == value) || (crystal[i + 1][j] == value)||
            (crystal[i][j - 1] == -1) || (crystal[i - 1][j] == -1) || (crystal[i][j + 1] == -1) || (crystal[i + 1][j] == -1));
}

int main(){
    seed_seq sseq = {32534, 1022};
    mt19937 generator(sseq);
    generator.discard(20000);

    uniform_int_distribution<int> directions(1, 4);
    uniform_int_distribution<int> is (0, CRYSTAL_HEIGHT - 1);
    uniform_int_distribution<int> js (0, CRYSTAL_WIDTH - 1);
   
    int crystal[CRYSTAL_HEIGHT][CRYSTAL_WIDTH] = {0};
    for (int k = 1; k <= TOTAL_DISLOCATIONS; k++){
        int i = is(generator);
        int j = js(generator);
        if(crystal[i][j] == 1){
            k -= 1;
            continue;
        }
        else{
            crystal[i][j] = 1;
        }
    }

    bool finished = false;
    int iteration = 1;
    while(!finished){
        PrintCrystal(crystal);
        cout << "//////////////////////////////////////////////" << endl;
        int count_active_dislocs = 0;
        for (int i = 0; i < CRYSTAL_HEIGHT; i++){
            for (int j = 0; j < CRYSTAL_WIDTH; j++){
                if(crystal[i][j] == iteration){
                    count_active_dislocs++;
                    int direction = directions(generator);  // 1 - влево, 2 - вверх, 3 - вправо, 4 - вниз
                    int cell_to_move_i = i + (direction - 2) % 2;
                    int cell_to_move_j = j + (direction - 3) % 2;
                    if(IsBorderCell(i, j) == true){
                        crystal[i][j] = -1;
                    }
                    else if(CheckAdjacentCells(crystal, i, j, iteration)){
                        crystal[i][j] = -1;
                    }
                    else if(crystal[cell_to_move_i][cell_to_move_j] != 0){
                        crystal[i][j] = -1;
                    }
                    else{
                        crystal[cell_to_move_i][cell_to_move_j] = iteration + 1;
                        crystal[i][j] = 0;
                    }
                }
            }
        }
        if(count_active_dislocs == 0){
            finished = true;
        }
        iteration++;
    }
    return 0;
}