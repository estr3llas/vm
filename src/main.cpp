
#include <windows.h>

#include "../headers/common.h"
#include "../headers/vm.h"
#include "../headers/Examples.h"
#include "../headers/misc/usage.h"
#include "../headers/aa/antidump.h"

int main (int argc, char** argv) {

    if(argc < 2) printf(USAGE, VM_VERSION);

    EnableAntidump();

    VM vm (Examples::push_module, Examples::PUSH_MODULE_ENTRYPOINT, 0);
    vm.SetTrace(VM_TRUE);
    vm.VMExec();

    return 0;

}