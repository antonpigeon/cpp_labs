#include <iostream>
template<typename Field, size_t M, size_t N>
class Matrix {
    public:
        Field mat[M][N];
    public:
        //friend Matrix operator+(const Matrix<typename Field, size_t M, size_t N> &lha, const Matrix<typename Field, size_t M, size_t N> &rha);
        //friend operator-(const Matrix<typename Field, size_t M, size_t N> &lha, const Matrix<typename Field, size_t M, size_t N> &rha);
        //friend operator*(const Matrix<typename Field, size_t M, size_t N> &lha, const Matrix<typename Field, size_t N, size_t K> &rha);
};

template<typename Field, size_t M, size_t N>
Matrix<Field, M, N> operator+(const Matrix<Field, M, N>& lha, const Matrix<Field, M, N>& rha) {
    Matrix<Field, M, N> res;
    for(size_t i = 0; i < M; i++){
        for(size_t j = 0; j < N; j++){
            res.mat[i][j] = lha.mat[i][j] + rha.mat[i][j];
        }
    }
    return res;
}

template<typename Field, size_t M, size_t N>
Matrix<Field, M, N> operator-(const Matrix<Field, M, N>& lha, const Matrix<Field, M, N>& rha) {
    Matrix<Field, M, N> res;
    for(size_t i = 0; i < M; i++){
        for(size_t j = 0; j < N; j++){
            res.mat[i][j] = lha.mat[i][j] - rha.mat[i][j];
        }
    }
    return res;
}

template<typename Field, size_t M, size_t N, size_t K>
Matrix<Field, M, K> operator*(const Matrix<Field, M, N>& lha, const Matrix<Field, N, K>& rha) {
    Matrix<Field, M, K> res;
    for(size_t i = 0; i < M; i++){
        for(size_t j = 0; j < K; j++){
            Field sum = 0;
            for(size_t curr = 0; curr < N; curr++){
                sum += lha.mat[i][curr] * rha.mat[curr][j];
            }
            res.mat[i][j] = sum;
        }
    }
    return res;
}

int main(){
    Matrix<int, 3, 3> A;
    Matrix<int, 3, 1> B;
    int arr[3][3] = {{1, 2, 3}, {0, 4, 0}, {2, 2, 1}};
    for(int i = 0; i < 3; i++){
        for(int j  = 0; j < 3; j++){
            A.mat[i][j] = arr[i][j];
        }
    }
    int barr[3] = {1, 1, 1};
    for(int i = 0; i < 3; i++){
        B.mat[i][0] = barr[i];
    }
    auto C = A * B;
    std::cout << C.mat[0][0] << C.mat[1][0] << C.mat[2][0] <<std::endl;
    return 0;
}