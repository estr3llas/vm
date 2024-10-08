//
// Created by User on 7/16/2024.
//
#ifndef VM_VM_H
#define VM_VM_H

#include "./common.h"

#define DATA_MAX_SIZE 4096
#define STACK_MAX_SIZE 1000
#define LOCALS_MAX_SIZE 256

#define VM_TRUE true
#define VM_FALSE false
#define VM_ZERO (0)
#define VM_SP_START (-1)

#define vm_print_ok(fmt, ...) \
    fprintf(stdout, (fmt) __VA_OPT__(,) __VA_ARGS__)

#define vm_print_err(fmt, ...) \
    fprintf(stderr, (fmt) __VA_OPT__(,) __VA_ARGS__)

class Context {
private:

    Context* prev;
    uint32_t return_ip;
public:

    std::vector<int64_t> locals;

    Context() :
    prev(nullptr),
    return_ip(0)
    {}
    ;

    Context(Context* _prev, uint32_t _return_ip, int32_t number_of_locals) :
    prev(_prev),
    return_ip(_return_ip),
    locals(number_of_locals)
    {}
    ;

    std::vector<int64_t>& getLocals() {
        return locals;
    }

    [[nodiscard]] int32_t getReturnIp() const {
        return static_cast<int32_t>(return_ip);
    }

    [[nodiscard]] Context* getPrev() const {
        return prev;
    }
};

typedef enum {
    STATUS_EXECUTION_OK = 0,
    STATUS_COMPILE_ERROR = 1,
    STATUS_RUNTIME_ERROR = 2,
} VMReturn;

class VM {
private:
    std::vector<int32_t> data;
    std::vector<int32_t> code;
    std::vector<int64_t> stack;

    Context ctx;

    std::string bc_filename;

    uint32_t ip;
    //must start below stack, every operation pushes something onto stack (preventing off by one)
    int32_t sp = VM_SP_START;
    int32_t fp;

    bool trace = false;
public:

    VM();
    VM(const std::vector<int32_t>& bytecode, int32_t entrypoint, size_t datasize);

    VMReturn VMExec();
    void Cpu();
    void Disassemble(int32_t opcode) const;

    template<typename  T>
    static void VMPrint(T arg);

    [[nodiscard]] uint32_t get_ip() const;

    void SetTrace(bool value);
    void SetBcFilename(const std::string &filename);
    const std::string &GetBcFilename();

    Context& GetCtx(){
        return ctx;
    }

};

#endif