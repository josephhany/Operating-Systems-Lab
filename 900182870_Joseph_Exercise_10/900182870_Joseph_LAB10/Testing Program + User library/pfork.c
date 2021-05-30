#include "pfork.h"

pid_t pfork(){
    return syscall(440);
}

int get_pfork_status(){
    return syscall(441);
}

pid_t get_pfork_sibling_pid(){
    return syscall(442);
}

int pfork_who(){
    return syscall(444);
}

void set_pfork_status(int status){
    syscall(443,status);
}

