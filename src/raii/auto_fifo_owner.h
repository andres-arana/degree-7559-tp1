#ifndef __RAII__AUTO_FIFO_OWNER__H_INCLUDED__
#define __RAII__AUTO_FIFO_OWNER__H_INCLUDED__

#include <string>

namespace raii {
  class auto_fifo_owner {
    public:
      explicit auto_fifo_owner(const std::string &path);

      explicit auto_fifo_owner(const auto_fifo_owner& other) = delete;
      auto_fifo_owner &operator=(const auto_fifo_owner& other) = delete;

      explicit auto_fifo_owner(auto_fifo_owner &&other) = delete;
      auto_fifo_owner &operator=(auto_fifo_owner &&other) = delete;

      std::string path() const;

      ~auto_fifo_owner();

    private:
      std::string fifo_path;
  };
}

#endif
