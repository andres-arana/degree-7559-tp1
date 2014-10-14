#include "raii/sem_set.h"
#include "syscalls/sem.h"

using namespace raii;

sem_set::sem_set(int semid)
  : semid(semid) {

  }

void sem_set::wait(int semnum, int amount) {
  syscalls::semwait(semid, semnum, amount);
}

bool sem_set::try_wait(int semnum, int amount) {
  return syscalls::try_semwait(semid, semnum, amount);
}

void sem_set::signal(int semnum, int amount) {
  syscalls::semsignal(semid, semnum, amount);
}

void sem_set::control(int semnum) {
  syscalls::semcontrol(semid, semnum);
}
