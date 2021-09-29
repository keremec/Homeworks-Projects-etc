#include <iostream>
#include <string>
#include <bitset>

using namespace std;

///// Linked list for storing the frequency of letters /////
struct tnode {
    char letter{}; // keeps character
    long double freq = 0; // Frequency is unique. This uniqueness is provided with the fractional part
    string huffman;
    tnode *next = nullptr;
};

class table {

public:
    //Constructor
    table() {
        root = nullptr;
    }

    // add item to the list sorted by the number of repetitions
    void additem(const char &letter) {
        tnode *cur = root;
        tnode *temp;
        // if list is empty add directly to the root.
        if (cur == nullptr) {
            root = new tnode;
            root->letter = letter;
            root->freq += 1;
            return;
        }
        // check if letter is already in the list
        while (cur != nullptr) {
            // if already in the list inc freq
            if (cur->letter == letter) {
                cur->freq += 1;
                // loop for placement
                if (cur->next == nullptr) { return; }
                while (cur->freq > cur->next->freq) {
                    temp = new tnode;
                    // copy cur->next values to temp
                    temp->freq = cur->next->freq;
                    temp->letter = cur->next->letter;
                    // copy cur values to cur->next
                    cur->next->freq = cur->freq;
                    cur->next->letter = cur->letter;
                    // copy temp values to cur
                    cur->freq = temp->freq;
                    cur->letter = temp->letter;

                    cur = cur->next;
                    delete temp;
                    if (cur->next == nullptr) { return; }
                }
                return;
            }
            cur = cur->next;
        }
        // if not in the list add to root.
        temp = root;
        root = new tnode;
        root->letter = letter;
        root->freq += 1;
        root->next = temp;
    }

    // pop the root from the list (remove the node from the list but keep the data and return the address of it)
    tnode *pop() {
        if (root == nullptr) { return nullptr; }
        tnode *temp;
        temp = root;
        root = root->next;
        return temp;
    }

    // returns the address (i+1)th node. Return the last element if i = -1 or i is bigger than list's length
    tnode *getnode(int i) {
        if (i >= listlength() || i == -1) {
            i = listlength() - 1;
        }
        tnode *temp = root;
        for (int j = 0; j < i; j++) {
            temp = temp->next;
        }
        return temp;
    }

    // returns the address of letter in the list
    tnode *findletter(char letter) {
        int i = listlength();
        tnode *temp = root;
        while (temp != nullptr) {
            if (temp->letter == letter) { return temp; }
            temp = temp->next;
        }
        return root;
    }

    // returns the length of list
    int listlength() {
        int i = 0;
        tnode *temp = root;
        while (temp != nullptr) {
            i++;
            temp = temp->next;
        }
        return i;
    }

    // print all items with their data
    void printitems() {
        tnode *cur = root;
        if (cur == nullptr) { return; }
        while (cur->next != nullptr) {
            cout << "Letter: '" << cur->letter << "' Frequency: " << cur->freq << " Huffman: " << cur->huffman << endl;
            cur = cur->next;
        }
        cout << "Letter: '" << cur->letter << "' Frequency: " << cur->freq << " Huffman: " << cur->huffman << endl;
    }

protected:
    tnode *root;
};
///// ------------------------------------------------ /////

///// Tree for Huffman Coding /////
struct Hnode {
    long double freq = 0; // Frequency is unique. This uniqueness is provided with the fractional part
    char letter = 0;
    Hnode *right = nullptr;
    Hnode *left = nullptr;
};

class HTree {
public:
    //Constructor
    explicit HTree(table &T) {
        root = nullptr;
        buildtree(T);
    }

    // return the address of root
    Hnode *getroot() {
        return root;
    }

protected:
    Hnode *root;

    // Function build tree
    void buildtree(table &T) {
        int listlenght = T.listlength();
        long double nodup = 0.001; // for keeping frequency is unique
        if (listlenght < 2) { cout << "List is not long enough" << endl; }

        // Creating the first elements of tree
        auto *h_temp = new Hnode;
        tnode *t_temp;

        // Creating left child
        h_temp->left = new Hnode;
        t_temp = T.getnode(0);
        h_temp->left->freq = t_temp->freq;
        h_temp->left->letter = t_temp->letter;

        // Creating right child
        h_temp->right = new Hnode;
        t_temp = T.getnode(1);
        h_temp->right->freq = t_temp->freq;
        h_temp->right->letter = t_temp->letter;

        // Filling the first Parent
        h_temp->freq = h_temp->right->freq + h_temp->left->freq;

        // After creating the tree this loop adds parent elements according to frequency
        for (int i = 2; i < listlenght; i++) {
            t_temp = T.getnode(i);
            // if new nodes freq lower than  the parent (root) node
            if (t_temp->freq < h_temp->freq) {
                auto *h2_temp = new Hnode;
                h2_temp->left = new Hnode;
                h2_temp->left->freq = t_temp->freq;
                h2_temp->left->letter = t_temp->letter;
                h2_temp->right = h_temp;
                h_temp = h2_temp;
                h_temp->freq = h_temp->right->freq + h_temp->left->freq;
            }
                // if new nodes freq greater than  the parent (root) node
            else if (t_temp->freq > h_temp->freq) {
                auto *h2_temp = new Hnode;
                h2_temp->right = new Hnode;
                h2_temp->right->freq = t_temp->freq;
                h2_temp->right->letter = t_temp->letter;
                h2_temp->left = h_temp;
                h_temp = h2_temp;
                h_temp->freq = h_temp->left->freq + h_temp->right->freq;
            }
                // if new nodes freq is same with parent (root) node
                // fractional part will be added to the new node's freq
                // and the new node's frequency will be greater than the parent(root) node
                // this will only affect the tree not the table
            else {
                auto *h2_temp = new Hnode;
                h2_temp->right = new Hnode;
                h2_temp->right->freq = t_temp->freq + nodup; // adding fractional part
                nodup += 0.001;  // Always increment the fractional part to keep all frequencies unique
                h2_temp->right->letter = t_temp->letter;
                h2_temp->left = h_temp;
                h_temp = h2_temp;
                h_temp->freq = h_temp->left->freq + h_temp->right->freq;
            }
        }
        root = h_temp;

    }
};
///// ---------------------- /////

///// Input and Calculation Functions /////
// adding string to table
void str2table(table &T, const string &str) {
    long long length = str.length();
    for (int i = 0; i < length; i++) {
        T.additem(str[i]);
    }
}

// filling the table.huff with the data from Huffman Tree
void fillhuff(Hnode *root, string bin, table &T) {
    Hnode *cur = root;
    if (cur == nullptr) { return; } //check if it's empty.
    cur = root->left; // going left
    bin += '0';
    fillhuff(cur, bin, T); // call recursive until finishing the left side
    bin.pop_back();
    if (root->letter != 0) {
        T.findletter(root->letter)->huffman = bin;
    }
    cur = root->right; //going right after finishing the left
    bin += '1';
    fillhuff(cur, bin, T); // call recursive until finishing the right side
    bin.pop_back();
}
///// ------------------------------ /////

///// Print Functions /////
// print the string in binary.
void str2bin(const string &str, bool space = false) {
    int length = str.length();
    cout << "Binary: " << endl;
    for (int i = 0; i < length; i++) {
        bitset<8> x(str[i]);
        cout << x;
        if (space) { cout << " "; }
    }
    cout << endl;
}

// print the string in huffman coded binary.
void str2huff(table &T, const string &str, bool space = false) {
    long long length = str.length();
    cout << "Huffman: " << endl;
    for (int i = 0; i < length; i++) {
        cout << T.findletter(str[i])->huffman;
        if (space) { cout << " "; }
    }
    cout << endl;
}
///// -------------- /////


int main() {

    /// getting input
    string input;
    cout << "Enter a string: " << endl;
    getline(cin, input);
    cout << endl;

    /// creating table
    table T;
    str2table(T, input); // adding the letters to the table
    HTree H(T); // creating the huffman tree
    string b; // temp string for calling tge fillhuff function
    fillhuff(H.getroot(), b, T); // filling the table.huff with huffman tree

    /// Printing
    str2bin(input, true); // print binary value of string
    cout << endl;
    str2huff(T, input, true); // print huffman coded binary string
    cout << endl << "Table: " << endl;
    T.printitems(); // print the table

    return 0;
}
