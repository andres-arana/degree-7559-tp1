#include "syscalls/sleep.h"

#include <time.h>

void syscalls::sleep(unsigned int seconds) {
  timespec timeout;
  timeout.tv_sec = seconds;
  timeout.tv_nsec = 0;

  if (::nanosleep(&timeout, nullptr)) {
    syscalls::check_interrupt("nanosleep");
  }
}
