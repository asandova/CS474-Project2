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

    void addRow();
    void addColumn();

    public:
    Matrix(int size);//creates a square matrix
    Matrix(int rows, int col);// creates a MxN matrix
    friend Matrix operator*(const Matrix& mat1, const Matrix& mat2);
    friend ostream& operator<<(ostream& out,const Matrix& mat);
    //static string fromFile(string filename);
    //static Matrix fromString(string matrix);
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