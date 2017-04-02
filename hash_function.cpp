/* This assignment originated at UC Riverside. */

/**
 * @file hash_function.cpp  The hashing algorithm used to
 *                          find the indices of each string
 *                          input.
 *
 * @brief
 *      Hashes by ASCII values and bitwise operations, then
 *      mods the result by HASH_TABLE_SIZE.
 *
 * @description
 *      This hash function takes in a string input, adds
 *      up the ASCII values of each character in the string,
 *      performs a bitwise operation to jumble up the end bits
 *      of the resulting integer, then mods the result by 
 *      HASH_TABLE_SIZE.
 *
 *      I discovered this particular hash function by consulting
 *      with several programming friends I had met online who
 *      pointed me in the right direction.
 *
 * @author  Landon Mote
 * @date    4-2-2017
 */

#include <string>
#include <stdint.h>
#include "hash.h"

using namespace std;
using std::string;
using std::swap;

/**
 * hf()
 *
 * Hashes strings by adding up ASCII values, swapping
 * the last few bits of the resultant integer around,
 * and modding them by HASH_TABLE_SIZE.
 *
 * @param input     String to be hashed.
 */
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