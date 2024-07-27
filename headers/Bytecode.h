//
// Created by User on 7/16/2024.
//
#ifndef VM_BYTECODE_H
#define VM_BYTECODE_H

#include "./common.h"
#include "vm.h"

enum Bytecode {
    VM_ADD = 1,
    VM_SUB = 2,
    VM_MUL = 3,
    VM_DIV = 4,
    VM_LT = 5,
    VM_EQ = 6,
    VM_BR = 7,
    VM_BRT = 8,
    VM_BRF = 9,
    VM_CONST = 10,
    VM_LOAD = 11,
    VM_GLOAD = 12,
    VM_STORE = 13,
    VM_GSTORE = 14,
    VM_PRINT = 15,
    VM_POP = 16,
    VM_HALT = 17,
    VM_CALL = 18,
    VM_RET = 19,
    VM_NEG = 20,
    VM_INC = 21,
    VM_DEC = 22,
    VM_NOP = 23,
    VM_INTERMODULAR_CALL = 24,
    VM_MODULE_BASE = 25
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

    Instruction(const char* _mnemonic, const int _operand) :
        mnemonic(_mnemonic),
        operand(_operand)
    {};

    [[nodiscard]] const char* getMnemonic() const{
        return mnemonic;
    }

    [[nodiscard]] int getOperand() const{
        return operand;
    }

};

namespace Instructions {
        inline Instruction opcodes[] = {
            Instruction(""),
            Instruction("VM_ADD"),
            Instruction("VM_SUB"),
            Instruction("VM_MUL"),
            Instruction("VM_DIV"),
            Instruction("VM_LT"),
            Instruction("VM_EQ"),
            Instruction("VM_BR", 1),
            Instruction("VM_BRT", 1),
            Instruction("VM_BRF", 1),
            Instruction("VM_CONST", 1),
            Instruction("VM_LOAD", 1),
            Instruction("VM_GLOAD", 1),
            Instruction("VM_STORE", 1),
            Instruction("VM_GSTORE", 1),
            Instruction("VM_PRINT"),
            Instruction("VM_POP"),
            Instruction("VM_HALT"),
            Instruction("VM_CALL", 3),
            Instruction("VM_RET"),
            Instruction("VM_NEG"),
            Instruction("VM_INC"),
            Instruction("VM_DEC"),
            Instruction("VM_NOP"),

            //argument = index of function within a table
            Instruction("VM_INTERMODULAR_CALL", 1),
            Instruction("VM_MODULE_BASE")
    };
}

#endif