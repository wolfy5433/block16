#pragma once
#pragma once
#include <string.h>

using namespace std;

typedef unsigned int uint;

#define size_of_one_block_in_bytes 64 
#define single_block_size_values 16 
#define block_expend_size_uints 80 

#define SHA1HASHLENGTHBYTES 20
#define SHA1HASHLENGTHUINTS 5

typedef uint* Block;
typedef uint ExpendBlock[block_expend_size_uints];

const uint H[5] =
{
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0
};

uint cycle_shift_left(uint val, int bit_count);
uint bring_to_human_attention(uint val);

uint* sha1(char* message, uint msize_bytes);