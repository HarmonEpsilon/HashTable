#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include "hash.h"

using namespace std;

using std::swap;
using std::string;
using std::fstream;
using std::list;

//Hash table constructor
Hash::Hash() {
    collisions = 0;
    longestList = 0;
    runningAvgListLength = 0;
}

//Remove a string from the Hash table
void Hash::remove(string input) {
    auto index = hf(input);

    for(auto iter = hashTable[index].begin();
             iter != hashTable[index].end();
             iter++) {
        if (*iter == input) {
            hashTable[index].erase(iter);
            return;
        }
    }
}

//Print strings in the Hash Table
void Hash::print() {
    for(int i = 0; i < HASH_TABLE_SIZE; i++) {
        cout << i + 1 << ":\t";
        int if_not_last = 0;
        for(const auto& iter : hashTable[i]) {
            cout << (if_not_last++ > 0 ? ", " : "") << iter;
        }
        cout << endl;
    }
}

//Process file from string input
void Hash::processFile(string input) {
    string from_file;
    ifstream input_file;
    
    input_file.open(input);

    while(true) {
        input_file >> from_file;

        //If the file has reached EOF
        if(!input_file.good()) {
            break;
        }

        //Hashes the string to get the index
        auto index = hf(from_file);

        //  Checks if something already exists at that index
        //  then increments collisions
        if(!hashTable[index].empty()) {
            collisions += 1;
        }

        //Adds the string to the list at that index
        hashTable[index].push_back(from_file);
    }
}

//Search through hash table and return true if found requested string
bool Hash::search(string input) {
    auto index = hf(input);

    for(const auto& iter : hashTable[index]) {
        if(iter == input) {
            return true;
        }
    }
    return false;
}

//Output a given string from the Hash table
void Hash::output(string input) {
    ofstream output_file;
    
    output_file.open(input);

    for(int i = 0; i < HASH_TABLE_SIZE; i++) {
        output_file << i + 1 << ":\t";
        int if_not_last = 0;
        for(const auto& iter : hashTable[i]) {
            output_file << (if_not_last++ > 0 ? ", " : "") << iter;
        }
        output_file << "\n";
    }
}

//Get and print statistics related to the Hash table
void Hash::printStats() {
    cout << "Total Collisions: " << collisions << "\n"
         << "Longest List: " << longestList << "\n"
         << "Average List Length: " << runningAvgListLength << endl;
}