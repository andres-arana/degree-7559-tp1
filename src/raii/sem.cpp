#include "raii/sem.h"
#include "syscalls/sem.h"

using namespace raii;

sem::sem(int semid, int semnum)
  : semid(semid), semnum(semnum) {

  }

void sem::wait(int amount) {
  syscalls::semwait(semid, semnum, amount);
}

bool sem::try_wait(int amount) {
  return syscalls::try_semwait(semid, semnum, amount);
}

void sem::signal(int amount) {
  syscalls::semsignal(semid, semnum, amount);
}

void sem::control() {
  syscalls::semcontrol(semid, semnum);
}
