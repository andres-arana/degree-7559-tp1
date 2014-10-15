#include "syscalls/process.h"
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

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

  if (pid > 0) {
    while (::waitpid(pid, &status, 0) < 0) {
      if (errno != EINTR) {
        throw syscalls::error("waitpid");
      }
    }
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
