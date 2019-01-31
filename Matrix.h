//
// Created by Carlos on 04/10/2018.
//
#ifndef COMPUTER_GRAPHICS_MATRIX_H
#define COMPUTER_GRAPHICS_MATRIX_H
//#define N 4

const int N = 4;

#include <iostream>
#include <cmath>
#include "Vec.h"
#include<bits/stdc++.h>
using namespace std;


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

    void transpose() {
        float aux[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                aux[i][j] = this->matrix[i][j];
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                this->matrix[i][j] = aux[j][i];
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

    friend bool operator== (const Matrix& first, const Matrix& second){
        bool ok = true;
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                if(ok){
                    ok = first.matrix[i][j] == second.matrix[i][j];
                }
            }
        }
        return ok;
    }


    //https://www.geeksforgeeks.org/adjoint-inverse-matrix/

    // C++ program to find adjoint and inverse of a matrix
// Function to get cofactor of A[p][q] in temp[][]. n is current
// dimension of A[][]
    static void getCofactor(float A[N][N], float temp[N][N], int p, int q, int n)
    {
        int i = 0, j = 0;

        // Looping for each element of the matrix
        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                // Copying into temporary matrix only those element
                // which are not in given row and column
                if (row != p && col != q)
                {
                    temp[i][j++] = A[row][col];

                    // Row is filled, so increase row index and
                    // reset col index
                    if (j == n - 1)
                    {
                        j = 0;
                        i++;
                    }
                }
            }
        }
    }

/* Recursive function for finding determinant of matrix.
n is current dimension of A[][]. */
    static float determinant(float A[N][N], float n)
    {
        float D = 0; // Initialize result

        // Base case : if matrix contains single element
        if (n == 1)
            return A[0][0];

        float temp[N][N]; // To store cofactors

        int sign = 1; // To store sign multiplier

        // Iterate for each element of first row
        for (int f = 0; f < n; f++)
        {
            // Getting Cofactor of A[0][f]
            Matrix::getCofactor(A, temp, 0, f, n);
            D += sign * A[0][f] * determinant(temp, n - 1);

            // terms are to be added with alternate sign
            sign = -sign;
        }

        return D;
    }

// Function to get adjoint of A[N][N] in adj[N][N].

    void adjoint(float A[N][N],float adj[N][N])
    {
        if (N == 1)
        {
            adj[0][0] = 1;
            return;
        }

        // temp is used to store cofactors of A[][]
        float sign = 1, temp[N][N];

        for (int i=0; i<N; i++)
        {
            for (int j=0; j<N; j++)
            {
                // Get cofactor of A[i][j]
                getCofactor(A, temp, i, j, N);

                // sign of adj[j][i] positive if sum of row
                // and column indexes is even.
                sign = ((i+j)%2==0)? 1: -1;

                // Interchanging rows and columns to get the
                // transpose of the cofactor matrix
                adj[j][i] = (sign)*(determinant(temp, N-1));
            }
        }
    }

// Function to calculate and store inverse, returns false if
// matrix is singular
    Matrix inverse()
    {
        // Find determinant of A[][]
        float inverse[N][N];

        float A[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                A[i][j] = matrix[i][j];
            }
        }

        float det = determinant(A, N);
        if (det == 0)
        {
            cout << "Singular matrix, can't find its inverse";
            std::exit(1);
        }

        // Find adjoint
        float adj[N][N];
        adjoint(A, adj);

        // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
        for (int i=0; i<N; i++)
            for (int j=0; j<N; j++)
                inverse[i][j] = adj[i][j]/float(det);

        return Matrix(inverse);
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
