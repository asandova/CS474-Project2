#include "Matrix/Matrix.hpp"
#include <iostream>

int main(){

    Matrix mat1 = Matrix(3,2);
    mat1.at(0,0) = 1;
    mat1.at(0,1) = 4;
    mat1.at(1,0) = 2;
    mat1.at(1,1) = 5;
    mat1.at(2,0) = 3;
    mat1.at(2,1) = 6;

    Matrix mat2 = Matrix(2,3);
    mat2.at(0,0) = 8;
    mat2.at(0,1) = 7;
    mat2.at(0,2) = 6;
    mat2.at(1,0) = 5;
    mat2.at(1,1) = 4;
    mat2.at(1,2) = 3;

    Matrix mat3 = mat1 * mat2;
    cout << mat3 << endl;

    return 0;
}