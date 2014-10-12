#ifndef __RAII__LOCK_WRITE__H_INCLUDED__
#define __RAII__LOCK_WRITE__H_INCLUDED__

namespace raii {
  class lock_write {
    public:
      explicit lock_write(int fd);

      explicit lock_write(const lock_write& other) = delete;
      lock_write &operator=(const lock_write& other) = delete;

      explicit lock_write(lock_write &&other) = delete;
      lock_write &operator=(lock_write &&other) = delete;

      ~lock_write();

    private:
      int file_descriptor;
  };
}

#endif
