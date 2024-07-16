//
// Created by User on 7/16/2024.
//
#include "../headers/common.h"
#include "../headers/vm.h"
#include "../headers/exception_handler.h"

void ExceptionHandler::EH_exit(){
    exit(VM_TRUE);
}

void ExceptionHandler::EH_abort(){
    abort();
}

bool ExceptionHandler::CheckForArithmeticOverflow(const int32_t operand1, const int32_t operand2, const int32_t opcode) {
    if((operand2 > 0 && operand1 > (INT32_MAX - operand2)) || (operand2 < 0 && operand1 < (INT32_MAX - operand2))) {
        Handler(EXCEPTION_ARITHMETIC_OVERFLOW, opcode);
        return true;
    }

    return false;
}

void ExceptionHandler::Handler(const uint32_t exception_code, const int32_t opcode) {

    if(exception_code == VM_ZERO) {
        return;
    }

    const std::string &filename = GetBcFilename();

    switch(exception_code){
        case EXCEPTION_DIVIDE_BY_ZERO:
            fprintf(stderr, "\n[-] Line %d in %s:\n\tEXCEPTION_DIVIDE_BY_ZERO: Operation not permitted.\n", (get_ip()-1), filename.c_str());
        EH_exit();
        break;
        case EXCEPTION_UNKNOWN_OPCODE:
            fprintf(stderr, "\n[-] Line %d in %s:\n\t[-] EXCEPTION_UNKNOWN_OPCODE: Unknown opcode: %d\n", (get_ip()-1), filename.c_str(), opcode);
        EH_exit();
        break;
        case EXCEPTION_ARITHMETIC_OVERFLOW:
            fprintf(stderr, "\n[-] Line %d in %s:\n\t[-] EXCEPTION_ARITHMETIC_OVERFLOW: The maximum integer size is 32-bit.", (get_ip()-1), filename.c_str());
        EH_exit();
        break;
        case EXCEPTION_IP_OVERFLOW:
            fprintf(stderr, "\n[-] Line %d in %s:\n\t[-] EXCEPTION_IP_OVERFLOW: The Instruction pointer is bigger than the bytecode boundaries.", (get_ip()-1), filename.c_str());
        EH_exit();
        break;
        default:
            return;
    }

}