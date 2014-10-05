#ifndef __SYSCALLS__ERROR_H_INCLUDED__
#define __SYSCALLS__ERROR_H_INCLUDED__

#include <stdexcept>
#include <string>

namespace syscalls {
    class error : public std::runtime_error {
      public:
        explicit error(
            const std::string &syscall);

        explicit error(
            const std::string &syscall,
            const std::string &context);
    };
}

#endif
