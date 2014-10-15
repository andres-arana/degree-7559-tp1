#ifndef __SYSCALLS__SLEEP__H_INCLUDED__
#define __SYSCALLS__SLEEP__H_INCLUDED__

#include "syscalls/error.h"
#include "syscalls/interrupt.h"

namespace syscalls {
  void sleep(unsigned int seconds);
}

#endif
