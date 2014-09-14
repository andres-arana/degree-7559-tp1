#ifndef __UTIL__FILE_H_INCLUDED__
#define __UTIL__FILE_H_INCLUDED__

#include <string>
#include <sys/file.h>

namespace util {
  class auto_file {
    private:
      int file_descriptor;

    public:
      explicit auto_file(const std::string &filename, int flags);

      int fd() const;

      ~auto_file();
  };
};

#endif
