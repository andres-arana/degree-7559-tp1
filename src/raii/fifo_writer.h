#ifndef __RAII__FIFO_WRITER__H_INCLUDED__
#define __RAII__FIFO_WRITER__H_INCLUDED__

#include "syscalls/file.h"
#include "raii/fifo.h"
#include <string>

namespace raii {
  template<typename T>
  class fifo_writer {
    public:
      explicit fifo_writer(const std::string &path)
        : internal_fifo(path, O_WRONLY) { }

      explicit fifo_writer(const fifo_writer& other) = delete;
      fifo_writer &operator=(const fifo_writer& other) = delete;

      explicit fifo_writer(fifo_writer &&other) = delete;
      fifo_writer &operator=(fifo_writer &&other) = delete;

      void write(const T what) {
        syscalls::write(internal_fifo.fd(), &what, sizeof(T));
      }

      int fd() {
        return internal_fifo.fd();
      }

    private:
      fifo internal_fifo;
  };
}

#endif
