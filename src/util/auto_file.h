#ifndef __UTIL__FILE_H_INCLUDED__
#define __UTIL__FILE_H_INCLUDED__

#include <string>
#include <sys/file.h>

namespace util {
  class auto_file {
    private:
      int file_descriptor;

    public:
      auto_file();
      explicit auto_file(const std::string &filename, int flags);

      auto_file(const auto_file &other) = delete;
      auto_file & operator=(const auto_file &other) = delete;

      auto_file(auto_file &&other);
      auto_file &operator=(auto_file &&other);

      int fd() const;

      ~auto_file();
  };
};

#endif
