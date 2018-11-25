#include "Matrix/Matrix.hpp"
#include <iostream>

int main(){

    Matrix t = Matrix(10);
    Matrix t2 = Matrix(10);
    Matrix t3 = Matrix(2, 3);

    Matrix r = t * t2;
    //cout << t << endl;
    //cout << t2 << endl;
    cout << r << endl;

}