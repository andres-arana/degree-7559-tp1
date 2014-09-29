#ifndef __UTIL_SYSCALLS_H_INCLUDED
#define __UTIL_SYSCALLS_H_INCLUDED

#include <string>
#include <vector>
#include <stdexcept>

namespace util {
  namespace syscalls {

    class error : public std::runtime_error {
      public:
        explicit error(
            const std::string &syscall);

        explicit error(
            const std::string &syscall,
            const std::string &context);
    };

    int checked_open(const std::string &filename, int flags, int permissions);

    void checked_write(int fd, const std::string &what);

    void checked_close(int fd);

    void checked_flock(int fd);

    void checked_funlock(int fd);

    int checked_fork(const std::string &command);

    void checked_execv(
        const std::string &command, const std::vector<std::string> &args);

    int checked_wait(int pid);

    int checked_getpid();


  };
};

#endif
