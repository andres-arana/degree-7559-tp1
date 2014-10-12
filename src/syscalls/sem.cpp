#include "syscalls/sem.h"
#include "syscalls/error.h"

using namespace std;

namespace {
  /**
   * rw-rw-rw semflg is associated with sem_perm.mode
   */
  const int PERMISSIONS = 0666;

  union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO */
  };

  int sem_op(int id, int semnum, int op) {
    struct sembuf sem_b;

    sem_b.sem_num = semnum;
    sem_b.sem_op = op;

    /**
     * Flags recognized in sem_flg are IPC_NOWAIT and SEM_UNDO.  If an operation
     * specifies SEM_UNDO, it will be automatically undone when the process
     * terminates.
     */
    sem_b.sem_flg = SEM_UNDO;

    return ::semop(id, &sem_b, 1);
  }

}

int syscalls::semget(unsigned short int nsem) {
  /**
   * key is equal to IPC_PRIVATE
   */
  auto result = ::semget(IPC_PRIVATE, nsem, ::PERMISSIONS | IPC_CREAT);

  if (result < 0) {
    throw syscalls::error("semget");
  }

  return result;
}

void syscalls::semrelease(int id) {
  /* The argument semnum is ignored. */
  auto result = ::semctl(id, 0, IPC_RMID);

  if (result < 0) {
    throw syscalls::error("semctl", "IPC_RMID");
  }
}

vector<unsigned short> syscalls::sem_getall(int id, int semnum) {
  union semun semarg;
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
  union semun semarg;
  auto result = ::semctl(id, semnum, GETVAL, semarg);

  if (result < 0) {
    throw syscalls::error("sem_getval");
  }

  return semarg.val;
}

int syscalls::sem_getzcnt(int id, int semnum) {
  union semun semarg;
  auto result = ::semctl(id, semnum, GETZCNT, semarg);

  if (result < 0) {
    throw syscalls::error("sem_getzcnt");
  }

  return result;
}

void syscalls::sem_setall(int id, const vector<unsigned short> &forks) {
  union semun semarg;
  semarg.array = const_cast<unsigned short *>(forks.data());
  auto result = ::semctl(id, 0, SETALL, semarg);

  if (result < 0) {
    throw syscalls::error("sem_setall");
  }
}

void syscalls::sem_setval(int id, int semnum, int semval) {
  union semun sem_union;
  sem_union.val = semval;
  auto result = ::semctl(id, semnum, SETVAL, sem_union);

  if (result < 0) {
    throw syscalls::error("sem_setval");
  }
}

void syscalls::sem_waiting(int id, int semnum) {
  auto result = ::sem_op(id, semnum, -1);

  if (result < 0) {
    throw syscalls::error("sem_waiting");
  }
}

void syscalls::sem_available(int id, int semnum) {
  auto result = ::sem_op(id, semnum, 1);

  if (result < 0) {
    throw syscalls::error("sem_available");
  }
}

