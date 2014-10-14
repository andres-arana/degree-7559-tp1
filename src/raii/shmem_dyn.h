#ifndef __RAII__SHMEM_DYN__H_INCLUDED__
#define __RAII__SHMEM_DYN__H_INCLUDED__

#include "syscalls/shmem.h"

namespace raii {
  template<typename T>
  class shmem_dyn {
    public:
      explicit shmem_dyn(int id)
        : data(static_cast<T*>(syscalls::shmat(id))),
        identifier(id) {

        }

      explicit shmem_dyn(const shmem_dyn& other) = delete;
      shmem_dyn &operator=(const shmem_dyn& other) = delete;

      explicit shmem_dyn(shmem_dyn &&other) = delete;
      shmem_dyn &operator=(shmem_dyn &&other) = delete;

      T &operator[](int index) {
        return data[index];
      }

      int id() {
        return identifier;
      }

      ~shmem_dyn() {
        syscalls::shmdt(data);
      }

    private:
      T *data;
      int identifier;
  };
}

#endif
