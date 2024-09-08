
#include <windows.h>

#include "../headers/common.h"
#include "../headers/vm.h"
#include "../headers/Examples.h"
#include "../headers/misc/usage.h"
#include "../headers/nt/parser.h"
#include "../headers/nt/peb.h"
#include "../headers/aa/antidump.h"
//#include "../headers/nt/parser.h"

//#include "../lib/include/boost/program_options.hpp"

int main (int argc, char** argv) {

    /*
    if(argc < 2) printf(USAGE, VM_VERSION);

    VM vm (Examples::push_module, Examples::PUSH_MODULE_ENTRYPOINT, 0);
    vm.SetTrace(VM_TRUE);
    vm.VMExec();

    return 0;
    */

    peb::PPEB peb = getPeb();
    IncreaseSizeOfImage(peb);

    WaitForSingleObject((HANDLE)(-1), INFINITE);
}