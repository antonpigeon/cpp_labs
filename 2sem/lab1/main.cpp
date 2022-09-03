#include <iostream>
#include <random>
#include <fstream>

using namespace std;

void PrintCrystal(int *crystal[], int size){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            cout << *(crystal[i] + j)  << " ";
        }
    cout << endl;
    }
}

void PrintDataToFile(int time[], float dislocs_area[], int experiments_count){
    fstream f1("data.txt", ios::out);
    for(int i = 0; i < experiments_count; i++){
        f1 << dislocs_area << " " << time << endl;
    }
    f1.close();
}

bool IsBorderCell(int i, int j, int size){
    return((i == 0) || (j == 0) || (i == size - 1) || (j == size - 1));
}

bool CheckAdjacentCells(int *ptr_crystal[], int i, int j, int value, int size){
    int values_to_check[4] = {*(ptr_crystal[i - 1] + j), *(ptr_crystal[i] + j - 1), *(ptr_crystal[i] + j - 1), *(ptr_crystal[i + 1] + j)};
    for(int i = 0; i < 4; i++){
        if(values_to_check[i] == value or values_to_check[i] == -1){
            return true;
        }
    }
    return false;
}

int main(){
    seed_seq sseq = {1022};
    mt19937 generator(sseq);
    uniform_int_distribution<int> directions(1, 4);

    int experiments = 5;
    int times[experiments];
    float areas[experiments];
    int crystal_size = 3;
    for (int experiment_number = 0; experiment_number < experiments; experiment_number++){
        uniform_int_distribution<int> is (0, crystal_size - 1);
        uniform_int_distribution<int> js (0, crystal_size - 1);
        // Создаем начальную расстановку
        int crystal[crystal_size][crystal_size];
        for (int k = 1; k <= 1; k++){
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

        // Шаги
        bool finished = false;
        int iteration = 1;
        while(!finished){
            int count_active_dislocs = 0;
            for (int i = 0; i < crystal_size; i++){
                for (int j = 0; j < crystal_size; j++){
                    if(crystal[i][j] == iteration){
                        count_active_dislocs++;
                        int direction = directions(generator);  // 1 - влево, 2 - вверх, 3 - вправо, 4 - вниз
                        int cell_to_move_i = i + (direction - 2) % 2;
                        int cell_to_move_j = j + (direction - 3) % 2;

                        int *ptr_crystal[crystal_size];
                        for(int a = 0; a < crystal_size; a++){
                            ptr_crystal[a] = &(crystal[a][0]); // Опасное место
                        }

                        if(IsBorderCell(i, j, crystal_size) == true){
                            crystal[i][j] = -1;
                        }
                        else if(CheckAdjacentCells(ptr_crystal, i, j, iteration, crystal_size)){
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
        times[experiment_number] = iteration - 2;
        areas[experiment_number] = crystal_size;
        crystal_size++;
    }
    PrintDataToFile(times, areas, experiments);
    return 0;
}