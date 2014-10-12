#ifndef __SYSCALLS__SEM__H_INCLUDED__
#define __SYSCALLS__SEM__H_INCLUDED__

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <vector>

namespace syscalls {

  /**
   * @brief get set of semaphores
   * function returns the semaphore identifier associated with key.
   *
   * @param nsems number of semaphores in set.
   */
  int semget(unsigned short int nsem);

  /**
   * @brief removes the semaphore set.
   * Immediately remove the semaphore set, awakening all processes blocked.
   *
   * @param id identifier.
   */
  void semrelease(int id);

  /**
   * @brief Fills the forks array.
   * The semval for all semaphores of the set.
   *
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   */
  std::vector<unsigned short> sem_getall(int id, int semnum);

  /**
   * @brief the number of processes waiting for an increase of semval for the
   * semnum-th semaphore of the set.
   * 
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   */
  int sem_getncnt(int id, int semnum);

  /**
   * @brief Get the PID of the last process to have called semop on the semaphore
   *
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   */
  int sem_getpid(int id, int semnum);

  /**
   * @brief The value of semval for the semnum-th* semaphore of the set.
   *
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   */
  int sem_getval(int id, int semnum);

  /**
   * @brief the number of processes waiting for semval of the semnum-th
   * semaphore of the set to become 0.
   * 
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   */
  int sem_getzcnt(int id, int semnum);

  /**
   * @brief Set semval for all sem by array.
   *
   * @param id identifier.
   * @param forks array with the all the values to be set.
   */
  void sem_setall(int id, const std::vector<unsigned short> &forks);

  /**
   * @brief Set  the  value  of  semval for the semnum-th semaphore
   * of the set.
   *
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   * @param semval the value to assign to the sem.
   */
  void sem_setval(int id, int semnum, int semval);

  /**
   * @brief Changes the semaphore to waiting
   *
   * @param id identifier.
   * @param semnun the semnum-th semaphore of the set.
   */
  void sem_waiting(int id, int semnum);

  /**
   * @brief Changes the semaphore to available
   *
   * @param id identifier.
   * @param semnun the semnum-th semaphore of the set.
   */
  void sem_available(int id, int semnum);

}

#endif
