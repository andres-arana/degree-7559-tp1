#ifndef __SYSCALLS__FILE_H_INCLUDED__
#define __SYSCALLS__FILE_H_INCLUDED__

#include <string>
#include "syscalls/error.h"

namespace syscalls {
    int open(const std::string &filename, int flags, int permissions);

    void write(int fd, const std::string &what);

    void close(int fd);

    void flock(int fd);

    void funlock(int fd);
}

#endif
