#include <iostream>
#include <cmath>
#include <cstring>

int calcDeterminantArray(int** arr, int n){
    if(n==1) return arr[0][0];
    else{
        int res = 0;
        for(int i = 0; i < n; i++){
            int** minor = new int*[n - 1];
            for(int j = 0; j < n - 1; j++){
                minor[j] = new int[n - 1];
            }
            for(int j= 1; j < n; j++){
                int g = 0;
                for(int k = 0; k < n; k++){
                    if(k != i){
                        minor[j - 1][g] = arr[j][k];
                        g++;
                    }
                }
            }
            res += arr[0][i]*std::pow(-1, i)*calcDeterminantArray(minor, n - 1);
            for(int i = 0; i < n - 1; i++){
                delete[] minor[i];
            }
            delete[] minor;   
        }
        return res;
    }
}

class Matrix {
    public:
        Matrix(int arr[], size_t n_elements) : size(std::sqrt(n_elements)){
            mat = new int*[size];
            for(int i = 0; i < size; i++){
                mat[i] = new int[size];
                for(int j = 0; j < size; j++){
                    mat[i][j] = arr[i*size + j];
                }
            }
        }

        Matrix(int element, size_t n_elements) : size(std::sqrt(n_elements)){
            mat = new int*[size];
            for(int i = 0; i < size; i++){
                mat[i] = new int[size];
                for(int j = 0; j < size; j++){
                    mat[i][j] = element;
                }
            }
        }

        Matrix() : size(1){
            mat = new int*[1];
            mat[0] = new int[1];
            mat[0][0] = 1;
        }

        Matrix(const Matrix& other) : size(other.size){
            mat = new int*[size];
            for(int i = 0; i < size; i++){
                mat[i] = new int[size];
                for(int j = 0; j < size; j++){
                    mat[i][j] = other.mat[i][j];
                }
            }
        }

        void printMatrix() const{
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){
                    std::cout << mat[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
    
        int calcDeterminant(){
            return calcDeterminantArray(mat, size);
        }
    
        void calcSquare() {
            int** res_mat = new int*[size];
            for(int i = 0; i < size; i++){
                res_mat[i] = new int[size];
                for(int j = 0; j < size; j++){
                    int curr_field = 0;
                    for(int p = 0; p < size; p++){
                        curr_field += mat[i][p] *mat[p][j];
                    }
                    res_mat[i][j] = curr_field;
                }
            }
            for(int i = 0; i < size; i++){
                std::memcpy(mat[i], res_mat[i], size*4);
                delete[] res_mat[i];
            }
            delete[] res_mat;
            
        }

        void matTranspose(){
            for(int i = 0; i < size; i++){
                for(int j = i; j < size; j++){
                    std::swap(mat[i][j], mat[j][i]);
                }
            }
        }

        ~Matrix(){
            for(int i = 0; i < size; i++){
                delete[] mat[i];
            }
            delete[] mat;
        }

    private:
        int** mat;
        int size;        
};
