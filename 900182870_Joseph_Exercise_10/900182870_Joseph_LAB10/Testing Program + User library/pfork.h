#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>

pid_t pfork();

int get_pfork_status();

pid_t get_pfork_sibling_pid();

int pfork_who();

void set_pfork_status(int status);

