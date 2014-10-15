#ifndef __SYSCALLS__SHMEM__H_INCLUDED__
#define __SYSCALLS__SHMEM__H_INCLUDED__

#include "syscalls/error.h"
#include "syscalls/interrupt.h"

namespace syscalls {
  int shmget(size_t size);

  void shmrelease(int id);

  void *shmat(int id);

  void shmdt(void *address);
}

#endif
