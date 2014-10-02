#include "auto_proc.h"
#include "syscalls.h"

using namespace util;
using namespace std;

auto_proc::auto_proc()
  : process_id(-1) {

  }

auto_proc::auto_proc(bool interrupt, const string &command)
  : auto_proc(interrupt, command, {}){

  }

auto_proc::auto_proc(
    bool interrupt,
    const string& command,
    const vector<string> &args)
  : interrupt(interrupt) {

    process_id = syscalls::fork(command);

    if (process_id == 0) {
      syscalls::execv(command, args);
    }
  }

auto_proc::auto_proc(auto_proc &&other)
  : process_id(other.process_id), interrupt(other.interrupt) {
    other.process_id = -1;
  }

auto_proc & auto_proc::operator=(auto_proc &&other) {
  syscalls::wait(process_id);
  process_id = other.process_id;
  interrupt = other.interrupt;
  other.process_id = -1;
  return *this;
}

pid_t auto_proc::pid() const {
  return process_id;
}

void auto_proc::signal(int signal) {
  syscalls::kill(process_id, signal);
}

auto_proc::~auto_proc() {
  if (process_id > 0 && interrupt) {
    signal(SIGINT);
  }

  syscalls::wait(process_id);
}

