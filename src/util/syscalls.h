#ifndef __UTIL_SYSCALLS_H_INCLUDED
#define __UTIL_SYSCALLS_H_INCLUDED

#include <string>
#include <vector>
#include <stdexcept>
#include <sys/types.h>
#include <signal.h>

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

    int open(const std::string &filename, int flags, int permissions);

    void write(int fd, const std::string &what);

    void close(int fd);

    void flock(int fd);

    void funlock(int fd);

    int fork(const std::string &command);

    void execv(
        const std::string &command, const std::vector<std::string> &args);

    int wait(pid_t pid);

    pid_t getpid();

    void kill(pid_t pid, int signal);

    void sigaction(int signal, sighandler_t handler);
  };
};

#endif
