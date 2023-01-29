#include "6502_memory.h"

void Mem::Initialise()
{
    for (u32 i = 0; i < MAX_MEM; i++)
    {
        Data[i] = 0;
    }
}

Byte Mem::operator[]( u32 Address ) const
{
    // assert here Address is < MAX_MEM
    return Data[Address];
}

Byte& Mem::operator[]( u32 Address ) 
{
    // assert here Address is < MAX_MEM
    return Data[Address];
}

void Mem::WriteWord( u32 &Cycles, Word Value, u32 Address )
    {
        Data[Address] = Value & 0xFF;
        Data[Address + 1] = (Value >> 8);
        Cycles -= 2;
    }