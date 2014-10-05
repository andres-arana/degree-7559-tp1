#include "syscalls/signal.h"
#include <cstring>

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
