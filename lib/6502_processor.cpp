#include "6502_processor.h"

void CPU::Reset( Mem& memory )
{
    PC = 0xFFFC;
    SP = 0x0100;
    C = Z = I = D = B = V = N = 0;
    A = X = Y = 0;
    memory.Initialise();
}

Byte CPU::FetchByte(u32 &Cycles, Mem &memory)
{
    Byte Data = memory[PC];
    PC++;
    Cycles--;
    return Data;
}

Word CPU::FetchWord(u32 &Cycles, Mem &memory)
{
    // The 6502 processor is little endian
    Word Data = memory[PC];
    PC++;
    Cycles--;

    Data |= (memory[PC] << 8);
    PC++;
    Cycles--;

    return Data;
}

Byte CPU::ReadByte(u32 &Cycles, Byte Address, Mem &memory)
{
    Byte Data = memory[Address];
    Cycles--;
    return Data;
}

void CPU::LDASetStatus()
{
    Z = (A == 0);
    N = (A & 0b1000000) > 0;
}

void CPU::Execute(u32 Cycles, Mem &memory)
{
    while (Cycles > 0)
    {
        Byte Instruction = FetchByte(Cycles, memory);

        switch (Instruction)
        {
        case INS_LDA_IM:
        {
            Byte Value = FetchByte(Cycles, memory);
            A = Value;
            LDASetStatus();
        }
        break;

        case INS_LDA_ZP:
        {
            Byte ZeroPageAddress = FetchByte(Cycles, memory);
            A = ReadByte(Cycles, ZeroPageAddress, memory);
            LDASetStatus();
        }
        break;

        case INS_LDA_ZPX:
        {
            Byte ZeroPageAddress = FetchByte(Cycles, memory);
            ZeroPageAddress += X;
            Cycles--;
            A = ReadByte(Cycles, ZeroPageAddress, memory);
            LDASetStatus();
        }
        break;

        case INS_JSR:
        {
            Word SubRoutineAddress = FetchWord(Cycles, memory);
            memory.WriteWord(Cycles, PC - 1, SP);
            SP++;
            PC = SubRoutineAddress;
            Cycles--;
        }
        break;

        default:
        {
            printf("Instruction not handled %d", Instruction);
        }
        break;
        }
    }
}