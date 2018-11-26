#include "Matrix.hpp"

#include <vector>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

Matrix::Matrix(int size){
    cout << "size: " << size << endl;
    Rows = size;
    Columns = size;
    matrix = vector<vector<int> >();
    cout << "Matrix size: " << matrix.size() << endl;
    matrix.reserve(size);
    for(int i = 0; i < size; i++){
        matrix.push_back( vector<int>(size,2) );
    }
    cout << "Matrix size: " << matrix.size() << endl;
}

Matrix::Matrix(int rows, int cols){
    Rows = rows;
    Columns = cols;
    matrix = vector<vector<int> >();
    matrix.reserve(rows);
    for(int i = 0; i < rows; i++){
        matrix.push_back( vector<int>(cols, 0));
    } 
}

Matrix operator*(const Matrix& mat1, const Matrix& mat2){
    if(mat1.getColumnSize() != mat2.getRowSize() ){
        cout << "ERROR: Incompatable matrices\n" << endl;
        exit(1);
    }
    Matrix result = Matrix(mat1.getRowSize(), mat2.getColumnSize());
    //cout << result << endl;
    int threadSize = result.Rows * result.Columns;

    //thread setup
    pthread_t threads[threadSize];
    thread_args* threadargs;
    threadargs = (thread_args*) malloc(threadSize * sizeof(thread_args));
    pthread_attr_t attr;
    void* status;
    int thread_id = 0;
    int rc;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //printf("max threads: %d\n",threadSize);
    //printf("before loop\n");

    //multiplication loop
    for(int i = 0; i < result.Rows; i++){
        for(int j = 0; j < result.Columns; j++, thread_id++){;
            threadargs[thread_id].A = &mat1;
            threadargs[thread_id].B = &mat2;
            threadargs[thread_id].C = &result;
            threadargs[thread_id].i = i;
            threadargs[thread_id].j = j;
            threadargs[thread_id].threadID = thread_id;
            threadargs[thread_id].k_max = mat1.getColumnSize();
            //printf("creating Thread ID: %d, i: %d, j: %d\n",thread_id,i,j);

            //create thread
            rc = pthread_create(&threads[thread_id], &attr, Matrix::multWorker, (void*)&threadargs[thread_id]);
            if( rc ){
                cout << "Error: unable to create thread" << endl;
                exit(-1);
            }
        }
    }
    //join threads
    pthread_attr_destroy(&attr);
    for(int i = 0; i < threadSize; i++){
        rc = pthread_join(threads[i],&status);
        if(rc){
            cout << "Error: unable to join thread" << endl;
            exit(-1);
        }
    }
    free(threadargs);
    return result;
}

void *Matrix::multWorker(void *data){
    //Thread function
    thread_args *d;
    d = (thread_args *) data;
    int temp = 0;
    for(int k = 0; k < d->k_max; k++){
        temp += (d->A)->at(d->i,k) * (d->B)->at(k,d->j);
        // printf("temp = %d(temp) + %d(i: %d, k:%d) * %d(k: %d, j:%d)\n",temp,d->i,k,k, d->j);
    }
    (d->C)->at(d->i,d->j) = temp;
    //printf("Thread ID: %d -- C[%d,%d] = %d\n",d->threadID,d->i,d->j, (d->C)->at(d->i,d->j) );
    pthread_exit(NULL);
}

ostream& operator<<(ostream& out,const Matrix& mat){
    printf("Rows %d, Colums %d\n",mat.Rows, mat.Columns);
    for(int r = 0; r < mat.Rows; r++){
        for(int c = 0; c < mat.Columns; c++){
            if(c + 1 == mat.Columns ){
                out << mat.at(r,c) << " " << endl;
            }else{
                out << mat.at(r,c) << ", ";
            }
        }
    }
    return out;
}
/*
string Matrix::fromFile(string filename){
    int rows = 0;
    int col = 0;
    string matrixString = "";
    ifstream in;
    in.open(filename, ifstream::in);

    if(in.is_open() ){
        char C;
        while(!in.fail()){
            C = in.get();
            matrixString += C;
        }
        matrixString.resize(matrixString.size()-1);
    }
    return matrixString;
}

Matrix Matrix::fromString(string sMatrix){
    int row = 0;
    int col = 0;
    Matrix mat = Matrix(1,1);
    for(int i = 0; i < sMatrix.size(); i++){
        if(sMatrix[i] == '\n'){
            row++;
            mat.addRow();
        }
        else if( isdigit(sMatrix[i] ){

            string num = "";
            for(; i < sMatrix.size(); i++){
                if(!isdigit(sMatrix[i])){
                    

                    break;
                }
                else{
                    num += sMatrix[i];
                }
            }
        }
    }
    return mat;
}
*/
int& Matrix::at(int r, int c){
    if( (r > Rows || c > Columns)
        || (r < 0 || c < 0) ) {
        printf("Out of bounds");
        exit(1);
    }
    return matrix.at(r).at(c);
}
const int& Matrix::at(int r, int c)const{
    return matrix.at(r).at(c);
}

int Matrix::getColumnSize()const{
    return Columns;
}
int Matrix::getRowSize()const{
    return Rows;
}

void Matrix::addRow(){
    matrix.push_back(vector<int>(Columns, 0) );
}
void Matrix::addColumn(){
    for(int i = 0; i < Rows;i++){
        matrix[i].push_back(0);
    }
}