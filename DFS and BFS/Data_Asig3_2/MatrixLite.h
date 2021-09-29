//
// Created by Kerem Safa on 01.05.2020.
//
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

template<class T>
class Matrix {
public:
    Matrix(int rows, int cols) {
        matrixData = vector<vector<T>>(rows, vector<T>(cols, 0));
    }

    vector<T> &operator[](int i) {
        return matrixData[i];
    }

    int howmanyrows() {
        return matrixData.capacity();
    }

    int howmanycols() {
        return matrixData[0].capacity();
    }

private:
    vector<vector<T>> matrixData;
};

template<class T>
void copy(Matrix<T> &from, Matrix<T> &to) {
    int rows = from.howmanyrows();
    int cols = from.howmanycols();
    if (rows != to.howmanyrows()) {
        cout << "Error Copy" << endl;
        return;
    }
    if (cols != to.howmanycols()) {
        cout << "Error Copy" << endl;
        return;
    }
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            to[x][y] = from[x][y];
        }
    }
}

template<class T>
void push_back_row(Matrix<T> &mtrx, T val) {
    int rows = mtrx.howmanyrows();
    int cols = mtrx.howmanycols();
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            mtrx[x][y] = val;
        }
    }
}

template<class T>
void printmatrix(Matrix<T> &mtrx) {
    int rows = mtrx.howmanyrows();
    int cols = mtrx.howmanycols();
    cout << "   ";
    for (int x = 0; x < cols; x++) { cout << x << " "; }
    cout << endl;
    cout << "   ";
    for (int x = 0; x < cols; x++) { cout << "_ "; }
    cout << endl;
    for (int x = 0; x < rows; x++) { cout << x << " |" << mtrx[x] << endl; }
}

ostream &operator<<(ostream &os, const vector<int> &input) {
    for (auto const &i: input) {
        os << i << " ";
    }
    return os;
}

int rownum(ifstream &file) {
    int rownum = 0;
    string tempstr;
    while (getline(file, tempstr)) {
        int pos = tempstr.find(':');
        int row;
        string sub = tempstr.substr(0, pos);
        istringstream toint(sub);
        toint >> row;
        rownum = fmax(row, rownum);
    }
    file.clear();
    file.seekg(0, ios::beg);
    return rownum + 1;
}

int colnum(ifstream &file) {
    int colnum = 0;
    string tempstr;
    while (getline(file, tempstr)) {
        int pos = tempstr.find(':');
        int col;
        string sub = tempstr.substr(pos + 1);
        istringstream toint(sub);
        while (toint >> col) {
            colnum = fmax(col, colnum);
        }
    }
    file.clear();
    file.seekg(0, ios::beg);
    return colnum + 1;
}

template<class T>
void Fill_Matrix(ifstream &file, class Matrix<T> &M) {
    int row = 0;
    int col = 0;
    string tempstr;
    while (getline(file, tempstr)) {
        int pos = tempstr.find(':');
        string sub = tempstr.substr(0, pos);
        istringstream toint(sub);
        toint >> row;
        sub = tempstr.substr(pos + 1);
        istringstream toint_2(sub);
        while (toint_2 >> col) {
            M[row][col] = 1;
        }
    }
    file.clear();
    file.seekg(0, ios::beg);

}