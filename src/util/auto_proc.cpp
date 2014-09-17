#include "auto_proc.h"
#include "syscall_error.h"
#include <unistd.h>
#include <sys/wait.h>

using namespace util;
using namespace std;

namespace {
  int do_fork(const string &command, const vector<string> &args) {
    auto result = fork();

    if (result < 0) {
      throw syscall_error("fork", command);
    } else if (result == 0) {
      vector<const char*> actual_args;
      actual_args.push_back(command.c_str());
      for (auto arg : args) {
        actual_args.push_back(arg.c_str());
      }
      actual_args.push_back(nullptr);
      auto raw_args = const_cast<char * const *>(actual_args.data());

      execv(command.c_str(), raw_args);

      throw syscall_error("execv", command);
    }

    return result;
  }

  void do_wait(int process_id) {
    if (process_id > 0) {
      int status;
      waitpid(process_id, &status, 0);
    }
  }
};

auto_proc::auto_proc()
  : process_id(-1) {

  }

auto_proc::auto_proc(const string& command, const vector<string> &args)
  : process_id(::do_fork(command, args)) {

  }

auto_proc::auto_proc(auto_proc &&other)
  : process_id(other.process_id) {
    other.process_id = -1;
  }

auto_proc & auto_proc::operator=(auto_proc &&other) {
  ::do_wait(this->process_id);
  this->process_id = other.process_id;
  other.process_id = -1;
  return *this;
}

pid_t auto_proc::pid() const {
  return this->process_id;
}

auto_proc::~auto_proc() {
  ::do_wait(this->process_id);
}

