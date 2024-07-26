//
// Created by User on 7/16/2024.
//

#ifndef EXAMPLES_H
#define EXAMPLES_H

#include "../headers/common.h"
#include "../headers/Bytecode.h"

namespace Examples {

    constexpr int FACTORIAL_ADDRESS = 0;
    constexpr int FACTORIAL_ENTRYPOINT = 23;
    inline std::vector<int32_t> factorial = {
//.def factorial: ARGS=1, LOCALS=0	ADDRESS
//	IF N < 2 RETURN 1
        VM_LOAD, 0,                // 0
        VM_CONST, 2,              // 2
        VM_LT,                    // 4
        VM_BRF, 10,                // 5
        VM_CONST, 1,              // 7
        VM_RET,                    // 9
//CONT:
//	RETURN N * FACT(N-1)
        VM_LOAD, 0,                // 10
        VM_LOAD, 0,                // 12
        VM_CONST, 1,              // 14
        VM_SUB,                   // 16
        VM_CALL, FACTORIAL_ADDRESS, 1, 0,    // 17
        VM_MUL,                   // 21
        VM_RET,                    // 22
//.DEF MAIN: ARGS=0, LOCALS=0
// PRINT FACT(1)
        VM_CONST, 5,              // 23    <-- MAIN METHOD!
        VM_CALL, FACTORIAL_ADDRESS, 1, 0,    // 25
        VM_PRINT,                  // 29
        VM_HALT                    // 30
    };

    const int MATH_ENTRYPOINT = 0;
    std::vector<int> math = {
    // MATH DEMONSTRATION
    // PUSH 1, 2
        VM_CONST, 1,                  // 0
        VM_CONST, 2,                  // 2
    // 1 + 2 = 3
        VM_ADD,                       // 3
    // PUSH 1
        VM_CONST, 1,                  // 4
    // 3 - 1 = 2
        VM_SUB,                       // 6
    // PUSH 2
        VM_CONST, 2,                  // 7
    // 2 * 2 = 4
        VM_MUL,                       // 9
    // PUSH 4
        VM_CONST, 4,                  // 10
    // 4 * 4 = 16
        VM_MUL,                       // 12
    // PUSH 2
        VM_CONST, 2,                  // 13
    // 16 / 2 = 8
        VM_DIV,                       // 15
    // PRINT(8)
        VM_PRINT,                      // 16
        VM_HALT                        // 17
    };

    constexpr int EXCEPTION_ENTRYPOINT = 0;
    inline std::vector<int> exception = {
    // TRIGGER EXCEPTION
    // STORE 1 ON GLOBAL MEMORY
        VM_CONST, 1,                  // 0
        VM_GSTORE, 0,                  // 2
    // STORE 0 ON GLOBAL MEMORY
        VM_CONST, 0,                  // 4
        VM_GSTORE, 1,                  // 6
    // LOAD BOTH ON STACK
        VM_GLOAD, 0,                   // 8
        VM_GLOAD, 1,                   // 10
    // TRY TO DIVIDE 1 BY 0
        VM_DIV,                       // 11
    // CAUSES EXCEPTION
        VM_PRINT,                      // 12
        VM_HALT                        // 13
    };

    constexpr int TEST_FUNC_ADDR = 12;
    constexpr int TEST_ENTRYPOINT = 0;
    inline std::vector<int32_t> test = {
        VM_CONST, 1,
        VM_CALL, TEST_FUNC_ADDR, 1, 0,
        VM_CONST, 2,
        VM_DEC,
        VM_NOP,
        VM_PRINT,
        VM_HALT,

        VM_CONST, 3,
        VM_POP,
        VM_RET
    };

    constexpr int PUSH_MODULE_ENTRYPOINT = 0;
    inline std::vector<int32_t> push_module = {
        VM_CONST, 9,
        VM_PRINT,
        MODULE_BASE,
        VM_PRINT,
        VM_HALT
    };

}

#endif //EXAMPLES_H
