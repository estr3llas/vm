//
// Created by User on 7/16/2024.
//
#ifndef VM_BYTECODE_H
#define VM_BYTECODE_H

#include "./common.h"
#include "vm.h"

enum Bytecode {
    IADD = 1,
    ISUB = 2,
    IMUL = 3,
    IDIV = 4,
    ILT = 5,
    IEQ = 6,
    BR = 7,
    BRT = 8,
    BRF = 9,
    ICONST = 10,
    LOAD = 11,
    GLOAD = 12,
    STORE = 13,
    GSTORE = 14,
    PRINT = 15,
    POP = 16,
    HALT = 17,
    CALL = 18,
    RET = 19,
    NEG = 20,
    INC = 21,
    DEC = 22,
    NOP = 23
};

class Instruction {
private:
    const char* mnemonic;
    int operand;
public:

    Instruction() :
        mnemonic(nullptr),
        operand(VM_ZERO)
    {};

    explicit Instruction(const char* _mnemonic) :
        mnemonic(_mnemonic),
        operand(VM_ZERO)
    {};

    Instruction(const char* _mnemonic, int _operand) :
        mnemonic(_mnemonic),
        operand(_operand)
    {};

    const char* getMnemonic(){
        return mnemonic;
    }

    int getOperand(){
        return operand;
    }

};

namespace Instructions {
        inline Instruction opcodes[] = {
        Instruction(""),
        Instruction("IADD"),
        Instruction("ISUB"),
        Instruction("IMUL"),
        Instruction("IDIV"),
        Instruction("ILT"),
        Instruction("IEQ"),
        Instruction("BR", 1),
        Instruction("BRT", 1),
        Instruction("BRF", 1),
        Instruction("ICONST", 1),
        Instruction("LOAD", 1),
        Instruction("GLOAD", 1),
        Instruction("STORE", 1),
        Instruction("GSTORE", 1),
        Instruction("PRINT"),
        Instruction("POP"),
        Instruction("HALT"),
        Instruction("CALL", 3),
        Instruction("RET"),
        Instruction("NEG"),
        Instruction("INC"),
        Instruction("DEC"),
        Instruction("NOP")
    };
}

#endif