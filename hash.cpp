/**
 * @file Hash.cpp   Contains all relevant functions for
 *                  Hash class
 *
 * @brief
 *      Implementation of all relevant functions for
 *      Hash class.
 * 
 * @author Landon Mote
 * @date 4-2-2017
 */

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

/**
 * Hash()
 * 
 * Default implicit constructor for the Hash
 * class
 */
Hash::Hash() {
    collisions = 0;
    longestList = 0;
    runningAvgListLength = 0.0;
    currentAvgListLen = 0.0;
}

/**
 * remove()
 *
 * Removes an entry from the hash table by taking its
 * hash as an index and removing it from the list at
 * that index.
 *
 * @param input     String to be removed.
 */
void Hash::remove(string input) {
    auto index = hf(input);

    for(auto iter = hashTable[index].begin();
             iter != hashTable[index].end();
             iter++) {
        if (*iter == input) {
            hashTable[index].erase(iter);
            runningAvgListLength--;
            return;
        }
    }
}

/**
 * print()
 * 
 * Prints all data in the hash table to the console.
 */
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

/**
 * processFile()
 * 
 * Takes in a filename and processes the file for insertion
 * into the hash table.
 *
 * @param input     Filename
 */
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
        
        //Increments running average list length
        runningAvgListLength++;

        //Increments longest list if size of list at the index
        //is lower than the value of longestList
        if(hashTable[index].size() < longestList) {
            longestList++;
        }
    }
}

/**
 * search()
 *
 * Searches through the hash table for a specified string
 * by hashing the string to generate its index and iterating
 * through the list at that index. 
 *
 * @param input     String to be found
 * @return          Returns true if found, false if not
 */
bool Hash::search(string input) {
    auto index = hf(input);

    for(const auto& iter : hashTable[index]) {
        if(iter == input) {
            return true;
        }
    }
    return false;
}

/**
 * output()
 *
 * Prints all data in the hash table to an output
 * file.
 *
 * @param input     Filename to be used for output
 *                  file.
 */
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

/**
 * printStats()
 * 
 * Prints all statistics relevant to the Hash table.
 */
void Hash::printStats() {
    unsigned int sum = 0;
    unsigned int non_empty = 0;

    for(int i = 0; i < HASH_TABLE_SIZE; i++) {
        if(hashTable[i].size() != 0) {
            sum += hashTable[i].size();
            non_empty++;
        }
    }

    currentAvgListLen = double(sum) / double(non_empty);

    runningAvgListLength = (currentAvgListLen + runningAvgListLength) / 2.0;

    cout << "Total Collisions: " << collisions << "\n"
         << "Longest List: " << longestList << "\n"
         << "Average List Length: " << runningAvgListLength << endl;
}