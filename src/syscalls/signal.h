#ifndef __SYSCALLS__SIGNAL_H_INCLUDED__
#define __SYSCALLS__SIGNAL_H_INCLUDED__

#include "syscalls/error.h"
#include <signal.h>
#include <sys/types.h>

namespace syscalls {
    void kill(pid_t pid, int signal);

    void sigaction(int signal, sighandler_t handler);
}

#endif

