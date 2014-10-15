#ifndef __SYSCALLS__PROCESSS_H_INCLUDED__
#define __SYSCALLS__PROCESSS_H_INCLUDED__

#include <string>
#include <vector>
#include <sys/types.h>
#include "syscalls/error.h"
#include "syscalls/interrupt.h"

namespace syscalls {
    int fork(const std::string &command);

    int wait(pid_t pid);

    pid_t getpid();

    void execv(
        const std::string &command, const std::vector<std::string> &args);
}

#endif

