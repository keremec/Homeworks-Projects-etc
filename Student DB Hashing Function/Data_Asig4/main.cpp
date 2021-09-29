//
// Created by Kerem Safa on 16.05.2020.
//

#include <iostream>
#include <list>
#include <ctime>
#include <random>

using namespace std;

struct student {
    long id;    // 9-digit student id,
    char name[30];  // student name, surname
    char address[50];   // address of the student
    double gpa; // gpa of the student
};

class Hash {
private:
    int BUCKET;   // Number of buckets
    // Pointer to an array containing buckets
    list<student> *table;

    // destroys the list
    void destroy() {
        delete[]table;
    }
    
    // hash functions to map values to key
    int (Hash::*hash_template)(student);  // function pointer as a wrapper. Assigned address in constructor.

    int hash1(student x) {
        return (x.id % BUCKET);
    }   // with student number

    int hash2(student x) {
        int retvalue = 0;
        for (int i = 0; i < 30; i++) {
            retvalue += x.name[i];
        }
        return (retvalue % BUCKET);
    }   // with student name

    int hash3(student x) {
        int retvalue = 0;
        for (int i = 0; i < 50; i++) {
            retvalue += x.address[i];
        }
        return (retvalue % BUCKET);
    }   // with student address

    int hash4(student x) {
        int retvalue = 0;
        for (int i = 0; i < 20; i++) {
            retvalue += x.address[i];
            retvalue += x.name[i];
        }
        retvalue += x.id;
        return (retvalue % BUCKET);
    }   // mixed up

    int hash5(student x) {
        int retvalue = 0;
        for (int i = 0; i < 20; i++) {
            retvalue += x.address[i];
            retvalue += x.name[i];
        }
        retvalue += x.id;
        return (retvalue % ((BUCKET) / 4) + 1);
    }   // bad algorithm for testing utilization

public:
    // Constructor
    explicit Hash(int b, int h = 0) {
        //initialing the list
        this->BUCKET = b;
        table = new list<student>[BUCKET];
        // assigning the address of hash function
        switch_hash(h);
    } // b = bucket, h = hash function (hash1 default)
    // Destructor
    ~Hash() {
        destroy();
    }

    // Returns Table Size
    int table_size(int i) {
        return table[i].size();
    }

    // Returns Bucket Size
    int bucket_size() {
        return BUCKET;
    }

    // switch the hash function (default 1)
    void switch_hash(int h = 0) {
        if (h == 2) { hash_template = &Hash::hash2; }
        else if (h == 3) { hash_template = &Hash::hash3; }
        else if (h == 4) { hash_template = &Hash::hash4; }
        else if (h == 5) { hash_template = &Hash::hash5; }
        else { hash_template = &Hash::hash1; }
    }

    // inserts a key into hash table (no duplicates)
    void insert(student key) {
        if (!search(key)) {
            int index = (this->*hash_template)(key);
            table[index].push_back(key);
        }
    }

    // search a key in the hash table
    bool search(student key) {
        // get the hash index of key
        int index = (this->*hash_template)(key);
        // find the key in (inex)th list
        list<student>::iterator i;
        for (i = table[index].begin(); i != table[index].end(); i++) {
            if (i->id == key.id) { break; }
        }
        // if key is found in hash table, return true
        if (i != table[index].end()) { return true; }
        else { return false; }
    }

    // search and deletes a key from hash table
    void remove(student key) {
        // get the hash index of key
        int index = (this->*hash_template)(key);
        // find the key in (inex)th list
        list<student>::iterator i;
        for (i = table[index].begin(); i != table[index].end(); i++) {
            if (i->id == key.id) { break; }
        }
        // if key is found in hash table, remove it
        if (i != table[index].end())
            table[index].erase(i);
    }

    // function that prints the lists (if onlyid=1, it only prints id of students, default 0)
    void display(bool onlyid = false) {
        for (int i = 0; i < BUCKET; i++) {
            cout << i;
            for (auto x : table[i]) {
                if (onlyid) {
                    cout << " --> " << x.id;
                }
                else {
                    cout << " --> |Id:" << x.id << "||Gpa:" << x.gpa << "||Name:" << x.name << "||Address:"
                         << x.address << "|";
                }
            }
            cout << endl;
        }
    }

};

// random name and adress generator
void gen_random(char *s, const int len, bool isnum) {
    // addresses contain numbers, names not
    if (isnum) {
        char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";

        for (int i = 0; i < len; ++i) {
            s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
        }
    }
    else {
        char onlyalph[] =
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
        for (int i = 0; i < len; ++i) {
            s[i] = onlyalph[rand() % (sizeof(onlyalph) - 1)];
        }
    }
    s[len] = 0;
}

// random number generator for gbp and id
template<class T>
T randnum(T min, T max) {
    uniform_real_distribution<double> distribution(min + 0, max + 0);
    random_device rd;
    default_random_engine generator(rd());
    auto num = (T) distribution(generator);
    return num;
}

// compares hash functions in terms of efficiency and returns the returns the most efficient hash functions number.
// Higher score is better.
int utilization() {
    Hash A(50);  // create a hashtable
    // create random students
    student test_arr[999];
    for (auto &i : test_arr) {
        i.gpa = randnum(0.0, 4.0);
        i.id = randnum(1, 210000000);
        gen_random(i.name, 29, false);
        gen_random(i.address, 49, true);
    }
    int final_hash = 1;
    double bestscore;

    for (int i = 1; i <= 5; i++) {
        A.switch_hash(i);  //Changing hashing algorithm to test them
        int max_listsize = 0;
        int numofkeys = 0;
        double tempscore;
        for (auto &j : test_arr) { A.insert(j); } // add temp students to the list
        // calculate the number of keys (its obvious number of keys equal the size of test_arr)
        for (int j = 0; j < A.bucket_size(); j++) {
            numofkeys += A.table_size(j);
            if (A.table_size(j) > max_listsize) { max_listsize = A.table_size(j); }
        }
        tempscore = numofkeys / ((double) max_listsize * (double) A.bucket_size());  // calculating score
        cout << "Hash" << i << " Score= " << tempscore << " numofkeys=" << numofkeys << " maxlistsize=" << max_listsize
             << " bucketsize=" << A.bucket_size() << endl;
        if (i == 1) {
            final_hash = i;
            bestscore = tempscore;
        }
        else if (tempscore >= bestscore) {
            final_hash = i;
            bestscore = tempscore;
        }
        for (auto &j : test_arr) { A.remove(j); } // remove the added temp students from the list
    }
    return final_hash;

}

int main() {

    int hashfunction = utilization();
    cout << "Best function is Hash" << hashfunction << endl;

    // Create hashtable
    Hash h(21, hashfunction);

    // Creating Random Students
    student arr[15];
    for (auto &i : arr) {
        i.gpa = randnum(0.0, 4.0);
        i.id = randnum(1, 210000000);
        gen_random(i.name, 29, false);
        gen_random(i.address, 49, true);
        h.insert(i);
    }
    //Testing functions
    h.display(false);
    if (h.search(arr[2])) { cout << "The item is in the list" << endl; }

    return 0;
}
