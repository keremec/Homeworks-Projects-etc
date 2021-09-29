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

    // in array operations
    void addItem(int a) {
        if (size + 1 > capacity) {
            capacity *= 2;
            reallocate();
        }
        arr[size] = a;
        size++;
    }

    void printItems() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << "capacity=" << capacity << " size=" << size << endl;
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

    //Sort Algorithms
private:
    void swap(int a, int b) {
        int temp;
        temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }

    int median(int l, int u) {
        const int *a = &(max(min(arr[l], arr[u]), min(max(arr[l], arr[u]), arr[(l + u) / 2])));
        return (int(a) - (int) &(arr[0])) / (int) sizeof(arr[0]);
    }

    void insertionSort(int min, int max) {
        int key, j;
        min++;
        max++;
        for (; min < max; min++) {
            key = arr[min];
            j = min - 1;
            while (j >= 0 && arr[j] > key) {
                swap(j + 1, j);
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }

    int partition_M(int min, int max) {
        swap((max + min) / 2, max);
        int pivot = arr[max];
        int i = (min - 1);
        for (int j = min; j <= max - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(i, j);
            }
        }
        swap(i + 1, max);
        return (i + 1);
    }

    int partition_FLM(int min, int max) {
        swap(median(min, max), max);
        int pivot = arr[max];
        int i = (min - 1);
        for (int j = min; j <= max - 1; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(i, j);
            }
        }
        swap(i + 1, max);
        return (i + 1);
    }

    //quick sort "quickSort(0, n-1)"
public:
    void quickSort_M(int min, int max) {
        if (min < max) {
            int pi = partition_M(min, max);
            quickSort_M(min, pi - 1);
            quickSort_M(pi + 1, max);
        }
    }

    void quickSort_M2(int min, int max) {
        if (min < max) {
            if (max - min < 20) {
                insertionSort(min, max);
            } else {
                int pi = partition_M(min, max);
                quickSort_M2(min, pi - 1);
                quickSort_M2(pi + 1, max);
            }
        }
    }

    void quickSort_FLM(int min, int max) {
        if (min < max) {
            int pi = partition_FLM(min, max);
            quickSort_FLM(min, pi - 1);
            quickSort_FLM(pi + 1, max);
        }
    }

    void quickSort_FLM2(int min, int max) {
        if (min < max) {
            if (max - min < 20) {
                insertionSort(min, max);
            } else {
                int pi = partition_FLM(min, max);
                quickSort_FLM2(min, pi - 1);
                quickSort_FLM2(pi + 1, max);
            }
        }
    }

};