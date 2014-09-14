#include "auto_proc.h"
#include "syscall_error.h"
#include <unistd.h>
#include <sys/wait.h>

using namespace util;

namespace {
  int do_fork(const std::string &command) {
    auto result = fork();

    if (result < 0) {
      throw syscall_error("fork", command);
    }

    return result;
  }
};

auto_proc::auto_proc(
    const std::string &command) {
  this->process_id = do_fork(command);

  if (this->process_id == 0) {
    execlp(command.c_str(), command.c_str(), NULL);

    throw syscall_error("execlp", command);
  }
}

auto_proc::auto_proc(
    const std::string &command, const std::string &arg1) {
  this->process_id = do_fork(command);

  if (this->process_id == 0) {
    execlp(command.c_str(), command.c_str(), arg1.c_str(), NULL);

    throw syscall_error("execlp", command);
  }
}

auto_proc::auto_proc(
    const std::string &command, const std::string &arg1,
    const std::string &arg2) {
  this->process_id = do_fork(command);

  if (this->process_id == 0) {
    execlp(command.c_str(), command.c_str(), arg1.c_str(), arg2.c_str(), NULL);

    throw syscall_error("execlp", command);
  }
}

auto_proc::auto_proc(
    const std::string &command, const std::string &arg1,
    const std::string &arg2, const std::string &arg3) {
  this->process_id = do_fork(command);

  if (this->process_id == 0) {
    execlp(command.c_str(), command.c_str(), arg1.c_str(), arg2.c_str(),
        arg3.c_str(), NULL);

    throw syscall_error("execlp", command);
  }
}

auto_proc::auto_proc(
    const std::string &command, const std::string &arg1,
    const std::string &arg2, const std::string &arg3,
    const std::string &arg4) {
  this->process_id = do_fork(command);

  if (this->process_id == 0) {
    execlp(command.c_str(), command.c_str(), arg1.c_str(), arg2.c_str(),
        arg3.c_str(), arg4.c_str(), NULL);

    throw syscall_error("execlp", command);
  }
}

auto_proc::auto_proc(
    const std::string &command, const std::string &arg1,
    const std::string &arg2, const std::string &arg3,
    const std::string &arg4, const std::string &arg5) {
  this->process_id = do_fork(command);

  if (this->process_id == 0) {
    execlp(command.c_str(), command.c_str(), arg1.c_str(), arg2.c_str(),
        arg3.c_str(), arg4.c_str(), arg5.c_str(),  NULL);

    throw syscall_error("execlp", command);
  }

}

pid_t auto_proc::pid() const {
  return this->process_id;
}

auto_proc::~auto_proc() {
  int status;
  waitpid(this->process_id, &status, 0);
}
