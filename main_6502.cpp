#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Mem
{
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];

    void Initialise()
    {
        for (u32 i = 0; i < MAX_MEM; i++)
        {
            Data[i] = 0;
        }
    }
    // Read 1 byte
    Byte operator[]( u32 Address ) const
    {
        // assert here Address is < MAX_MEM
        return Data[Address];
    }

    // Write 1 byte
    Byte& operator[]( u32 Address ) 
    {
        // assert here Address is < MAX_MEM
        return Data[Address];
    }
    
};

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

    void Reset( Mem& memory )
    {
        PC = 0xFFFC;
        SP = 0x0100;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;
        memory.Initialise();
    }

    Byte FetchByte( u32& Cycles, Mem& memory )
    {
        Byte Data = memory[PC];
        PC++;
        Cycles--;
        return Data;
    }

    Byte ReadByte( u32& Cycles, Byte Address, Mem& memory )
    {
        Byte Data = memory[Address];
        Cycles--;
        return Data;
    } 

    // opcodes
    static constexpr Byte 
        INS_LDA_IM = 0xA9,
        INS_LDA_ZP = 0xA5,
        INS_LDA_ZPX = 0xB5;

    void LDASetStatus()
    {
        Z = (A == 0);
        N = (A & 0b1000000) > 0;
    }

    void Execute( u32 Cycles, Mem& memory )
    {
        while ( Cycles > 0 )
        {
            Byte Instruction = FetchByte( Cycles, memory );

            switch ( Instruction )
            {
            case INS_LDA_IM:
            {
                Byte Value = FetchByte(Cycles, memory);
                A = Value;
                LDASetStatus();
                
            } break;

            case INS_LDA_ZP:
            {
                Byte ZeroPageAddress = FetchByte(Cycles, memory);
                A = ReadByte( Cycles, ZeroPageAddress, memory );
                LDASetStatus();
            } break;

            case INS_LDA_ZPX:
            {
                Byte ZeroPageAddress = FetchByte(Cycles, memory);
                ZeroPageAddress += X;
                Cycles--;
                A = ReadByte( Cycles, ZeroPageAddress, memory );
                LDASetStatus();  

            } break;
            
            default:
            {
                printf("Instruction not handled %d", Instruction);
            } break;
            }
        }
    }
};

int main() {
    Mem mem;
    CPU cpu;
    cpu.Reset( mem );
    mem[0xFFFC] = CPU::INS_LDA_ZP;
    mem[0xFFFD] = 0x42;
    mem[0x0042] = 0x84;
    cpu.Execute( 3, mem );
    return 0;
}