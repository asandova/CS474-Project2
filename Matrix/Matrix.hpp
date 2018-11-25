#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Matrix{

    private:
    vector< vector<int> > matrix;
    int Rows;
    int Columns;
    static void *multWorker(void *data);

    public:
    Matrix(int size);//creates a square matrix
    Matrix(int rows, int col);// creates a MxN matrix 
    friend Matrix operator*(const Matrix& mat1, const Matrix& mat2);
    friend ostream& operator<<(ostream& out,const Matrix& mat);
    int& at(int r, int c);
    const int& at(int r, int c)const;
    int getColumnSize()const;
    int getRowSize()const;
};

typedef struct thread_data{
    int threadID;
    const Matrix* A;
    const Matrix* B;
    Matrix* C;
    int i;
    int j;
    int k_max;
} thread_args;

#endif