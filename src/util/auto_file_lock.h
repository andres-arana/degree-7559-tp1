#ifndef __UTIL__AUTO_FILE_LOCK_H_INCLUDED__
#define __UTIL__AUTO_FILE_LOCK_H_INCLUDED__

#include <string>

namespace util {

  class auto_file_lock {
    private:
      int file_descriptor;

    public:

      explicit auto_file_lock(int file_descriptor);

      ~auto_file_lock();
  };

};

#endif
