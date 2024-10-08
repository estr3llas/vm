//
// Created by User on 7/16/2024.
//
#ifndef VM_EXCEPTION_HANDLER_H
#define VM_EXCEPTION_HANDLER_H

#include "common.h"
#include "vm.h"

class ExceptionHandler : public VM{
public:

    enum exception_codes {
        EXCEPTION_DIVIDE_BY_ZERO = 1,
        EXCEPTION_UNKNOWN_OPCODE = 2,
        EXCEPTION_ARITHMETIC_OVERFLOW = 3,
        EXCEPTION_IP_OVERFLOW = 4,
    };

    void CheckForArithmeticOverflow(int64_t operand1, int64_t operand2, int32_t opcode);

    void Handler(uint32_t exception_code, int32_t opcode);

    static void EH_exit();
    static void EH_abort();
};

#endif