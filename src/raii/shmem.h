#ifndef __RAII__SHMEM__H_INCLUDED__
#define __RAII__SHMEM__H_INCLUDED__

#include "syscalls/shmem.h"

namespace raii {
  template<typename T>
  class shmem {
    public:
      explicit shmem(int id)
        : data(static_cast<T*>(syscalls::shmat(id))),
        identifier(id) {

        }

      explicit shmem(const shmem& other) = delete;
      shmem &operator=(const shmem& other) = delete;

      explicit shmem(shmem &&other) = delete;
      shmem &operator=(shmem &&other) = delete;

      T &operator*() {
        return *data;
      }

      T* operator->() {
        return data;
      }

      int id() {
        return identifier;
      }

      ~shmem() {
        syscalls::shmdt(data);
      }

    private:
      T *data;
      int identifier;
  };
}

#endif
