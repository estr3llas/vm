//
// Created by User on 7/16/2024.
//
#include "../headers/common.h"
#include "../headers/vm.h"
#include "../headers/Bytecode.h"
#include "../headers/exceptions.h"
#include "../headers/nt/parser.h"
#include "../headers/nt/syscalls.h"
#include "../headers/nt/params.h"

VM::VM() :
    ip(VM_ZERO),
    sp(),
    fp(VM_ZERO),
    ctx(Context(nullptr, 0, LOCALS_MAX_SIZE))
    {};

VM::VM(const std::vector<int>& bytecode, const int32_t entrypoint, const size_t datasize) :
    code(bytecode),
    ip(entrypoint),
    data(
        datasize
            != DATA_MAX_SIZE
            ? datasize
            : DATA_MAX_SIZE
        ),
    stack(STACK_MAX_SIZE),
    fp(VM_ZERO),
    ctx(Context(nullptr, 0, LOCALS_MAX_SIZE))
    {};

void VM::SetTrace(const bool value) {
    trace = value;
}

template<typename T>
void VM::VMPrint(T arg){

    if(typeid(arg) == typeid(PVOID)) {
        vm_print_ok("%p\n", arg);
        return;
    }

    if(typeid(arg) == typeid(int64_t)) {
        vm_print_ok("%llx\n", arg);
        return;
    }

    vm_print_ok("%d\n", arg);
}

uint32_t VM::get_ip() const {
    return ip;
}

void VM::SetBcFilename(const std::string &filename) {
    filename.empty()
    ? bc_filename = nullptr
    : bc_filename = filename;
}

const std::string& VM::GetBcFilename() {
    return bc_filename;
}

void VM::Disassemble(const int32_t opcode) const {

    if (ip >= code.size()) return;

    const Instruction instr = Instructions::opcodes[opcode];
    printf("%04d: %-16s", ip, instr.getMnemonic());

    bool noops = false;
    //print operands
    switch (instr.getOperand()) {
        case 1:
            vm_print_ok(" %d", code[ip + 1]);
            break;
        case 2:
            vm_print_ok(" %d, %d", code[ip + 1], code[ip + 2]);
            break;
        case 3:
            vm_print_ok(" %d, %d, %d", code[ip + 1], code[ip + 2], code[ip + 3]);
            break;
        default:
            noops = true;
            break;
    }

    //print current stack
    vm_print_ok("\t\t");
    if(noops) vm_print_ok("\t");
    if (sp == -1) {
        vm_print_ok("[ ]\n");
    } else {
        vm_print_ok("[");
        for (int i = 0; i <= sp; ++i) {
            vm_print_ok("%ld", stack[i]);
        if (i < sp) {
            vm_print_ok(", ");
        }
        }
        vm_print_ok("]\n");
    }
}

VMReturn VM::VMExec() {
    //ctx = Context();
    Cpu();
    return STATUS_EXECUTION_OK;
}

// hacky
int_fast32_t global_mem[DATA_MAX_SIZE];
int_fast64_t global_mem_64[DATA_MAX_SIZE];

void VM::Cpu() {

    ExceptionHandler _exception_handler;

    if (ip > code.size()) {
        _exception_handler.Handler(ExceptionHandler::exception_codes::EXCEPTION_IP_OVERFLOW, 0);
    }

    int32_t operand, addr, offset;
    int64_t a, b, operand_64;
    int32_t first_arg;
    int32_t nargs;

    std::vector<Context> call_stack;

    while(ip < code.size()) {
        const int32_t opcode = code[ip];
        if(trace) {
            VM::Disassemble(opcode);
        }
        ip++;
        switch (opcode) {
            case VM_NOP:
                // just for padding
            break;
            case VM_GLOAD:
                addr = code[ip];
                ip++;
                operand = global_mem[addr];
                sp++;
                stack[sp] = operand;
            break;
            case VM_GSTORE:
                operand_64 = stack[sp];
                sp--;
                addr = code[ip];
                ip++;
                global_mem_64[addr] = operand_64;
            break;
            case VM_CALL:
                addr = code[ip++];
                nargs = code[ip++];
                call_stack.push_back(ctx);
                ctx = Context(&call_stack.back(), (++ip), LOCALS_MAX_SIZE);
                first_arg = sp - (nargs + 1);
                for (int i = 0; i < nargs; i++) {
                    ctx.getLocals()[i] = stack[first_arg + i];
                }
                sp -= nargs;
                ip = addr;
            break;
            case VM_RET:
                //ctx = call_stack.back();
                call_stack.pop_back();
                ip = ctx.getReturnIp();
            break;
            case VM_LOAD:
                offset = code[ip++];
                ctx = Context(&ctx, ip, LOCALS_MAX_SIZE);
                stack[++sp] = ctx.getLocals()[offset];
            break;
            case VM_EQ:
                b = stack[sp--];
                a = stack[sp--];
                stack[++sp] = a == b;
            break;
            case VM_LT:
                b = stack[sp--];
                a = stack[sp--];
                stack[++sp] = a < b;
            break;
            case VM_BR:
                ip = code[ip++];
            break;
            case VM_BRT:
                addr = code[ip++];
                if (stack[sp--] == VM_TRUE) ip = addr;
            break;
            case VM_BRF:
                addr = code[ip++];
                if (stack[sp--] == VM_FALSE) ip = addr;
            break;
            case VM_ADD:
                b = stack[sp--];
                a = stack[sp--];
                _exception_handler.CheckForArithmeticOverflow(a, b, opcode);
                stack[++sp] = a + b;
            break;
            case VM_SUB:
                b = stack[sp--];
                a = stack[sp--];
                _exception_handler.CheckForArithmeticOverflow(a, b, opcode);
                stack[++sp] = a - b;
            break;
            case VM_MUL:
                b = stack[sp--];
                a = stack[sp--];
                _exception_handler.CheckForArithmeticOverflow(a, b, opcode);
                stack[++sp] = a * b;
            break;
            case VM_DIV:
                b = stack[sp--];
                a = stack[sp--];
                if(b == 0) {
                    _exception_handler.Handler(ExceptionHandler::exception_codes::EXCEPTION_DIVIDE_BY_ZERO, opcode);
                }
                stack[++sp] = a / b;
            break;
            case VM_NEG:
                a = stack[sp--];
                stack[++sp] = (-a);
            break;
            case VM_INC:
                a = stack[sp--];
                a = a + 1;
                stack[++sp] = a;
            break;
            case VM_DEC:
                a = stack[sp--];
                a = a - 1;
                stack[++sp] = a;
            break;
            case VM_CONST:
                stack[++sp] = code[ip++];
            break;
            case VM_POP:
                --sp;
            break;
            case VM_PRINT:
                VMPrint(stack[sp--]);
            break;
            // pushes the module base to stack
            case VM_MODULE_BASE:
                stack[++sp] = reinterpret_cast<int64_t>(getModuleBase());
            break;
            // the top 3 values of stacks will be popped in order to pass as parameters to FnVMAlloc
            case VM_ALLOC:
            {
                SIZE_T alloc_size = stack[sp--];
                const ULONG alloc_type = stack[sp--];
                const ULONG alloc_protect = stack[sp--];
                stack[++sp] = reinterpret_cast<int64_t>(vm_alloc(&alloc_size, alloc_type, alloc_protect));
            }
            break;
            // the same as VM_ALLOC, but pushes if the free was successful or not
            case VM_FREE:
            {
                auto free_ba = stack[sp--];
                SIZE_T free_size = stack[sp--];
                const ULONG free_type = stack[sp--];
                if (vm_free(reinterpret_cast<PVOID>(free_ba), &free_size, free_type) == STATUS_SUCCESS) {
                    stack[++sp] = 0;
                } else {
                    stack[++sp] = 1;
                }
            }
            break;
            case VM_HALT:
                return;
            default:
                //__builtin_unreachable();
                //
                // By applying "__builtin_unreachable()", clang would remove the following:
                //
                //      lea     ecx, [rbx-1]    ; switch 27 cases
                //      cmp     ecx, 1Ah
                //      ja      def_1400029EB   ; jumptable 00000001400029EB default case, cases 13,24
                //
                // which makes the jump table unbounded.
                // Still thinking if it is worth it.

                _exception_handler.Handler(ExceptionHandler::exception_codes::EXCEPTION_UNKNOWN_OPCODE, opcode);
                return;
        }
    }
}