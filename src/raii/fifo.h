#ifndef __RAII__FIFO__H_INCLUDED__
#define __RAII__FIFO__H_INCLUDED__

#include <string>

namespace raii {
  class fifo {
    public:
      explicit fifo(const std::string &path, int flags);

      explicit fifo(const fifo& other) = delete;
      fifo &operator=(const fifo& other) = delete;

      explicit fifo(fifo &&other) = delete;
      fifo &operator=(fifo &&other) = delete;

      int fd();

      ~fifo();

    private:
      int file_descriptor;
  };
}

#endif
