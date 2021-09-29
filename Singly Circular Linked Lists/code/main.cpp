//
// Created by Kerem Safa on 20.03.2020.
//
#include <iostream>
#include <cassert>

using namespace std;

template<class Type>
struct nodeType {
    Type info;
    nodeType<Type> *link;
};

template<class Type>
class circularLinkedList {
public:
    const circularLinkedList<Type> &operator=(const circularLinkedList<Type> &);

    //Overloads the assignment operator.
    void initializeList();

    //Initializes the list to an empty state.
    //Postcondition: first = NULL, last = NULL,
    //                count = 0
    bool isEmptyList();
    //Function to determine whether the list is empty.
    //Postcondition: Returns true if the list is empty;
    //               otherwise, returns false.

    void print() const;

    int length();

    //Function to return the number of nodes in the
    //list.
    //Postcondition: The value of count is returned.
    void destroyList();

    //Function to delete all the nodes from the list.
    //Postcondition: first = NULL, last = NULL,
    //               count = 0
    Type front();

    //Function to return the first element of the list.
    //Precondition: The list must exist and must not be
    //empty.
    //Postcondition: If the list is empty, then the
    //               program terminates; otherwise,
    //               the first element of the list is
    //               returned.
    Type back();
    //Function to return the last element of the
    //list.
    //Precondition: The list must exist and must not
    //be empty.
    //Postcondition: If the list is empty, then the
    //               program terminates; otherwise,
    //               the last element of the list is
    //               returned.

    bool search(const Type &searchItem);
    //Function to determine whether searchItem is in
    //the list.
    //Postcondition: Returns true if searchItem is found
    //               in the list; otherwise, it returns
    //               false.

    void insertNode(const Type &newitem);

    void deleteNode(const Type &deleteItem);
    //Function to delete deleteItem from the list.
    //Postcondition: If found, the node containing
    //               deleteItem is deleted from the
    //                list, first points to the first
    //                node, and last points to the last
    //                node of the updated list.

    circularLinkedList();
    //Default constructor
    //Initializes the list to an empty state.
    //Postcondition: first = NULL, last = NULL,
    //               count = 0

    circularLinkedList(const circularLinkedList<Type> &otherList);
    //Copy constructor

    ~circularLinkedList();
    //Destructor
    //Deletes all the nodes from the list.
    //Postcondition: The list object is destroyed.

protected:
    int count;        //variable to store the number of
    //elements in the list
    nodeType<Type> *first; //pointer to the first node of
    //the list
    nodeType<Type> *last;  //pointer to the last node of
    //the list
private:
    void copyList(const circularLinkedList<Type> &otherList);
    //Function to make a copy of otherList.
    //Postcondition: A copy of otherList is created
    //               and assigned to this list.
};

template<class Type>
void circularLinkedList<Type>::initializeList() {
    count = 0;
    first = NULL;
    last = NULL;
}

template<class Type>
bool circularLinkedList<Type>::isEmptyList() {
    return (count == 0);
}

template<class Type>
int circularLinkedList<Type>::length() {
    return count;
}

template<class Type>
Type circularLinkedList<Type>::front() {
    if (isEmptyList()) { return NULL; }
    return first->info;
}

template<class Type>
Type circularLinkedList<Type>::back() {
    if (isEmptyList()) { return NULL; }
    return last->info;
}

template<class Type>
bool circularLinkedList<Type>::search(const Type &searchItem) {
    nodeType<Type> *it;
    it = first;
    for (int i = 1; i <= count; i++, it = it->link) {
        if (searchItem == it->info) {
            return true;
        }
    }
    return false;
}

template<class Type>
void circularLinkedList<Type>::insertNode(const Type &newitem) {
    nodeType<Type> *it;
    it = last;
    last = new nodeType<Type>;
    last->info = newitem;
    if (isEmptyList()) {
        first = last;
        last->link = first;
        count++;
        return;
    }
    it->link = last;
    last->link = first;
    count++;
    return;
}

template<class Type>
void circularLinkedList<Type>::deleteNode(const Type &deleteItem) {
    if (isEmptyList()) { return; }
    nodeType<Type> *it;
    nodeType<Type> *trash;
    it = first;
    // middle nodes
    while (it->link != last) {
        if (it->link->info == deleteItem) {
            trash = it->link;
            it->link = it->link->link;
            delete trash;
            count--;
        } else { it = it->link; }
    }
    // last node
    if (it->link->info == deleteItem && count > 1) {
        trash = it->link;
        it->link = first;
        last = it;
        delete trash;
        count--;
    }
    //first node
    if (first->info == deleteItem) {
        trash = first;
        if (count == 1) {
            first = NULL;
            last = NULL;
            delete trash;
            count--;
            return;
        }
        first = first->link;
        last->link = first;
        delete trash;
        count--;
    }
}

template<class Type>
void circularLinkedList<Type>::destroyList() {
    nodeType<Type> *trash;
    while (count != 0) {
        trash = first;
        if (count == 1) {
            first = NULL;
            last = NULL;
            delete trash;
            count--;
            return;
        }
        first = first->link;
        last->link = first;
        delete trash;
        count--;
    }
}

template<class Type>
void circularLinkedList<Type>::print() const {
    nodeType<Type> *it;
    it = first;
    for (int i = 1; i <= count; i++, it = it->link) {
        cout << it->info << " ";
    }
    cout << endl;
}

template<class Type>
circularLinkedList<Type>::circularLinkedList() {
    initializeList();
}

template<class Type>
circularLinkedList<Type>::~circularLinkedList() {
    destroyList();
}

template<class Type>
void circularLinkedList<Type>::copyList(const circularLinkedList<Type> &otherList) {
    if (count != 0) { destroyList(); }
    if (otherList.count == NULL) { return; }
    nodeType<Type> *it;
    it = otherList.first;
    for (int i = 1; i <= otherList.count; i++) {
        insertNode(it->info);
        it = it->link;
    }
}

template<class Type>
circularLinkedList<Type>::circularLinkedList(const circularLinkedList<Type> &otherList) {
    initializeList();
    copyList(otherList);
}

template<class Type>
const circularLinkedList<Type> &circularLinkedList<Type>::operator=(const circularLinkedList<Type> &otherList) {
    if (this != &otherList) {
        copyList(otherList);
    }
    return *this;
}


int main() {

    circularLinkedList<int> list1, list2;
    list1.insertNode(1);
    list1.insertNode(2);
    list1.insertNode(3);
    cout << "list1: ";
    list1.print();
    cout << "list1: ";
    list2.print();
    cout << "is list 1 empty = " << list1.isEmptyList() << endl;
    cout << "is list 2 empty = " << list2.isEmptyList() << endl;
    cout << "length of list1: " << list1.length() << endl;
    cout << "first element of list1: " << list1.front() << endl;
    cout << "last element of list2: " << list2.back() << endl;
    cout << "search 2 in list1= " << list1.search(2) << endl;
    cout << "search 7 in list1= " << list1.search(7) << endl;
    cout << "search 5 in list2= " << list2.search(7) << endl;
    list1.deleteNode(3);
    list2 = list1;
    cout << "list2: ";
    list2.print();
    cout << "length of list2: " << list2.length() << endl;
    {
        circularLinkedList<int> list3(list2);
        cout << "list3: ";
        list3.print();
    }
    list1.destroyList();
    cout << "is list 1 empty = " << list1.isEmptyList() << endl;

    return 0;
}