//
// Created by User on 7/16/2024.
//
#include "../headers/common.h"
#include "../headers/vm.h"
#include "../headers/exception_handler.h"

auto ExceptionHandler::EH_exit() -> void{
    exit(VM_TRUE);
}

auto ExceptionHandler::EH_abort() -> void{
    abort();
}

auto ExceptionHandler::CheckForArithmeticOverflow(const int64_t operand1, const int64_t operand2, const int32_t opcode) {
    if((operand2 > 0 && operand1 > (INT32_MAX - operand2)) || (operand2 < 0 && operand1 < (INT32_MAX - operand2)))
        Handler(EXCEPTION_ARITHMETIC_OVERFLOW, opcode);
}

auto ExceptionHandler::Handler(const uint32_t exception_code, const int32_t opcode) {

    if(exception_code == VM_ZERO) {
        return;
    }

    const std::string &filename = GetBcFilename();

    switch(exception_code){
        case EXCEPTION_DIVIDE_BY_ZERO:
            vm_print_err("\n[-] Line %d in %s:\n\tEXCEPTION_DIVIDE_BY_ZERO: Operation not permitted.\n", (get_ip()-1), filename.c_str());
            EH_exit();
            break;
        case EXCEPTION_UNKNOWN_OPCODE:
            vm_print_err("\n[-] Line %d in %s:\n\t[-] EXCEPTION_UNKNOWN_OPCODE: Unknown opcode: %d\n", (get_ip()-1), filename.c_str(), opcode);
            EH_exit();
            break;
        case EXCEPTION_ARITHMETIC_OVERFLOW:
            vm_print_err("\n[-] Line %d in %s:\n\t[-] EXCEPTION_ARITHMETIC_OVERFLOW: The maximum integer size is 32-bit.", (get_ip()-1), filename.c_str());
            EH_exit();
            break;
        case EXCEPTION_IP_OVERFLOW:
            vm_print_err("\n[-] Line %d in %s:\n\t[-] EXCEPTION_IP_OVERFLOW: The Instruction pointer is bigger than the bytecode boundaries.", (get_ip()-1), filename.c_str());
            EH_exit();
            break;
        default:
            return;
    }

}