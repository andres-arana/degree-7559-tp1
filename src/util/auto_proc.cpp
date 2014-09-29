#include "auto_proc.h"
#include "syscalls.h"

using namespace util;
using namespace std;

auto_proc::auto_proc()
  : process_id(-1) {

  }

auto_proc::auto_proc(const string &command)
  : auto_proc(command, {}){

}

auto_proc::auto_proc(const string& command, const vector<string> &args) {
  process_id = syscalls::checked_fork(command);

  if (process_id == 0) {
    syscalls::checked_execv(command, args);
  }
}

auto_proc::auto_proc(auto_proc &&other)
  : process_id(other.process_id) {
    other.process_id = -1;
  }

auto_proc & auto_proc::operator=(auto_proc &&other) {
  syscalls::checked_wait(process_id);
  process_id = other.process_id;
  other.process_id = -1;
  return *this;
}

pid_t auto_proc::pid() const {
  return process_id;
}

void auto_proc::signal(int signal) {
  syscalls::checked_kill(process_id, signal);

}

auto_proc::~auto_proc() {
  syscalls::checked_wait(process_id);
}

