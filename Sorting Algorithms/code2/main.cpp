//
// Created by Kerem Safa on 15.04.2020.
//

#include "ArrayLite.h"
#include <ctime>

#define ARRAY_LENGTH 10000
#define MIN_NUMBER 0
#define MAX_NUMBER 10000

int main() {

    int n = ARRAY_LENGTH;
    int input;
    clock_t c1;
    Array a(n);
    a.fillrandomnums(MIN_NUMBER, MAX_NUMBER);

    cout << "Random array created!" << " Length:" << ARRAY_LENGTH << " Max:" << MAX_NUMBER << " Min:" << MIN_NUMBER
         << endl;
    cout << "1. Quick sort, pivot as the middle element of the array." << endl;
    cout << "2. Quick sort, pivot as the median of the first, last, and middle elements of the array." << endl;
    cout << "3. Quick Sort + Insertion Sort, pivot as the middle element of the array." << endl;
    cout << "4. Quick Sort + Insertion Sort, pivot as the median of the first, last, and middle elements of the array."
         << endl;
    cout << "9. Print the Array" << endl;
    cout << "0. Exit Program" << endl;

    while (true) {
        cin >> input;
        switch (input) {
            case 1:
                c1 = clock();
                a.quickSort_M(0, n - 1);
                cout << "Done! CPU time is:" << clock() - c1 << "\nEnter '9' for print the sorted array!" << endl;
                break;
            case 2:
                c1 = clock();
                a.quickSort_FLM(0, n - 1);
                cout << "Done! CPU time is:" << clock() - c1 << "\nEnter '9' for print the sorted array!" << endl;
                break;
            case 3:
                c1 = clock();
                a.quickSort_M2(0, n - 1);
                cout << "Done! CPU time is:" << clock() - c1 << "\nEnter '9' for print the sorted array!" << endl;
                break;
            case 4:
                c1 = clock();
                a.quickSort_FLM2(0, n - 1);
                cout << "Done! CPU time is:" << clock() - c1 << "\nEnter '9' for print the sorted array!" << endl;
                break;
            case 9:
                a.printItems();
                break;
            case 0:
                return 0;
            default:
                cout << "Invalid command, try again!" << endl;
                break;
        }
    }
}