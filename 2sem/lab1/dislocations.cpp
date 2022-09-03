#include <iostream>
#include <random>
#include <fstream>

using namespace std;

void PrintCrystal(int dislocations[][3], int dislocations_count, int size){
    int crystal[size][size];
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            crystal[i][j] = 0;
        }
    }
    for(int k = 0; k < dislocations_count; k++){
        crystal[dislocations[k][0]][dislocations[k][1]] = dislocations[k][2] + 2;
    }
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            cout << crystal[i][j]  << " ";
        }
    cout << endl;
    }
}

bool IsBorderCell(int i, int j, int size){
    return((i == 0) || (j == 0) || (i == size - 1) || (j == size - 1));
}

int FindDislocation(int array[][3], int dislocations_count, int i, int j){
    for(int k = 0; k < dislocations_count; k++){
        if(array[k][0] == i and array[k][1] == j){
            return k;
        }
    }
    return -1;
}

bool CheckAdjacentCells(int dislocations[][3], int dislocations_count, int i, int j, int startidx, int endidx){
    int is_to_check[] = {i - 1, i, i + 1, i};
    int js_to_check[] = {j, j - 1, j, j + 1};
    for(int s = 0; s < 4; s++){
        int k = FindDislocation(dislocations, dislocations_count, is_to_check[s], js_to_check[s]);
        if(k != -1){
            if (dislocations[k][2] == -1 || (k >= startidx && k < endidx)){
                return true;
            }
        }
    }
    return false;
}

int main(){
    seed_seq sseq = {1, 2, 3, 4};
    mt19937 generator(sseq);
    uniform_int_distribution<int> directions(1, 4);

    int experiments = 4000;
    int results[experiments] = {0};
    float area_ratios[experiments] = {0};
    for(int experiment = 1; experiment <= experiments; experiment++){
        cout << experiment << endl;
        int crystal_size = 100;
        int dislocations_count = experiment/10 + 1;
        area_ratios[experiment - 1] = dislocations_count*1.0/(crystal_size * crystal_size * 1.0);
        bool finished = false;

        uniform_int_distribution<int> idxes (0, crystal_size - 1);
        int dislocations[dislocations_count][3];
        int crystal[crystal_size][crystal_size];
        for(int i = 0; i < crystal_size; i++){
            for(int j = 0; j < crystal_size; j++){
                crystal[i][j] = 0;
            }
        }
        for(int k = 0; k < dislocations_count; k++){
            dislocations[k][2] = 0;
            int i = idxes(generator), j = idxes(generator);
            while(crystal[i][j] == 1){
                i = idxes(generator);
                j = idxes(generator);
            }
            crystal[i][j] = 1;
            dislocations[k][0] = idxes(generator);
            dislocations[k][1] = idxes(generator);
        }
        //if(experiment == 18){
        //   PrintCrystal(dislocations, dislocations_count, crystal_size);
        //    cout << "////////////// \n";
        //}

        int iteration = 0;
        while(!finished){
            int count_active_dislocs = 0;
            for(int i = 0; i < dislocations_count; i++){
                if(dislocations[i][2] != -1){
                    count_active_dislocs++;
                }
                int direction = directions(generator);  // 1 - влево, 2 - вверх, 3 - вправо, 4 - вниз
                int cell_to_move_i = dislocations[i][0] + (direction - 2) % 2;
                int cell_to_move_j = dislocations[i][1] + (direction - 3) % 2;

                if(IsBorderCell(dislocations[i][0], dislocations[i][1], crystal_size) == true){
                    dislocations[i][2] = -1;
                    count_active_dislocs--;
                }
                else if(CheckAdjacentCells(dislocations, dislocations_count, dislocations[i][0], dislocations[i][1], i + 1, dislocations_count)){
                    dislocations[i][2] = -1;
                    count_active_dislocs--;
                }
                else if(FindDislocation(dislocations, dislocations_count, cell_to_move_i, cell_to_move_j) != -1){
                    dislocations[i][2] = -1;
                    count_active_dislocs--;
                }
                else{
                    dislocations[i][0] = cell_to_move_i;
                    dislocations[i][1] = cell_to_move_j;
                }
            }
            if(count_active_dislocs <= 0){
                finished = true;
            }
            else{
                iteration++;
            }
            //if(experiment == 18){
            //    PrintCrystal(dislocations, dislocations_count, crystal_size);
            //    cout << "\n" << "//////////////////" << "\n";
            //}
        }
        results[experiment - 1] = iteration;
    }
    fstream f("data2.txt", ios::out);
    for(int i = 1; i <= experiments; i++){
        f << i << " " << area_ratios[i- 1] << " " << results[i - 1] << "\n";
    }
    return 0; 
}