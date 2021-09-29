//
// Created by Kerem Safa on 4.05.2020.
//
#include "MyTree.h"

int main() {

    BTree<char> A;

    A.additem('D');
    printitems(A.getroot());
    cout << endl;
    A.additem('D');
    printitems(A.getroot());
    cout << endl;
    A.additem('E');
    printitems(A.getroot());
    cout << endl;
    A.additem('B');
    printitems(A.getroot());
    cout << endl;
    A.additem('A');
    printitems(A.getroot());
    cout << endl;
    A.additem('C');
    printitems(A.getroot());
    cout << endl;
    A.additem('D');
    printitems(A.getroot());
    cout << endl;
    A.additem('B');
    printitems(A.getroot());
    cout << endl;


    A.delitem('D');
    printitems(A.getroot());
    cout << endl;
    A.delitem('D');
    printitems(A.getroot());
    cout << endl;
    A.delitem('D');
    printitems(A.getroot());
    cout << endl;
    A.delitem('B');
    printitems(A.getroot());
    cout << endl;
    A.delitem('B');
    printitems(A.getroot());
    cout << endl;
    A.delitem('C');
    printitems(A.getroot());
    cout << endl;
    A.delitem('E');
    printitems(A.getroot());
    cout << endl;

    return 0;
}
