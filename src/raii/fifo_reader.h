#ifndef __RAII__FIFO_READER__H_INCLUDED__
#define __RAII__FIFO_READER__H_INCLUDED__

#include "syscalls/file.h"
#include "raii/fifo.h"
#include <string>

namespace raii {
  template<typename T>
  class fifo_reader {
    public:
      explicit fifo_reader(const std::string &path)
        : internal_fifo(path, O_RDONLY) { }

      explicit fifo_reader(const fifo_reader& other) = delete;
      fifo_reader &operator=(const fifo_reader& other) = delete;

      explicit fifo_reader(fifo_reader &&other) = delete;
      fifo_reader &operator=(fifo_reader &&other) = delete;

      T read() {
        T result;
        syscalls::read(internal_fifo.fd(), &result, sizeof(T));
        return result;
      }

      int fd() {
        return internal_fifo.fd();
      }

    private:
      fifo internal_fifo;
  };
}

#endif
