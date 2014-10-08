#ifndef __SYSCALLS__SHMEM__H_INCLUDED__
#define __SYSCALLS__SHMEM__H_INCLUDED__

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

namespace syscalls {
  int shmget(size_t size);

  void shmrelease(int id);

  void *shmat(int id);

  void shmdt(void *address);
}

#endif
