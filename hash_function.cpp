/* This assignment originated at UC Riverside. */

#include <string>
#include <stdint.h>
#include "hash.h"

using namespace std;
using std::string;
using std::swap;

//Hashing strings using bitwise operation
int Hash::hf(string input) {
    uint32_t string_sum = 0;

    //Adds values of all ASCII characters in the string together
    for(unsigned char c : input) {
        string_sum += c;

        //Bitwise operation that jumbles up the bits used by
        //string_sum
        string_sum = (string_sum << 5 | string_sum >> (32 - 5));
    }
    
    //Then mods by table size
    return string_sum % HASH_TABLE_SIZE;
}