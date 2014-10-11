#ifndef __RAII__FIFO_OWNER__H_INCLUDED__
#define __RAII__FIFO_OWNER__H_INCLUDED__

#include <string>

namespace raii {
  class fifo_owner {
    public:
      explicit fifo_owner(const std::string &path);

      explicit fifo_owner(const fifo_owner& other) = delete;
      fifo_owner &operator=(const fifo_owner& other) = delete;

      explicit fifo_owner(fifo_owner &&other) = delete;
      fifo_owner &operator=(fifo_owner &&other) = delete;

      std::string path() const;

      ~fifo_owner();

    private:
      std::string fifo_path;
  };
}

#endif
