#ifndef __RAII__AUTH_SHMEM_OWNER__H_INCLUDED__
#define __RAII__AUTH_SHMEM_OWNER__H_INCLUDED__

#include "syscalls/shmem.h"

namespace raii {
  template<typename T>
    class auto_shmem_owner {
      public:
        explicit auto_shmem_owner()
          :identifier(syscalls::shmget(sizeof(T))) {

          }

        explicit auto_shmem_owner(const auto_shmem_owner& other) = delete;
        auto_shmem_owner &operator=(const auto_shmem_owner& other) = delete;

        explicit auto_shmem_owner(auto_shmem_owner &&other) = delete;
        auto_shmem_owner &operator=(auto_shmem_owner &&other) = delete;

        int id() const {
          return identifier;
        }

        ~auto_shmem_owner() {
          syscalls::shmrelease(identifier);
        }

      private:
        int identifier;
    };
}

#endif
