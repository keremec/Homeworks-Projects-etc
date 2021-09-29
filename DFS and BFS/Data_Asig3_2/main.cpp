//
// Created by Kerem Safa on 4.05.2020.
//

#include <iostream>

#include "ArrayLite.h"
#include "MatrixLite.h"

using namespace std;

template<class T>
void BFS(class Matrix<T> &M, int row = 0) {
    int totalcols = M.howmanycols();
    int totalrows = M.howmanyrows();
    if (row >= totalrows) { row = 0; }
    Array Arr;
    Array col(totalrows, 0); //stores iterator location of each rows
    int idx = 0;
    Arr.addItem(row);
    while (idx != totalrows - 1) {
        row = Arr[idx];
        for (; col[row] < totalcols; col[row]++) {
            if (M[row][col[row]] != 0) {
                if (Arr.findIndex(col[row]) == -1) {
                    Arr.addItem(col[row]);
                }
            }
        }
        idx++;
    }
    cout << "BFS being calculated..." << endl;
    Arr.printItems();
}

template<class T>
void DFS(class Matrix<T> &M, int row = 0) {
    int totalcols = M.howmanycols();
    int totalrows = M.howmanyrows();
    if (row >= totalrows) { row = 0; }
    Array Arr;
    Array col(totalrows, 0); //stores iterator location of each rows
    int idx = 0;
    Arr.addItem(row);
    bool idxdec = false; // true if idx decreased as last action
    while (idx != 1) {
        row = Arr[idx];
        for (; col[row] < totalcols; col[row]++) {
            if (M[row][col[row]] != 0) {
                if (Arr.findIndex(col[row]) == -1) {
                    Arr.addItem(col[row]);
                    row = col[row];
                    col[row]--;
                    if (idxdec) {
                        idx = Arr.sizeofarr() - 1;
                        idxdec = false;
                    }
                    else {
                        idx++;
                        idxdec = false;
                    }
                }
            }
        }
        idx--;
        idxdec = true;
    }
    cout << "DFS being calculated..." << endl;
    Arr.printItems();
}

template<class T>
int print_menu(Matrix<T> &M) {
    cout << M.howmanyrows() << "x" << M.howmanycols() << " Matrix is read and created..." << endl;
    cout << "Adjacency Matrix: " << endl;
    printmatrix(M);
    cout << "Enter start vertex (between 0 to " << M.howmanycols() - 1 << ") for BFS and DFS methods: " << endl;
    int input;
    cin >> input;
    return input;
}

int main() {

    ifstream file("graph_template.txt");
    Matrix<int> A(rownum(file), colnum(file));
    Fill_Matrix(file, A);
    int inp = print_menu(A);
    BFS(A, inp);
    DFS(A, inp);
    return 0;
}
