#include "Sha1.h"

uint* sha1(char* message, uint msize_bytes)
{
    uint A = H[0];
    uint B = H[1];
    uint C = H[2];
    uint D = H[3];
    uint E = H[4];

    uint BlockCount = msize_bytes / size_of_one_block_in_bytes;

    uint ExtraBytesNeed = size_of_one_block_in_bytes - (msize_bytes - BlockCount * size_of_one_block_in_bytes);

    if (ExtraBytesNeed < 8)
    {
        BlockCount += 2;
        ExtraBytesNeed += size_of_one_block_in_bytes;
    }
    else
    {
       BlockCount += 1;
    }

    uint advancedMessageSize = msize_bytes + ExtraBytesNeed;

    unsigned char* newMessage = new unsigned char[advancedMessageSize];
    memcpy(newMessage, message, msize_bytes);

    uint* ptr_to_size = (uint*)(newMessage + advancedMessageSize - 4);
    *ptr_to_size = bring_to_human_attention(msize_bytes * 8);

    newMessage[msize_bytes] = 0x80;
    memset(newMessage + msize_bytes + 1, 0, ExtraBytesNeed - 1);


    ExpendBlock expblock;
    for (int i = 0; i < BlockCount; i++)
    {
        unsigned char* cur_p = newMessage + size_of_one_block_in_bytes * i;
        Block block = (Block)cur_p;

        for (int j = 0; j < single_block_size_values; ++j)
        {
            expblock[j] = bring_to_human_attention(block[j]);
        }
        for (int j = single_block_size_values; j < block_expend_size_uints; ++j) {
            expblock[j] = expblock[j - 3] ^ expblock[j - 8] ^ expblock[j - 14] ^ expblock[j - 16];
            expblock[j] = cycle_shift_left(expblock[j], 1);
        }
        uint a = H[0];
        uint b = H[1];
        uint c = H[2];
        uint d = H[3];
        uint e = H[4];

        for (int j = 0; j < block_expend_size_uints; ++j)
        {
            uint y;
            uint z;
            if (j < 20)
            {
                y = (b & c) | ((~b) & d);
                z = 0x5A827999;
            }
            else if (j < 40)
            {
                y = b ^ c ^ d;
                z = 0x6ED9EBA1;
            }
            else if (j < 60)
            {
                y = (b & c) | (b & d) | (c & d);
                z = 0x8F1BBCDC;
            }
            else
            {
                y = b ^ c ^ d;
                z = 0xCA62C1D6;
            }

            uint temp = cycle_shift_left(a, 5) + y + e + z + expblock[j];
            e = d;
            d = c;
            c = cycle_shift_left(b, 30);
            b = a;
            a = temp;
        }
        A = A + a;
        B = B + b;
        C = C + c;
        D = D + d;
        E = E + e;
    }

    uint* digest = new uint[5];
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = E;

    delete[] newMessage;
    return digest;
}
uint cycle_shift_left(uint val, int bit_count)
{
    return (val << bit_count | val >> (32 - bit_count));
}

uint bring_to_human_attention(uint val)
{
    return  ((val & 0x000000FF) << 24) | ((val & 0x0000FF00) << 8) | ((val & 0x00FF0000) >> 8) | ((val & 0xFF000000) >> 24);
}