#include "Matrix/Matrix.hpp"
#include <iostream>
#include <string>
#include <string.h>

int main(int argc, char* argv[]){
    string matrixfile1;
    string matrixfile2;

    if(argc > 1){
        int i = 1;
        while(i < argc){
            if( strcmp("-file1", argv[i]) == 0){
                matrixfile1 = string( argv[i+1] );
                i++;
            }
            if(strcmp("-file2", argv[i]) == 0){
                matrixfile2 = string( argv[i+1] );
                i++;
            }
            i++;
        }
    }else{
        cout << "Enter first text file with matrix value:" << endl;
        cin >> matrixfile1;
        cout << "Enter second text file with matrix value:" << endl;
        cin >> matrixfile2;
    }

    if(matrixfile1.empty() || matrixfile2.empty()){
        cout << "Only one matrix file entered\nExiting" << endl;
        return 0;
    }

    Matrix mat1 = Matrix::fromString( Matrix::fromFile(matrixfile1) );
    cout << "Matrix 1:\n" <<mat1 << endl;
    Matrix mat2 = Matrix::fromString( Matrix::fromFile(matrixfile2) );
    cout << "Matrix 2:\n" <<mat2 << endl;

    cout << "Result Matrix:" << endl;
    Matrix mat3 = mat1 * mat2;
    cout << mat3 << endl;

    return 0;
}