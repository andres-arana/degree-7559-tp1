#ifndef __RAII__SHMEM_DYN_OWNER__H_INCLUDED__
#define __RAII__SHMEM_DYN_OWNER__H_INCLUDED__

#include "syscalls/shmem.h"

namespace raii {
  template<typename T>
    class shmem_dyn_owner {
      public:
        explicit shmem_dyn_owner(size_t count)
          :identifier(syscalls::shmget(count * sizeof(T))) {

          }

        explicit shmem_dyn_owner(const shmem_dyn_owner& other) = delete;
        shmem_dyn_owner &operator=(const shmem_dyn_owner& other) = delete;

        explicit shmem_dyn_owner(shmem_dyn_owner &&other) = delete;
        shmem_dyn_owner &operator=(shmem_dyn_owner &&other) = delete;

        int id() const {
          return identifier;
        }

        ~shmem_dyn_owner() {
          syscalls::shmrelease(identifier);
        }

      private:
        int identifier;
    };
}

#endif
