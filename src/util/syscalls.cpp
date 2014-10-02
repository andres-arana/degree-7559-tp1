#include "syscalls.h"
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <errno.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <signal.h>

using namespace util;
using namespace std;

namespace {
  string build_error_message(const string &syscall, const string &context) {
    stringstream error;
    error << "La syscall " << syscall << " ";
    if (context != "") {
      error << "(" << context << ") ";
    }
    error << "fallo con errno [" << errno << "]";

    return error.str();
  }
};

syscalls::error::error(const string &syscall, const string &context)
  : runtime_error(::build_error_message(syscall, context)) {

  }

syscalls::error::error(const string &syscall)
  : runtime_error(::build_error_message(syscall, "")) {

  }


void syscalls::close(int fd) {
  if (fd > 0) {
    auto result = ::close(fd);

    if (result < 0) {
      throw syscalls::error("close");
    }
  }

}

int syscalls::open(
    const string &filename, int flags, int permissions) {

  auto result = ::open(filename.c_str(), flags, permissions);

  if (result < 0) {
    throw syscalls::error("open", filename);
  }

  return result;
}

void syscalls::flock(int fd) {
  if (fd > 0 && ::flock(fd, LOCK_EX)) {
    throw syscalls::error("flock", "LOCK_EX");
  }
}

void syscalls::funlock(int fd) {
  if (fd > 0 && ::flock(fd, LOCK_UN)) {
    throw syscalls::error("flock", "LOCK_UN");
  }
}

int syscalls::fork(const string &command) {
  auto result = ::fork();

  if (result < 0) {
    throw syscalls::error("fork", command);
  }

  return result;
}

void syscalls::execv(const string &command, const vector<string> &args) {
  vector<const char *> actual_args;
  actual_args.push_back(command.c_str());
  for (auto arg : args) {
    actual_args.push_back(arg.c_str());
  }
  actual_args.push_back(nullptr);
  auto raw_args = const_cast<char * const *>(actual_args.data());

  ::execv(command.c_str(), raw_args);

  throw syscalls::error("execv", command);
}

int syscalls::wait(pid_t pid) {
  int status;
  if (pid > 0 && ::waitpid(pid, &status, 0) < 0) {
    throw syscalls::error("waitpid");
  }

  return status;
}

pid_t syscalls::getpid() {
  auto result = ::getpid();

  if (result < 0) {
    throw syscalls::error("getpid");
  }

  return result;
}

void syscalls::write(int fd, const string &what) {
  if (::write(fd, what.c_str(), what.length()) < 0) {
    throw syscalls::error("write");
  }
}

void syscalls::kill(pid_t pid, int signal) {
  if (::kill(pid, signal)) {
    throw syscalls::error("kill");
  }
}

void syscalls::sigaction(int signal, sighandler_t handler) {
  struct sigaction action;
  memset(&action, 0, sizeof(action));
  action.sa_handler = handler;
  ::sigemptyset(&action.sa_mask);
  ::sigaddset(&action.sa_mask, signal);

  if (::sigaction(signal, &action, nullptr)) {
    throw syscalls::error("sigaction");
  }
}
