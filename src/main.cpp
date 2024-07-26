
#include <windows.h>

#include "../headers/common.h"
#include "../headers/vm.h"
#include "../headers/Examples.h"
#include "../headers/parser.h"
#include "../headers/peb.h"

//#include "../lib/include/boost/program_options.hpp"

#define MAIN_ADDR 0
#define VM_VERSION "0.0.1"
#define USAGE   " Estrellas's simple vm.\n"                           \
                " Version: %s\n\n"                                    \
                " [+] Usage: vm.exe <bytecode>\n\n"                   \
                " Contact: https://github.com/estr3llas\n\n"

int main (int argc, char** argv) {

    //if(argc < 2) printf(USAGE, VM_VERSION);

    VM vm (Examples::push_module, Examples::PUSH_MODULE_ENTRYPOINT, 0);
    vm.SetTrace(VM_TRUE);
    const VMReturn ret = vm.VMExec();

    printf("\n[!] VMReturn: %d", ret);

    return 0;
}