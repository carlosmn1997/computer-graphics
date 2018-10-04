//
// Created by Carlos on 04/10/2018.
//
#ifndef COMPUTER_GRAPHICS_MATRIX_H
#define COMPUTER_GRAPHICS_MATRIX_H

#include <iostream>
#include <cmath>
#include "ReferenceSystem.h"
#include "Vec.h"
using namespace std;

const int N = 4;

class Matrix {
public:
    Matrix() {}

    Matrix(float matrix[N][N]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                this->matrix[i][j] = matrix[i][j];
            }
        }
    }

    void translation(Vec origin){
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if(i==j){
                    matrix[i][j] = 1;
                }
                else{
                    matrix[i][j] = 0;
                }

            }
        }

        matrix[0][3] = origin.getX();
        matrix[1][3] = origin.getY();
        matrix[2][3] = origin.getZ();
    }

    void onlyDirections(){
        matrix[3][0] = 0;
        matrix[3][1] = 0;
        matrix[3][2] = 0;
        matrix[0][3] = 0;
        matrix[1][3] = 0;
        matrix[2][3] = 0;
        matrix[3][3] = 1; // TODO no estoy seguro
    }


    Matrix(ReferenceSystem r) {
        this->matrix[0][0] = r.getI().getX();
        this->matrix[1][0] = r.getI().getY();
        this->matrix[2][0] = r.getI().getZ();
        this->matrix[3][0] = 0;

        this->matrix[0][1] = r.getJ().getX();
        this->matrix[1][1] = r.getJ().getY();
        this->matrix[2][1] = r.getJ().getZ();
        this->matrix[3][1] = 0;

        this->matrix[0][2] = r.getK().getX();
        this->matrix[1][2] = r.getK().getY();
        this->matrix[2][2] = r.getK().getZ();
        this->matrix[3][2] = 0;

        this->matrix[0][3] = r.getOrigin().getX();
        this->matrix[1][3] = r.getOrigin().getY();
        this->matrix[2][3] = r.getOrigin().getZ();
        this->matrix[3][3] = 1;
    }
    void transpose() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                this->matrix[i][j] = matrix[j][i];
            }
        }
    }

    // https://www.programiz.com/cpp-programming/examples/matrix-multiplication
    friend Matrix operator* (const Matrix& first, const Matrix& second){
        float matrix[N][N];
        // inizialize matrix
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j] = 0;
            }
        }
        // Multiplying matrix a and b and storing in array mult.
        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N; ++j){
                for(int k = 0; k < N; ++k) {
                    matrix[i][j] += first.matrix[i][k] * second.matrix[k][j];
                }
            }
        }
        return Matrix(matrix);
    }

    // OJO QUE AUTOCOMPLETA LA ULTIMA FILA
    friend Vec operator* (const Matrix& first, const Vec& second){
        float auxX = first.matrix[0][0]*second.getX() + first.matrix[0][1]*second.getY() + first.matrix[0][2]*second.getZ() + first.matrix[0][3]*second.getType();
        float auxY = first.matrix[1][0]*second.getX() + first.matrix[1][1]*second.getY() + first.matrix[1][2]*second.getZ() + first.matrix[1][3]*second.getType();
        float auxZ = first.matrix[2][0]*second.getX() + first.matrix[2][1]*second.getY() + first.matrix[2][2]*second.getZ() + first.matrix[2][3]*second.getType();
        float type = second.getType();
        return Vec(auxX, auxY, auxZ, type);
    }



private:
    //Columnas
    float matrix[4][4];
};

Vec translate(Vec origin, Vec vec){
    float pepe[N][N];
    Matrix matrix(pepe);
    matrix.translation(origin);
    return matrix*vec;
}

#endif //COMPUTER_GRAPHICS_MATRIX_H
