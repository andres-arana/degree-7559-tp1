#ifndef __SYSCALLS__SEM__H_INCLUDED__
#define __SYSCALLS__SEM__H_INCLUDED__

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <vector>
#include "syscalls/error.h"
#include "syscalls/interrupt.h"

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
  std::vector<unsigned short> semgetall(int id, int semnum);

  /**
   * @brief the number of processes waiting for an increase of semval for the
   * semnum-th semaphore of the set.
   * 
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   */
  int semgetncnt(int id, int semnum);

  /**
   * @brief Get the PID of the last process to have called semop on the semaphore
   *
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   */
  int semgetpid(int id, int semnum);

  /**
   * @brief The value of semval for the semnum-th* semaphore of the set.
   *
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   */
  int semgetval(int id, int semnum);

  /**
   * @brief the number of processes waiting for semval of the semnum-th
   * semaphore of the set to become 0.
   * 
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   */
  int semgetzcnt(int id, int semnum);

  /**
   * @brief Set semval for all sem by array.
   *
   * @param id identifier.
   * @param forks array with the all the values to be set.
   */
  void semsetall(int id, const std::vector<unsigned short> &forks);

  /**
   * @brief Set  the  value  of  semval for the semnum-th semaphore
   * of the set.
   *
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   * @param semval the value to assign to the sem.
   */
  void semsetval(int id, int semnum, int semval);

  /**
   * @brief Increase the value for the semnum-th semaphore by a given amount.
   *
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   * @param amount the amount to increase by.
   */
  void semsignal(int id, int semnum, int amount);

  /**
   * @brief Block until a given amount is available in the semnum-th semaphore,
   * and atomically decrease the semaphore when it is available.
   *
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   * @param amount the amount to decrease by.
   */
  void semwait(int id, int semnum, int amount);

  /**
   * @brief Try to decrease a given amount in the semnum-th semaphore if it is
   * available. Otherwise, do not decrease any amount and return false,
   *
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   * @param amount the amount to decrease by.
   *
   * @return true if the operation succedeed, false otherwise.
   */
  bool try_semwait(int id, int semnum, int amount);

  /**
   * @brief Block until the semnum-th semaphore is completely used (with amount
   * zero).
   *
   * @param id identifier.
   * @param semnum the semnum-th semaphore of the set.
   */
  void semcontrol(int id, int semnum);
}

#endif
