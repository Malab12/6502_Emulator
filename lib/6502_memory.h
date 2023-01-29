#ifndef MEMORY_H
#define MEMORY_H


#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Mem
{
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    void Initialise();
    // Read 1 byte
    Byte operator[]( u32 Address ) const;
    // Write 1 byte
    Byte& operator[]( u32 Address );
    // Write 2 bytes in little endian format
    void WriteWord( u32 &Cycles, Word Value, u32 Address );

};
#endif