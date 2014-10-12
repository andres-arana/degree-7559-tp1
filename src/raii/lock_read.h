#ifndef __RAII__LOCK_READ__H_INCLUDED__
#define __RAII__LOCK_READ__H_INCLUDED__

namespace raii {
  class lock_read {
    public:
      explicit lock_read(int fd);

      explicit lock_read(const lock_read& other) = delete;
      lock_read &operator=(const lock_read& other) = delete;

      explicit lock_read(lock_read &&other) = delete;
      lock_read &operator=(lock_read &&other) = delete;

      ~lock_read();

    private:
      int file_descriptor;
  };
}

#endif
