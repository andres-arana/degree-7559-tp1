#include "syscalls/sem.h"
#include "syscalls/error.h"

using namespace std;

namespace {
  const int PERMISSIONS = 0666;

  union semun {
    int             val;
    semid_ds        *buf;
    unsigned short  *array;
    seminfo         *__buf;
  };

  int sem_op(int id, int semnum, int op) {
    sembuf sem_b;

    sem_b.sem_num = semnum;
    sem_b.sem_op = op;

    return ::semop(id, &sem_b, 1);
  }

}

int syscalls::semget(unsigned short int nsem) {
  auto result = ::semget(IPC_PRIVATE, nsem, ::PERMISSIONS | IPC_CREAT);

  if (result < 0) {
    throw syscalls::error("semget");
  }

  return result;
}

void syscalls::semrelease(int id) {
  auto result = ::semctl(id, 0, IPC_RMID);

  if (result < 0) {
    throw syscalls::error("semctl", "IPC_RMID");
  }
}

vector<unsigned short> syscalls::sem_getall(int id, int semnum) {
  semun semarg;
  vector<unsigned short> forks(semnum);
  semarg.array = forks.data();
  auto result = ::semctl(id, 0, GETALL, semarg);

  if (result < 0) {
    throw syscalls::error("sem_getall");
  }

  return forks;
}

int syscalls::sem_getncnt(int id, int semnum) {
  auto result = ::semctl(id, semnum, GETNCNT);

  if (result < 0) {
    throw syscalls::error("sem_getncnt");
  }

  return result;
}

int syscalls::sem_getpid(int id, int semnum) {
  auto result = ::semctl(id, semnum, GETPID);

  if (result < 0) {
    throw syscalls::error("sem_getpid");
  }

  return result;
}

int syscalls::sem_getval(int id, int semnum) {
  semun semarg;
  auto result = ::semctl(id, semnum, GETVAL, semarg);

  if (result < 0) {
    throw syscalls::error("sem_getval");
  }

  return semarg.val;
}

int syscalls::sem_getzcnt(int id, int semnum) {
  semun semarg;
  auto result = ::semctl(id, semnum, GETZCNT, semarg);

  if (result < 0) {
    throw syscalls::error("sem_getzcnt");
  }

  return result;
}

void syscalls::sem_setall(int id, const vector<unsigned short> &forks) {
  semun semarg;
  semarg.array = const_cast<unsigned short *>(forks.data());
  auto result = ::semctl(id, 0, SETALL, semarg);

  if (result < 0) {
    throw syscalls::error("sem_setall");
  }
}

void syscalls::sem_setval(int id, int semnum, int semval) {
  semun sem_union;
  sem_union.val = semval;
  auto result = ::semctl(id, semnum, SETVAL, sem_union);

  if (result < 0) {
    throw syscalls::error("sem_setval");
  }
}

void syscalls::sem_signal(int id, int semnum, int amount) {
  auto result = sem_op(id, semnum, amount);

  if (result < 0) {
    throw syscalls::error("semop", "signal");
  }
}

void syscalls::sem_wait(int id, int semnum, int amount) {
  auto result = sem_op(id, semnum, -amount);

  if (result < 0) {
    throw syscalls::error("semop", "wait");
  }
}

void syscalls::sem_control(int id, int semnum) {
  auto result = sem_op(id, semnum, 0);

  if (result < 0) {
    throw syscalls::error("semop", "control");
  }
}
