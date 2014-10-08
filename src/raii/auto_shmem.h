#ifndef __RAII__AUTH_SHMEM__H_INCLUDED__
#define __RAII__AUTH_SHMEM__H_INCLUDED__

namespace raii {
  template<typename T>
  class auto_shmem {
    public:
      explicit auto_shmem(int id)
        : data(static_cast<T*>(syscalls::shmat(id))) {

        }

      explicit auto_shmem(const auto_shmem& other) = delete;
      auto_shmem &operator=(const auto_shmem& other) = delete;

      explicit auto_shmem(auto_shmem &&other) = delete;
      auto_shmem &operator=(auto_shmem &&other) = delete;

      T &operator*() {
        return *data;
      }

      T* operator->() {
        return data;
      }

      ~auto_shmem() {
        syscalls::shmdt(data);
      }

    private:
      T *data;
  };
}

#endif
