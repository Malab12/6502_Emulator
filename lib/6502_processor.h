#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "6502_memory.h"

struct CPU
{
    Word PC; // Program Counter
    Word SP; // Stack Pointer

    Byte A; // Accumalator register
    Byte X; // Index register X
    Byte Y; // Index register Y

// Status Flags
    Byte C : 1; // Carry Flag 
    Byte Z : 1; // Zero Flag
    Byte I : 1; // IRQ Disable Flag
    Byte D : 1; // Decimal Mode Flag
    Byte B : 1; // Break Command Flag
    Byte V : 1; // Overflow Flag
    Byte N : 1; // Negative Flag

    // opcodes
    static constexpr Byte
        INS_LDA_IM = 0xA9,
        INS_LDA_ZP = 0xA5,
        INS_LDA_ZPX = 0xB5,
        INS_JSR = 0x20;

    void Reset( Mem& memory );

    Byte FetchByte( u32& Cycles, Mem& memory );

    Word FetchWord( u32& Cycles, Mem& memory );

    Byte ReadByte( u32& Cycles, Byte Address, Mem& memory );

    void LDASetStatus();

    void Execute( u32 Cycles, Mem& memory );
};
#endif