#include "syscalls/shmem.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

using namespace std;

namespace {
  const int PERMISSIONS = 0666;
}

int syscalls::shmget(size_t size) {
  auto result = ::shmget(IPC_PRIVATE, size, ::PERMISSIONS);

  if (result < 0) {
    throw syscalls::error("shmget");
  }

  return result;
}

void syscalls::shmrelease(int id) {
  auto result = ::shmctl(id, IPC_RMID, nullptr);

  if (result < 0) {
    throw syscalls::error("shmctl", "IPC_RMID");
  }
}

void *syscalls::shmat(int id) {
  auto result = ::shmat(id, nullptr, 0);

  if (reinterpret_cast<void*>(-1) == result) {
    throw syscalls::error("shmat");
  }

  return result;
}

void syscalls::shmdt(void *address) {
  auto result = ::shmdt(address);

  if (result < 0) {
    throw syscalls::error("shmdt");
  }
}

