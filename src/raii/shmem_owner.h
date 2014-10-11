#ifndef __RAII__SHMEM_OWNER__H_INCLUDED__
#define __RAII__SHMEM_OWNER__H_INCLUDED__

#include "syscalls/shmem.h"

namespace raii {
  template<typename T>
    class shmem_owner {
      public:
        explicit shmem_owner()
          :identifier(syscalls::shmget(sizeof(T))) {

          }

        explicit shmem_owner(const shmem_owner& other) = delete;
        shmem_owner &operator=(const shmem_owner& other) = delete;

        explicit shmem_owner(shmem_owner &&other) = delete;
        shmem_owner &operator=(shmem_owner &&other) = delete;

        int id() const {
          return identifier;
        }

        ~shmem_owner() {
          syscalls::shmrelease(identifier);
        }

      private:
        int identifier;
    };
}

#endif
