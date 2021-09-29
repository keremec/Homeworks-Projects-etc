//
// Created by Kerem Safa on 15.04.2020.
//

#pragma once

#include <iostream>
#include <random>

using namespace std;

class Array {
private:
    int capacity;
    int size;
    int *arr;

    // useful functions
    void reallocate() {
        int *temparr = new int[capacity];
        for (int i = 0; i <= size - 1; i++) {
            temparr[i] = arr[i];
        }
        delete[]arr;
        arr = temparr;
    }

    int findit(int number, int start = 0) {
        for (; start <= size - 1; start++) {
            if (arr[start] == number) {
                return start;
            }
        }
        return -1;
    }

    void deleteitem(int index) {
        for (int i = index; i <= size - 2; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }

public:
    //constructors
    Array() {
        capacity = 5;
        size = 0;
        arr = new int[capacity];
    }

    explicit Array(int cap) {
        capacity = cap;
        size = 0;
        arr = new int[capacity];
    }

    explicit Array(int cap, int data) {
        capacity = cap;
        size = 0;
        arr = new int[capacity];
        for (int i = 0; i < cap; i++) {
            addItem(data);
        }
    }

    Array(const Array &x) {
        capacity = x.capacity;
        arr = new int[capacity];
        size = x.size;
        for (int i = 0; i < size; i++) {
            arr[i] = x.arr[i];
        }
    }

    ~Array() {
        delete[]arr;
    }

    int &operator[](int i) {
        if (i < 0) {
            return arr[size - 1];
        }
        if (i < size) {
            return arr[i];
        }
        else
            return arr[0];
    }

    // in array operations
    int findIndex(int a) {
        return findit(a);
    }

    void addItem(int a) {
        if (size + 1 > capacity) {
            capacity *= 2;
            reallocate();
        }
        arr[size] = a;
        size++;
    }

    void removeIndexItem(int a) {
        if (a <= size - 1 && a >= 0) {
            deleteitem(a);
        }
        else {
            return;
        }
    }

    void removeItem(int a) {
        int control = 0;
        int counter = 0;
        while (control != -1) {
            control = findit(a, control);
            if (control != -1) {
                deleteitem(control);;
                counter++;
            }
        }

        cout << counter << " items (" << a << ") are deleted from the Array" << endl << endl;
    }

    int sizeofarr() const {
        return size;
    }

    int capacityofarr() const {
        return capacity;
    }

    void printItems(bool details = false) {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        if (details) {
            cout << "capacity=" << capacity << " size=" << size << endl;
        }
    }

    void fillrandomnums(int min = 0, int max = 100) {
        uniform_real_distribution<double> distribution(min + 0, max + 1);
        random_device rd;
        default_random_engine generator(rd());
        for (int i = 0; i <= capacity - 1; i++) {
            int num = (int) distribution(generator);
            addItem(num);
        }
    }
};