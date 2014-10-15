#include "syscalls/process.h"
#include "syscalls/signal.h"
#include "raii/proc.h"
#include <iostream>

using namespace raii;
using namespace std;

proc::proc()
  : process_id(-1) {

  }

proc::proc(bool interrupt, const string &command)
  : proc(interrupt, command, {}){

  }

proc::proc(
    bool interrupt,
    const string& command,
    const vector<string> &args)
  : interrupt(interrupt), command(command) {

    process_id = syscalls::fork(command);

    if (process_id == 0) {
      syscalls::execv(command, args);
    }
  }

proc::proc(proc &&other)
  : process_id(other.process_id), interrupt(other.interrupt), command(other.command) {
    other.process_id = -1;
  }

proc & proc::operator=(proc &&other) {
  syscalls::wait(process_id);
  process_id = other.process_id;
  interrupt = other.interrupt;
  command = other.command;
  other.process_id = -1;
  return *this;
}

pid_t proc::pid() const {
  return process_id;
}

void proc::signal(int signal) {
  syscalls::kill(process_id, signal);
}

proc::~proc() {
  if (process_id > 0 && interrupt) {
    signal(SIGINT);
  }
  syscalls::wait(process_id);
}

