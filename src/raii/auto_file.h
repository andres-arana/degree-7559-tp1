#ifndef __RAII__FILE_H_INCLUDED__
#define __RAII__FILE_H_INCLUDED__

#include <string>
#include <sys/file.h>

namespace raii {
  class auto_file {
    public:
      auto_file();
      explicit auto_file(const std::string &filename, int flags);

      auto_file(const auto_file &other) = delete;
      auto_file & operator=(const auto_file &other) = delete;

      auto_file(auto_file &&other);
      auto_file &operator=(auto_file &&other);

      int fd() const;

      ~auto_file();

    private:
      int file_descriptor;
  };
}

#endif
