#ifndef __RAII__FILE_H_INCLUDED__
#define __RAII__FILE_H_INCLUDED__

#include <string>
#include <sys/file.h>

namespace raii {
  class file {
    public:
      explicit file(const std::string &filename, int flags);

      file(const file &other) = delete;
      file & operator=(const file &other) = delete;

      file(file &&other) = delete;
      file &operator=(file &&other) = delete;

      int fd() const;

      void write(const std::string &what);

      ~file();

    private:
      int file_descriptor;
  };
}

#endif
