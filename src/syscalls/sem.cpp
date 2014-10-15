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

  int sem_op(int id, int semnum, int op, int flags) {
    sembuf sem_b;

    sem_b.sem_num = semnum;
    sem_b.sem_op = op;
    sem_b.sem_flg = flags;

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

vector<unsigned short> syscalls::semgetall(int id, int semnum) {
  semun semarg;
  vector<unsigned short> forks(semnum);
  semarg.array = forks.data();
  auto result = ::semctl(id, 0, GETALL, semarg);

  if (result < 0) {
    throw syscalls::error("semgetall");
  }

  return forks;
}

int syscalls::semgetncnt(int id, int semnum) {
  auto result = ::semctl(id, semnum, GETNCNT);

  if (result < 0) {
    throw syscalls::error("semgetncnt");
  }

  return result;
}

int syscalls::semgetpid(int id, int semnum) {
  auto result = ::semctl(id, semnum, GETPID);

  if (result < 0) {
    throw syscalls::error("semgetpid");
  }

  return result;
}

int syscalls::semgetval(int id, int semnum) {
  semun semarg;
  auto result = ::semctl(id, semnum, GETVAL, semarg);

  if (result < 0) {
    throw syscalls::error("semgetval");
  }

  return semarg.val;
}

int syscalls::semgetzcnt(int id, int semnum) {
  semun semarg;
  auto result = ::semctl(id, semnum, GETZCNT, semarg);

  if (result < 0) {
    throw syscalls::error("semgetzcnt");
  }

  return result;
}

void syscalls::semsetall(int id, const vector<unsigned short> &forks) {
  semun semarg;
  semarg.array = const_cast<unsigned short *>(forks.data());
  auto result = ::semctl(id, 0, SETALL, semarg);

  if (result < 0) {
    throw syscalls::error("semsetall");
  }
}

void syscalls::semsetval(int id, int semnum, int semval) {
  semun sem_union;
  sem_union.val = semval;
  auto result = ::semctl(id, semnum, SETVAL, sem_union);

  if (result < 0) {
    throw syscalls::error("semsetval");
  }
}

void syscalls::semsignal(int id, int semnum, int amount) {
  auto result = sem_op(id, semnum, amount, 0);

  if (result < 0) {
    throw syscalls::error("semop", "signal");
  }
}

void syscalls::semwait(int id, int semnum, int amount) {
  auto result = sem_op(id, semnum, -amount, 0);

  if (result < 0) {
    syscalls::check_interrupt("semop", "wait");
  }
}

bool syscalls::try_semwait(int id, int semnum, int amount) {
  auto result = sem_op(id, semnum, -amount, IPC_NOWAIT);

  if (result < 0) {
    if (errno == EAGAIN) {
      return false;
    } else {
      syscalls::check_interrupt("semop", "trywait");
    }
  }

  return true;
}

void syscalls::semcontrol(int id, int semnum) {
  auto result = sem_op(id, semnum, 0, 0);

  if (result < 0) {
    syscalls::check_interrupt("semop", "control");
  }
}
