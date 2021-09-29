//
// Created by Kerem Safa on 4.05.2020.
//
#pragma once

#include <iostream>

using namespace std;

template<class Type>
struct nodeType {
    Type data{};
    int count = 0;
    nodeType<Type> *R_link = nullptr;
    nodeType<Type> *L_link = nullptr;
};

template<class Type>
class BTree {

public:
    //Constructor
    BTree() {
        root = nullptr;
    }

    // Function for adding item
    void additem(const Type &newitem) {
        //Check if it's empty.
        if (root == nullptr) {
            root = new nodeType<Type>;
            root->data = newitem;
            root->count += 1;
            return;
        }
        nodeType<Type> *cur = root;
        nodeType<Type> *back = root;
        bool RorL; // 0=Left, 1=Right // Store the last link's direction
        while (true) {
            if (cur == nullptr) { //if node doesn't exist create new one
                if (RorL) {
                    back->R_link = new nodeType<Type>;
                    cur = back->R_link;
                }
                else {
                    back->L_link = new nodeType<Type>;
                    cur = back->L_link;
                }
                cur->data = newitem;
                cur->count += 1;
                break;
            }
            else if (newitem == cur->data) { //if node exist increase the count
                cur->count += 1;
                break;
            }
            else if (newitem > cur->data) { //walking tree
                back = cur;
                cur = cur->R_link;
                RorL = true;
            }
            else if (newitem < cur->data) { //walking tree
                back = cur;
                cur = cur->L_link;
                RorL = false;
            }
        }
    }

    // Function for removing item
    void delitem(const Type &item) {
        if (root == nullptr) { //check if it's empty.
            return;
        }
        nodeType<Type> *cur = root;
        nodeType<Type> *back = root;
        bool RorL; // 0=Left, 1=Right // Store the last link's direction
        while (cur != nullptr) {
            if (item == cur->data) { // if item found
                cur->count -= 1; // decrease the count
                if (cur->count == 0) { // if counter hit 0 delete the node
                    if (cur == root) { // if the node will be deleted is root
                        if (cur->L_link == nullptr) {
                            if (cur->R_link == nullptr) { // if it's also the last node
                                delete cur;
                                root = nullptr;
                                break;
                            }
                            root = cur->R_link;
                            delete cur;
                            break;
                        }
                        if (cur->R_link == nullptr) {
                            root = cur->L_link;
                            delete cur;
                            break;
                        }
                    }
                    nodeType<Type> *t_root = cur;
                    nodeType<Type> *t_back = nullptr;
                    if (cur->L_link == nullptr) { // checks if the item in the last level
                        if (cur->R_link != nullptr) { t_back = cur->R_link; }
                        if (RorL) {
                            back->R_link = t_back;
                        }
                        else {
                            back->L_link = t_back;
                        }
                        delete cur;
                        break;
                    }
                    cur = t_root->L_link; //searching the highest item of the small items
                    while (cur->R_link != nullptr) { //going right after going left one time
                        t_back = cur;
                        cur = cur->R_link;
                    }
                    if (t_back == nullptr) { // if never goes right after going left
                        t_root->data = cur->data;
                        t_root->count = cur->count;
                        t_root->L_link = nullptr;
                        delete cur;
                        break;
                    }
                    // if not exceptional follow standard procedure
                    t_root->data = cur->data;
                    t_root->count = cur->count;
                    t_back->R_link = cur->L_link;
                    delete cur;
                }
                break;
            }
            else if (item > cur->data) { //walking tree
                back = cur;
                cur = cur->R_link;
                RorL = true;
            }
            else if (item < cur->data) { //walking tree
                back = cur;
                cur = cur->L_link;
                RorL = false;
            }
        }
    }

    // Function for getting address of root.
    nodeType<Type> *getroot() {
        return root;
    }

protected:
    nodeType<Type> *root;
};

//Print Function
template<class Type>
void printitems(nodeType<Type> *root) {
    nodeType<Type> *cur = root;
    if (cur == nullptr) { return; } //check if it's empty.
    cur = root->L_link; // going left
    printitems(cur); // call recursive until finishing the left side
    cout << string(root->count, root->data); //print
    cur = root->R_link; //going right after finishing the left
    printitems(cur); // call recursive until finishing the right side
}
